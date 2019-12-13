#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_app_t r_app_t;
typedef struct r_memory_arena_t r_memory_arena_t;

typedef void* (*R_APP_LOADER_FN)(void*, const char*);

typedef struct r_app_load_info_t {
  R_APP_LOADER_FN fn;
  void* handle;
  void* app_addr;
  void* state_addr;
} r_app_load_info_t;

typedef struct r_app_t {
  r_lib_t lib;
  r_memory_arena_t* memory_arena;
  bool running;
} r_app_t;

#ifdef __cplusplus
}
#endif