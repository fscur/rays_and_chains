#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_api_db_t r_api_db_t;
typedef struct r_plugin_t r_plugin_t;
typedef void* (*R_PLUGIN_LOADER_FN)(void*, const char*);

typedef struct r_plugin_load_info_t {
  R_PLUGIN_LOADER_FN fn;
  void* handle;
  void* memory_addr;
} r_plugin_load_info_t;

typedef u32 (*R_PLUGIN_GET_ID)();
typedef size_t (*R_PLUGIN_GET_SIZE)();
typedef void* (*R_PLUGIN_LOAD)(r_plugin_load_info_t* load_info);

typedef void (*R_PLUGIN_INIT)(void* state, r_api_db_t* api_db);
typedef void (*R_PLUGIN_INPUT)(void* state);
typedef void (*R_PLUGIN_UPDATE)(void* state, f64 dt);
typedef void (*R_PLUGIN_RENDER)(void* state);
typedef void (*R_PLUGIN_UNLOAD)(void* state);
typedef void (*R_PLUGIN_DESTROY)(void* state);

typedef struct r_plugin_t {
  void* handle;
  R_PLUGIN_INIT init;
  R_PLUGIN_INPUT input;
  R_PLUGIN_UPDATE update;
  R_PLUGIN_RENDER render;
  R_PLUGIN_UNLOAD unload;
  R_PLUGIN_DESTROY destroy;
  void* api;
  u32 id;
  char name[MAX_FILE_NAME_LENGTH];
  char file_name[MAX_FILE_NAME_LENGTH];
  char tmp_file_name[MAX_FILE_NAME_LENGTH];
  r_time_t last_modification;
  int version;
  void* state;
  bool active;
  bool reload;
  size_t memory_size;
} r_plugin_t;

#ifdef __cplusplus
}
#endif