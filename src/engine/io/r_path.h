#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

dll_export void //
r_path_a_get_file_name_without_extension(char* path, char* file_name);

#ifdef __cplusplus
}
#endif