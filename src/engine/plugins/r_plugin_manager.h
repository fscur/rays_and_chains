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
  void* init[MAX_PLUGINS_COUNT];
  void* input[MAX_PLUGINS_COUNT];
  void* update[MAX_PLUGINS_COUNT];
  void* render[MAX_PLUGINS_COUNT];
  void* unload[MAX_PLUGINS_COUNT];
  void* destroy[MAX_PLUGINS_COUNT];
  r_plugin_t* plugins[MAX_PLUGINS_COUNT];
  u8 plugin_count;
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
  void* (*find_plugin)(r_plugin_manager_t* state, const wchar_t* file_name);
} r_plugin_manager_api_t;

typedef r_plugin_manager_t* (*R_PLUGIN_MANAGER_CREATE)(r_memory_t*);
typedef void (*R_PLUGIN_MANAGER_ADD_PLUGIN)(r_plugin_manager_t*, r_plugin_t*);
typedef void (*R_PLUGIN_MANAGER_REMOVE_PLUGIN)(r_plugin_manager_t*, void*);
typedef void* (*R_PLUGIN_MANAGER_FIND_PLUGIN)(r_plugin_manager_t*, const wchar_t*);

dll_export void //
r_plugin_manager_add_plugin(r_plugin_manager_t* state, r_plugin_t* plugin);

dll_export void //
r_plugin_manager_remove_plugin(r_plugin_manager_t* state, r_plugin_t* plugin);

dll_export r_plugin_t* //
r_plugin_manager_find_plugin(r_plugin_manager_t* state, const wchar_t* file_name);

#ifdef __cplusplus
}
#endif