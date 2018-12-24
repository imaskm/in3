/** @file 
 * simple commandline-util sending in3-requests.
 * */ 

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <util/debug.h>
#include <util/utils.h>
#include <client/client.h>
#include <client/cache.h>
#include <in3_curl.h>
#include <in3_storage.h>
#include <eth_full.h>

#include <util/data.h>

uint64_t getChainId(char* name) {
  if (strcmp(name,"mainnet")==0)    return 0x01L;
  if (strcmp(name,"kovan")==0)      return 0x2aL;
  if (strcmp(name,"tobalaba")==0)   return 0x44dL;
  if (strcmp(name,"evan")==0)       return 0x4b1L;
  if (strcmp(name,"evan")==0)       return 0x4b1L;
  if (strcmp(name,"ipfs")==0)       return 0x7d0;
  return atoi(name);
}

void newp() {
  char* js = "{ \"key\":\"value\", \"array\":[1,2,3,4,\"test\"], \"sub\":{ \"a\":3}, \"bytes\":\"0xabcdef1234567890\"  }";
  d_item_t* root;
  int tokc;

  if (parse_json(js,&root,&tokc)==0) {
    char* val = d_get_string(root,"key");
    bytes_t* bytes = d_get_bytes(root,"bytes");
    b_print(bytes);

    str_range_t s = d_to_json( d_get(root,key("sub")));
    char tmp[1000];
    strncpy(tmp,s.data,s.len);
    printf("json = | %s | ",tmp);
  }

}


int main (int argc, char *argv[])
{
  newp();
  int i;
  if (argc < 2) {
    fprintf(stdout,"Usage: %s <options> method params ... \n  -p -proof    none|standard|full\n  -s -signs    number of signatures\n  -c -chain    mainnet|kovan|evan|tobalaba|ipfs\n",argv[0]);
    return 1;
  }
  

  char* method=NULL;
  char params[5000];
  params[0]='[';
  int p=1;

  in3_storage_handler_t storage_handler;
  storage_handler.get_item=storage_get_item;
  storage_handler.set_item=storage_set_item;

  in3_register_eth_full();

  in3_t* c = in3_new();
  c->transport = send_curl;
  c->requestCount = 1;
  c->cacheStorage = &storage_handler;
  in3_cache_init(c);
  

  // fill from args
  for (i=1;i<argc;i++) {
    if (strcmp(argv[i],"-chain")==0 || strcmp(argv[i],"-c")==0)
       c->chainId = getChainId(argv[++i]);
    else if (strcmp(argv[i],"-signs")==0 || strcmp(argv[i],"-s")==0)
       c->signatureCount = atoi(argv[++i]);
    else if (strcmp(argv[i],"-proof")==0 || strcmp(argv[i],"-p")==0) {
      if (strcmp(argv[i+1],"none")==0) 
         c->proof = PROOF_NONE;
      else if (strcmp(argv[i+1],"standard")==0) 
         c->proof = PROOF_STANDARD;
      else if (strcmp(argv[i+1],"full")==0) 
         c->proof = PROOF_FULL;
      else {
        printf("Invalid Argument for proof: %s\n",argv[i+1]);
        return 1;
      }
      i++;
    }
    else {
      if (method==NULL)
        method=argv[i];
      else {
        if (p>1) params[p++]=',';
        if (argv[i][0]=='{' || strcmp(argv[i],"true")==0 || strcmp(argv[i],"false")==0)
          p+=sprintf(params+p,"%s",argv[i]);
        else
          p+=sprintf(params+p,"\"%s\"",argv[i]);
      }
    }
  }
  params[p++]=']';
  params[p]=0;


  char* result;
  char* error;;

  in3_client_rpc(c, method, params, &result, &error);
  in3_free(c);

  if (error) {
    fprintf(stderr, "Error: %s\n",error);
    free(error);
    return 1;
  }
  else {
     printf( "%s\n",result);
     free(result);
  }
  return 0;
}