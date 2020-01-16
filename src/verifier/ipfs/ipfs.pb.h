/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.0 */

#ifndef PB_IPFS_PB_H_INCLUDED
#define PB_IPFS_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _Data_DataType {
    Data_DataType_Raw = 0,
    Data_DataType_Directory = 1,
    Data_DataType_File = 2,
    Data_DataType_Metadata = 3,
    Data_DataType_Symlink = 4,
    Data_DataType_HAMTShard = 5
} Data_DataType;

/* Struct definitions */
typedef struct _PBNode {
    pb_callback_t Data;
    pb_callback_t Links;
} PBNode;

typedef struct _Data {
    Data_DataType Type;
    pb_callback_t Data;
    bool has_filesize;
    uint64_t filesize;
    pb_callback_t blocksizes;
    bool has_hashType;
    uint64_t hashType;
    bool has_fanout;
    uint64_t fanout;
} Data;

typedef struct _PBLink {
    pb_callback_t Hash;
    pb_callback_t Name;
    bool has_Tsize;
    uint64_t Tsize;
} PBLink;


/* Helper constants for enums */
#define _Data_DataType_MIN Data_DataType_Raw
#define _Data_DataType_MAX Data_DataType_HAMTShard
#define _Data_DataType_ARRAYSIZE ((Data_DataType)(Data_DataType_HAMTShard+1))


/* Initializer values for message structs */
#define Data_init_default                        {_Data_DataType_MIN, {{NULL}, NULL}, false, 0, {{NULL}, NULL}, false, 0, false, 0}
#define PBLink_init_default                      {{{NULL}, NULL}, {{NULL}, NULL}, false, 0}
#define PBNode_init_default                      {{{NULL}, NULL}, {{NULL}, NULL}}
#define Data_init_zero                           {_Data_DataType_MIN, {{NULL}, NULL}, false, 0, {{NULL}, NULL}, false, 0, false, 0}
#define PBLink_init_zero                         {{{NULL}, NULL}, {{NULL}, NULL}, false, 0}
#define PBNode_init_zero                         {{{NULL}, NULL}, {{NULL}, NULL}}

/* Field tags (for use in manual encoding/decoding) */
#define PBNode_Links_tag                         2
#define PBNode_Data_tag                          1
#define Data_Type_tag                            1
#define Data_Data_tag                            2
#define Data_filesize_tag                        3
#define Data_blocksizes_tag                      4
#define Data_hashType_tag                        5
#define Data_fanout_tag                          6
#define PBLink_Hash_tag                          1
#define PBLink_Name_tag                          2
#define PBLink_Tsize_tag                         3

/* Struct field encoding specification for nanopb */
#define Data_FIELDLIST(X, a) \
X(a, STATIC,   REQUIRED, UENUM,    Type,              1) \
X(a, CALLBACK, OPTIONAL, BYTES,    Data,              2) \
X(a, STATIC,   OPTIONAL, UINT64,   filesize,          3) \
X(a, CALLBACK, REPEATED, UINT64,   blocksizes,        4) \
X(a, STATIC,   OPTIONAL, UINT64,   hashType,          5) \
X(a, STATIC,   OPTIONAL, UINT64,   fanout,            6)
#define Data_CALLBACK pb_default_field_callback
#define Data_DEFAULT NULL

#define PBLink_FIELDLIST(X, a) \
X(a, CALLBACK, OPTIONAL, BYTES,    Hash,              1) \
X(a, CALLBACK, OPTIONAL, STRING,   Name,              2) \
X(a, STATIC,   OPTIONAL, UINT64,   Tsize,             3)
#define PBLink_CALLBACK pb_default_field_callback
#define PBLink_DEFAULT NULL

#define PBNode_FIELDLIST(X, a) \
X(a, CALLBACK, OPTIONAL, BYTES,    Data,              1) \
X(a, CALLBACK, REPEATED, MESSAGE,  Links,             2)
#define PBNode_CALLBACK pb_default_field_callback
#define PBNode_DEFAULT NULL
#define PBNode_Links_MSGTYPE PBLink

extern const pb_msgdesc_t Data_msg;
extern const pb_msgdesc_t PBLink_msg;
extern const pb_msgdesc_t PBNode_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define Data_fields &Data_msg
#define PBLink_fields &PBLink_msg
#define PBNode_fields &PBNode_msg

/* Maximum encoded size of messages (where known) */
/* Data_size depends on runtime parameters */
/* PBLink_size depends on runtime parameters */
/* PBNode_size depends on runtime parameters */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
