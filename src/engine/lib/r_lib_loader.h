#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_memory_t r_memory_t;
typedef struct r_lib_t r_lib_t;

dll_export r_lib_t* //
r_lib_loader_load_lib(r_memory_t* memory, const char* filename);

dll_export void //
r_lib_loader_destroy_lib(r_lib_t* lib);

dll_export void //
r_lib_loader_reload_lib(r_lib_t* lib);

dll_export void* //
r_lib_loader_fn(void* handle, const char* function_name);

#ifdef __cplusplus
}
#endif