#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"
typedef struct r_plugin_t r_plugin_t;
typedef void* (*R_PLUGIN_LOADER_FN)(void*, const char*);

typedef struct r_plugin_manager_t r_plugin_manager_t;
typedef struct r_plugin_manager_api_t r_plugin_manager_api_t;
typedef r_plugin_t* (*R_PLUGIN_MANAGER_FIND_PLUGIN)(r_plugin_manager_t*, const char*);

typedef struct r_plugin_t {
  void* handle;
  void (*init)(void*, R_PLUGIN_MANAGER_FIND_PLUGIN, r_plugin_manager_t*);
  void (*input)(void*);
  void (*update)(void*, f64);
  void (*render)(void*);
  void (*unload)(void*);
  void (*destroy)(void*);
  void* api;
  char name[MAX_FILE_NAME_LENGTH];
  char file_name[MAX_FILE_NAME_LENGTH];
  char tmp_file_name[MAX_FILE_NAME_LENGTH];
  int version;
  void* state_addr;
  bool active;
  bool reload;
  size_t memory_size;
} r_plugin_t;

typedef size_t (*R_PLUGIN_GET_SIZE)();
typedef void* (*R_PLUGIN_LOAD)(R_PLUGIN_LOADER_FN, void*, void*);
typedef void (*R_PLUGIN_INIT)(void* state, R_PLUGIN_MANAGER_FIND_PLUGIN, r_plugin_manager_t*);
typedef void (*R_PLUGIN_INPUT)(void* state);
typedef void (*R_PLUGIN_UPDATE)(void* state, f64 dt);
typedef void (*R_PLUGIN_RENDER)(void* state);
typedef void (*R_PLUGIN_UNLOAD)(void* state);
typedef void (*R_PLUGIN_DESTROY)(void* state);

#ifdef __cplusplus
}
#endif