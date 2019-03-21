#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define MAX_PLUGINS_COUNT 100

typedef struct r_memory_t r_memory_t;
typedef struct r_plugin_t r_plugin_t;

typedef struct r_plugin_manager_t {
  r_memory_t* memory;
  u8 init[MAX_PLUGINS_COUNT];
  u8 input[MAX_PLUGINS_COUNT];
  u8 update[MAX_PLUGINS_COUNT];
  u8 render[MAX_PLUGINS_COUNT];
  u8 unload[MAX_PLUGINS_COUNT];
  u8 destroy[MAX_PLUGINS_COUNT];
  // void* init[MAX_PLUGINS_COUNT];
  // void* input[MAX_PLUGINS_COUNT];
  // void* update[MAX_PLUGINS_COUNT];
  // void* render[MAX_PLUGINS_COUNT];
  // void* unload[MAX_PLUGINS_COUNT];
  // void* destroy[MAX_PLUGINS_COUNT];
  r_plugin_t* plugins[MAX_PLUGINS_COUNT];
  u8 plugin_count;
  u8 init_count;
  u8 input_count;
  u8 update_count;
  u8 render_count;
  u8 unload_count;
  u8 destroy_count;
} r_plugin_manager_t;

#define R_PLUGIN_MANAGER_API L"r_plugin_manager.dll"
#define R_PLUGIN_MANAGER_API_CREATE "r_plugin_manager_create"
#define R_PLUGIN_MANAGER_API_ADD_PLUGIN "r_plugin_manager_add_plugin"
#define R_PLUGIN_MANAGER_API_REMOVE_PLUGIN "r_plugin_manager_remove_plugin"
#define R_PLUGIN_MANAGER_API_FIND_PLUGIN "r_plugin_manager_find_plugin"

typedef struct r_plugin_manager_api_t {
  void* handle;
  r_plugin_manager_t* (*create)(r_memory_t* memory);
  void (*add_plugin)(r_plugin_manager_t* state, r_plugin_t* plugin);
  void (*remove_plugin)(r_plugin_manager_t* state, r_plugin_t* plugin);
  r_plugin_t* (*find_plugin)(r_plugin_manager_t* state, const char* name);
} r_plugin_manager_api_t;

typedef r_plugin_manager_t* (*R_PLUGIN_MANAGER_CREATE)(r_memory_t*);
typedef void (*R_PLUGIN_MANAGER_ADD_PLUGIN)(r_plugin_manager_t*, r_plugin_t*);
typedef void (*R_PLUGIN_MANAGER_REMOVE_PLUGIN)(r_plugin_manager_t*, void*);
typedef r_plugin_t* (*R_PLUGIN_MANAGER_FIND_PLUGIN)(r_plugin_manager_t*, const char*);

dll_export void //
r_plugin_manager_init(r_plugin_manager_t* this);

dll_export void //
r_plugin_manager_add_plugin(r_plugin_manager_t* this, r_plugin_t* plugin);

dll_export void //
r_plugin_manager_remove_plugin(r_plugin_manager_t* this, r_plugin_t* plugin);

dll_export r_plugin_t* //
r_plugin_manager_find_plugin(r_plugin_manager_t* this, const char* name);

#ifdef __cplusplus
}
#endif