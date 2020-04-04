#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_memory_arena_t r_memory_arena_t;
typedef struct r_lib_load_info_t r_lib_load_info_t;
typedef struct r_api_db_i r_api_db_i;

typedef void* (*R_LIB_LOADER_FN)(void*, const char*);
typedef size_t (*R_LIB_GET_SIZE)();
typedef u32 (*R_LIB_GET_FN_COUNT)();
typedef void* (*R_LIB_LOAD)(r_lib_load_info_t* load_info);

typedef struct r_lib_load_info_t {
  R_LIB_LOADER_FN fn;
  void* handle;
  void* api_memory_addr;
  void* lib_memory_addr;
  void* state_memory_addr;
} r_lib_load_info_t;

typedef struct r_lib_i {
  size_t (*get_size)(void);
  char* (*get_api_name)(void);
  void* (*init)(void* api, r_api_db_i* db);
  void* (*destroy)(void* state);
} r_lib_i;

typedef struct r_lib_t {
  char name[R_SHORT_STRING_LENGTH];          // 256
  char file_name[R_SHORT_STRING_LENGTH];     // 256
  char tmp_file_name[R_SHORT_STRING_LENGTH]; // 256
  r_datetime_t last_modification;          // 16
  void* handle;                            // 8
  r_memory_arena_t* memory_arena;          // 8
  void* api;                               // 8
  void* state;                             // 8
  i32 version;                             // 4
} r_lib_t;

#ifdef __cplusplus
}
#endif

