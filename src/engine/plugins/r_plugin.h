#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_plugin_manager_t r_plugin_manager_t;

typedef struct r_plugin_t {
  void* handle;
  void (*init)(void* state, r_plugin_manager_t* plugin_manager);
  void (*input)(void* state);
  void (*update)(void* state, f64 dt);
  void (*render)(void* state);
  void (*unload)(void* state);
  void (*destroy)(void* state);
  void* api;
  char name[MAX_FILE_NAME_LENGTH];
  char file_name[MAX_FILE_NAME_LENGTH];
  int version;
  void* state_addr;
  bool active;
  bool reload;
  size_t memory_size;
} r_plugin_t;

typedef void* (*R_PLUGIN_LOAD)(r_memory_t*, void*);
typedef void (*R_PLUGIN_INIT)(void* state, r_plugin_manager_t*);
typedef void (*R_PLUGIN_INPUT)(void* state);
typedef void (*R_PLUGIN_UPDATE)(void* state, f64 dt);
typedef void (*R_PLUGIN_RENDER)(void* state);
typedef void (*R_PLUGIN_UNLOAD)(void* state);
typedef void (*R_PLUGIN_DESTROY)(void* state);

#ifdef __cplusplus
}
#endif