#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_api_db_t r_api_db_t;
typedef struct r_plugin_t r_plugin_t;
typedef struct r_memory_arena_t r_memory_arena_t;
typedef struct r_plugin_load_info_t r_plugin_load_info_t;

typedef void* (*R_PLUGIN_LOADER_FN)(void*, const char*);

typedef u32 (*R_PLUGIN_GET_ID)();
typedef size_t (*R_PLUGIN_GET_SIZE)();
typedef void* (*R_PLUGIN_LOAD)(r_plugin_load_info_t* load_info);

typedef void (*R_PLUGIN_INIT)(void* state, r_api_db_t* api_db);
typedef void (*R_PLUGIN_INPUT)(void* state);
typedef void (*R_PLUGIN_UPDATE)(void* state, f64 dt);
typedef void (*R_PLUGIN_RENDER)(void* state);
typedef void (*R_PLUGIN_UNLOAD)(void* state);
typedef void (*R_PLUGIN_DESTROY)(void* state);

typedef struct r_plugin_load_info_t {
  R_PLUGIN_LOADER_FN fn;
  void* handle;
  void* plugin_memory_addr;
  void* state_memory_addr;
} r_plugin_load_info_t;

typedef struct r_plugin_t {
  char name[SHORT_STRING_LENGTH];
  u32 id;
  int version;
  size_t memory_size;
  void* handle;
  void* state;
  void* api;
  r_memory_arena_t* memory_arena;
  R_PLUGIN_INIT init;
  R_PLUGIN_INPUT input;
  R_PLUGIN_UPDATE update;
  R_PLUGIN_RENDER render;
  R_PLUGIN_UNLOAD unload;
  R_PLUGIN_DESTROY destroy;
  char file_name[SHORT_STRING_LENGTH];
  char tmp_file_name[SHORT_STRING_LENGTH];
  r_datetime_t last_modification;
} r_plugin_t;

#ifdef __cplusplus
}
#endif