#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_memory_t r_memory_t;
typedef struct r_plugin_t r_plugin_t;

dll_export r_plugin_t* //
r_plugin_loader_load_plugin(r_memory_t* memory, r_plugin_t* plugins, const char* file_name);

dll_export void //
r_plugin_loader_unload_plugin(r_plugin_t* plugin);

dll_export r_plugin_t* //
r_plugin_loader_reload_plugin(r_memory_t* memory, r_plugin_t* plugin);

dll_export void* //
r_plugin_loader_fn(void* plugin_handle, const char* function_name);

#ifdef __cplusplus
}
#endif