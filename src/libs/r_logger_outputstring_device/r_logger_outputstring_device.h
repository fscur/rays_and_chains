#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_lib_load_info_t r_lib_load_info_t;

dll_export void //
r_logger_outputstring_device_load(r_lib_load_info_t* load_info);

dll_export size_t //
r_logger_outputstring_device_get_api_size(void);

dll_export size_t //
r_logger_outputstring_device_get_size(void);

#ifdef __cplusplus
}
#endif