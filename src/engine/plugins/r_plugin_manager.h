#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_memory_t r_memory_t;
typedef struct r_plugin_t r_plugin_t;

typedef struct r_plugin_manager_t {
  r_memory_t* memory;
  r_plugin_t* plugins;
  u8 plugin_count;
} r_plugin_manager_t;

dll_export void //
r_plugin_manager_add(r_plugin_manager_t* state, char* file_name, void* api, size_t memory_size);

dll_export void //
r_plugin_manager_remove(r_plugin_manager_t* state, void* api);

dll_export void* //
r_plugin_manager_find(r_plugin_manager_t* state, char* file_name);

#ifdef __cplusplus
}
#endif