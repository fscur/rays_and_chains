#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define MAX_PLUGINS_COUNT 256

typedef struct r_memory_t r_memory_t;
typedef struct r_memory_block_t r_memory_block_t;
typedef struct r_plugin_t r_plugin_t;

typedef struct r_plugin_manager_t {
  r_memory_t* memory;
  u8 init[MAX_PLUGINS_COUNT];
  u8 input[MAX_PLUGINS_COUNT];
  u8 update[MAX_PLUGINS_COUNT];
  u8 render[MAX_PLUGINS_COUNT];
  u8 unload[MAX_PLUGINS_COUNT];
  u8 destroy[MAX_PLUGINS_COUNT];
  u8 reloaded_plugins[MAX_PLUGINS_COUNT];
  r_plugin_t* plugins;
  u8 plugin_count;
  u8 init_count;
  u8 input_count;
  u8 update_count;
  u8 render_count;
  u8 unload_count;
  u8 destroy_count;
  u8 reloaded_count;
} r_plugin_manager_t;

typedef r_plugin_manager_t* (*R_PLUGIN_MANAGER_CREATE)(r_memory_t*);
typedef void (*R_PLUGIN_MANAGER_ADD_PLUGIN)(r_plugin_manager_t*, r_plugin_t*);
typedef void (*R_PLUGIN_MANAGER_REMOVE_PLUGIN)(r_plugin_manager_t*, void*);
typedef r_plugin_t* (*R_PLUGIN_MANAGER_FIND_PLUGIN)(r_plugin_manager_t*, const char*);

dll_export void //
r_plugin_manager_init(r_plugin_manager_t* this);

dll_export void //
r_plugin_manager_reload_plugins(r_plugin_manager_t* this);

dll_export void //
r_plugin_manager_add_plugin(r_plugin_manager_t* this, r_plugin_t* plugin);

dll_export bool //
r_plugin_manager_should_reload(r_plugin_manager_t* this, r_plugin_t* plugin);

dll_export void //
r_plugin_manager_unload_plugin(r_plugin_manager_t* this, r_plugin_t* plugin);

dll_export void //
r_plugin_manager_reload_plugin(r_plugin_manager_t* this, r_plugin_t* plugin);

dll_export void //
r_plugin_manager_remove_plugin(r_plugin_manager_t* this, r_plugin_t* plugin);

dll_export r_plugin_t* //
r_plugin_manager_find_plugin(r_plugin_manager_t* this, const char* name);

#ifdef __cplusplus
}
#endif