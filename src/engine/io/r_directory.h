#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_file_info_w_t {
  wchar_t name[MAX_FILE_NAME_LENGTH];
  wchar_t full_name[MAX_FILE_NAME_LENGTH];
  size_t size;
} r_file_info_w_t;

typedef struct r_file_info_a_t {
  char name[MAX_FILE_NAME_LENGTH];
  char full_name[MAX_FILE_NAME_LENGTH];
  size_t size;
} r_file_info_a_t;

typedef void (*R_DIRECTORY_W_FOREACH_FILE_CALLBACK)(r_file_info_w_t file_info, void* data);
typedef void (*R_DIRECTORY_A_FOREACH_FILE_CALLBACK)(r_file_info_a_t file_info, void* data);

dll_export void //
r_directory_w_foreach_file(wchar_t* path, wchar_t* filter, void* callback, void* data);

dll_export void //
r_directory_a_foreach_file(char* path, char* filter, void* callback, void* data);

#ifdef __cplusplus
}
#endif