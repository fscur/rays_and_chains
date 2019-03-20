#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

dll_export void* //
r_plugin_loader_load_plugin(const wchar_t* file_name);

dll_export void //
r_plugin_loader_unload_plugin(void* plugin_handle);

dll_export void* //
r_plugin_loader_reload_plugin(void* plugin_handle,
                              const wchar_t* file_name,
                              const wchar_t* tmp_file_name);

dll_export void* //
r_plugin_loader_fn(void* plugin_handle, const char* function_name);

#ifdef __cplusplus
}
#endif