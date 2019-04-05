#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_api_db_t r_api_db_t;
typedef struct r_app_t r_app_t;
typedef struct r_memory_block_t r_memory_block_t;
typedef struct r_app_load_info_t r_app_load_info_t;
typedef struct r_frame_info_t r_frame_info_t;

typedef void* (*R_APP_LOADER_FN)(void*, const char*);

typedef u32 (*R_APP_GET_ID)();
typedef size_t (*R_APP_GET_SIZE)();
typedef void* (*R_APP_LOAD)(r_app_load_info_t* load_info);

typedef void (*R_APP_INIT)(void* state, r_api_db_t* api_db);
typedef void (*R_APP_RUN)(void* state, r_frame_info_t* frame_info);
typedef void (*R_APP_DESTROY)(void* state);

typedef struct r_app_load_info_t {
  R_APP_LOADER_FN fn;
  void* handle;
  void* app_addr;
  void* state_addr;
} r_app_load_info_t;

typedef struct r_app_api_t {
  R_APP_INIT init;
  R_APP_RUN run;
  R_APP_DESTROY destroy;
} r_app_api_t;

typedef struct r_app_t {
  r_lib_t lib;
  r_app_api_t api;
  void* state;  
} r_app_t;

#ifdef __cplusplus
}
#endif