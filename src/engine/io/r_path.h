#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

dll_export void //
r_path_a_get_filename_without_extension(char* path, char* file_name);

dll_export void //
r_path_get_file_extension(const char* path, char* extension);

#ifdef __cplusplus
}
#endif