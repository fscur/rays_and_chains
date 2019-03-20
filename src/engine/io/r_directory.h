#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_file_info_t {
  wchar_t name[256];
  wchar_t full_name[MAX_PATH];
  size_t size;
} r_file_info_t;

typedef void (*R_DIRECTORY_FOREACH_FILE_CALLBACK)(r_file_info_t file_info, void* data);

dll_export void //
r_directory_foreach_file(wchar_t* path, wchar_t* filter, void* callback, void* data);

#ifdef __cplusplus
}
#endif