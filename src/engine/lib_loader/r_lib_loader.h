#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_memory_t r_memory_t;
typedef struct r_api_db_t r_api_db_t;

dll_export void //
r_lib_loader_load_lib(r_memory_t* memory, r_lib_t* lib, const char* filename);

dll_export void //
r_lib_loader_destroy_lib(r_lib_t* lib);

dll_export void //
r_lib_loader_reload_lib(r_lib_t* lib);

dll_export void* //
r_lib_loader_fn(void* handle, const char* function_name);

#ifdef __cplusplus
}
#endif