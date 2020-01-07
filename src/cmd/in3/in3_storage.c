
/*******************************************************************************
 * This file is part of the Incubed project.
 * Sources: https://github.com/slockit/in3-c
 * 
 * Copyright (C) 2018-2019 slock.it GmbH, Blockchains LLC
 * 
 * 
 * COMMERCIAL LICENSE USAGE
 * 
 * Licensees holding a valid commercial license may use this file in accordance 
 * with the commercial license agreement provided with the Software or, alternatively, 
 * in accordance with the terms contained in a written agreement between you and 
 * slock.it GmbH/Blockchains LLC. For licensing terms and conditions or further 
 * information please contact slock.it at in3@slock.it.
 * 	
 * Alternatively, this file may be used under the AGPL license as follows:
 *    
 * AGPL LICENSE USAGE
 * 
 * This program is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Affero General Public License as published by the Free Software 
 * Foundation, either version 3 of the License, or (at your option) any later version.
 *  
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
 * [Permissions of this strong copyleft license are conditioned on making available 
 * complete source code of licensed works and modifications, which include larger 
 * works using a licensed work, under the same license. Copyright and license notices 
 * must be preserved. Contributors provide an express grant of patent rights.]
 * You should have received a copy of the GNU Affero General Public License along 
 * with this program. If not, see <https://www.gnu.org/licenses/>.
 *******************************************************************************/

#include "in3_storage.h"
#include "../../core/client/client.h"
#include "../../core/util/mem.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// fixme: this is required until we find a good alternative to nfw() on gcc5
// and arm7
#ifndef _U_SHORT
#define _U_SHORT
typedef unsigned short u_short;
#endif /* _U_SHORT */

#if defined(_WIN32)
#include <direct.h>
#else
#include <fts.h>
#include <ftw.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif

static char* _HOME_DIR = NULL;
static char* get_storage_dir() {
  if (_HOME_DIR == NULL) {
#if defined(_WIN32)
    char* home = getenv("USERPROFILE");
    if (!home) home = ".";
    _HOME_DIR = _malloc(strlen(home) + 8);
    sprintf(_HOME_DIR, "%s\\.in3\\", home);
    _mkdir(_HOME_DIR);
#else
    char* home = getenv("HOME");
    if (!home) home = ".";
    _HOME_DIR = _malloc(strlen(home) + 8);
    sprintf(_HOME_DIR, "%s/.in3/", home);
    mode_t old_umask;
    old_umask = umask(0);
    mkdir(_HOME_DIR, 0777);
    umask(old_umask);
#endif
  }
  return _HOME_DIR;
}

static char* create_path(char* key) {
  char* path = _malloc(strlen(get_storage_dir()) + strlen(key) + 5);
  sprintf(path, "%s%s", get_storage_dir(), key);
  return path;
}

bytes_t* storage_get_item(void* cptr, char* key) {
  UNUSED_VAR(cptr);
  char* path = create_path(key);

  FILE* file = fopen(path, "r");
  if (file) {
    size_t   allocated = 1024;
    size_t   len       = 0;
    uint8_t* buffer    = _malloc(1024);
    size_t   r;

    while (1) {
      r = fread(buffer + len, 1, allocated - len, file);
      len += r;
      if (feof(file)) break;
      buffer = _realloc(buffer, allocated * 2, allocated);
      allocated *= 2;
    }
    fclose(file);

    bytes_t* res = _malloc(sizeof(bytes_t));
    res->data    = buffer;
    res->len     = len;
    return res;
  }
  return NULL;
}

void storage_set_item(void* cptr, char* key, bytes_t* content) {
  UNUSED_VAR(cptr);
  char* path = create_path(key);
  FILE* file = fopen(path, "wb");
  if (file) {
    fwrite(content->data, sizeof(uint8_t), content->len, file);
    fclose(file);
  }
  _free(path);
}

static int rm_recurs(const char* dir) {
  int     ret  = 0;
  FTS*    ftsp = NULL;
  FTSENT* curr;

  char* files[] = {(char*) dir, NULL};

  ftsp = fts_open(files, FTS_NOCHDIR | FTS_PHYSICAL | FTS_XDEV, NULL);
  if (!ftsp) {
    ret = -1;
    goto finish;
  }

  while ((curr = fts_read(ftsp))) {
    switch (curr->fts_info) {
      case FTS_NS:
      case FTS_DNR:
      case FTS_ERR:
        fprintf(stderr, "%s: fts_read error: %s\n",
                curr->fts_accpath, strerror(curr->fts_errno));
        break;

      case FTS_DC:
      case FTS_DOT:
      case FTS_NSOK:
      case FTS_D:
        break;

      case FTS_DP:
      case FTS_F:
      case FTS_SL:
      case FTS_SLNONE:
      case FTS_DEFAULT:
        if (remove(curr->fts_accpath) < 0)
          ret = -1;
        break;
    }
  }

finish:
  if (ftsp)
    fts_close(ftsp);

  return ret;
}

void storage_clear(void* cptr) {
  UNUSED_VAR(cptr);
  rm_recurs(get_storage_dir());
  // recreate storage dir
  free(_HOME_DIR);
  _HOME_DIR = NULL;
  UNUSED_VAR(get_storage_dir());
}
