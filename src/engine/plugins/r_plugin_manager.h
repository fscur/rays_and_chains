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
  void* update[MAX_PLUGINS_COUNT];
  r_plugin_t* plugins[MAX_PLUGINS_COUNT];
  u8 plugin_count;
} r_plugin_manager_t;

#define R_PLUGIN_MANAGER_API "r_plugin_manager.dll"
#define R_PLUGIN_MANAGER_API_CREATE "r_plugin_manager_create"
#define R_PLUGIN_MANAGER_API_ADD "r_plugin_manager_add"
#define R_PLUGIN_MANAGER_API_REMOVE "r_plugin_manager_remove"
#define R_PLUGIN_MANAGER_API_FIND "r_plugin_manager_find"

// typedef struct r_plugin_manager_api_t {
//   void* handle;
//   r_plugin_manager_t* (*create)(r_memory_t* memory);
//   void (*add)(r_plugin_manager_t* state, r_plugin_t* plugin);
//   void (*remove)(r_plugin_manager_t* state, r_plugin_t* plugin);
//   void* (*find)(r_plugin_manager_t* state, char* file_name);
// } r_plugin_manager_api_t;

// typedef r_plugin_manager_t* (*R_PLUGIN_MANAGER_CREATE)(r_memory_t*);
// typedef void (*R_PLUGIN_MANAGER_ADD)(r_plugin_manager_t*, char*, void*, size_t);
// typedef void (*R_PLUGIN_MANAGER_REMOVE)(r_plugin_manager_t*, void*);
// typedef void* (*R_PLUGIN_MANAGER_FIND)(r_plugin_manager_t*, char*);

dll_export void //
r_plugin_manager_add(r_plugin_manager_t* state, r_plugin_t* plugin);

dll_export void //
r_plugin_manager_remove(r_plugin_manager_t* state, r_plugin_t* plugin);

dll_export r_plugin_t* //
r_plugin_manager_find(r_plugin_manager_t* state, char* file_name);

#ifdef __cplusplus
}
#endif