#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_datetime_t r_datetime_t;

dll_export bool //
r_file_a_copy(const char* src_file_name, const char* dst_file_name);

dll_export bool //
r_file_a_get_last_modification(const char* file_name, r_datetime_t* time);

#ifdef __cplusplus
}
#endif