#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"
#include "engine/memory/r_memory.h"
#include "engine/memory/r_memory_arena.h"
#include "r_plugin.h"

typedef struct r_plugin_manager_state_t {
  r_memory_arena_t* memory_arena;
  r_plugin_t plugins[5];
  u8 plugin_count;
} r_plugin_manager_state_t;

typedef struct r_plugin_manager_api {
  void* handle;
  r_plugin_manager_state_t* (*create)(r_memory_t* memory);
  void (*add)(r_plugin_manager_state_t* state, char* file_name, void* api, size_t memory_size);
  void (*remove)(r_plugin_manager_state_t* state, void* api);
  void* (*find)(r_plugin_manager_state_t* state, char* file_name);
} r_plugin_manager_api;

typedef r_plugin_manager_state_t* (*R_PLUGIN_MANAGER_CREATE)(r_memory_t*);
typedef void (*R_PLUGIN_MANAGER_ADD)(r_plugin_manager_state_t*, char*, void*, size_t);
typedef void (*R_PLUGIN_MANAGER_REMOVE)(r_plugin_manager_state_t*, void*);
typedef void* (*R_PLUGIN_MANAGER_FIND)(r_plugin_manager_state_t*, char*);

dll_export r_plugin_manager_state_t* //
r_plugin_manager_create(r_memory_t* memory);

dll_export void //
r_plugin_manager_add(r_plugin_manager_state_t* state,
                     char* file_name,
                     void* api,
                     size_t memory_size);

dll_export void //
r_plugin_manager_remove(r_plugin_manager_state_t* state, void* api);

dll_export void* //
r_plugin_manager_find(r_plugin_manager_state_t* state, char* file_name);

#ifdef __cplusplus
}
#endif