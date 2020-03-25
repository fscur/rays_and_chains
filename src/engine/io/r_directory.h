#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

dll_export void //
r_directory_w_foreach_file(wchar_t* path, wchar_t* filter, void* callback, void* data);

dll_export void //
r_directory_a_foreach_file(char* path, char* filter, void* callback, void* data);

#ifdef __cplusplus
}
#endif