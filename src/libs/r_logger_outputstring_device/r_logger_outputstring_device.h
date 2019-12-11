#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_api_db_i r_api_db_i;

#define R_LOGGER_OUTPUTSTRING_DEVICE_API_ID 259
#define R_LOGGER_OUTPUTSTRING_DEVICE_API_NAME "r_logger_outputstring_device"

dll_export void //
r_logger_outputstring_device_load(r_lib_load_info_t* load_info);

dll_export size_t //
r_logger_outputstring_device_get_size();

dll_export u32 //
r_logger_outputstring_device_get_id();

dll_export void //
r_logger_outputstring_device_init(void* this, r_api_db_i* api_db);

dll_export void //
r_logger_outputstring_device_destroy(void* this);

#ifdef __cplusplus
}
#endif