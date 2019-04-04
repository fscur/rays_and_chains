#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_api_db_t r_api_db_t;
typedef struct r_app_t r_app_t;
typedef struct r_memory_block_t r_memory_block_t;
typedef void* (*R_APP_LOADER_FN)(void*, const char*);

typedef struct r_app_load_info_t {
  R_APP_LOADER_FN fn;
  void* handle;
  void* app_addr;
  void* memory_addr;
} r_app_load_info_t;

typedef u32 (*R_APP_GET_ID)();
typedef size_t (*R_APP_GET_SIZE)();
typedef void* (*R_APP_LOAD)(r_app_load_info_t* load_info);

typedef void (*R_APP_INIT)(void* state, r_api_db_t* api_db);
typedef void (*R_APP_RUN)(void* state);
typedef void (*R_APP_DESTROY)(void* state);

typedef struct r_app_t {
  void* handle;
  R_APP_INIT init;
  R_APP_RUN run;
  R_APP_DESTROY destroy;
  u32 id;
  int version;
  char name[MAX_FILE_NAME_LENGTH];
  char file_name[MAX_FILE_NAME_LENGTH];
  char tmp_file_name[MAX_FILE_NAME_LENGTH];
  r_datetime_t last_modification;
  void* state;
  void* api;
  size_t memory_size;
  r_memory_block_t* memory_block;
} r_app_t;

#ifdef __cplusplus
}
#endif