#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_memory_arenat_t r_memory_arenat_t;

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

