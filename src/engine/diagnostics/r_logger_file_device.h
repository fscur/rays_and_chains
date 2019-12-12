#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

global char R_LOGGER_FILE_DEVICE_FILE_NAME[LONG_STRING_LENGTH] = "log.log";

void //
r_logger_file_device_print(const char* msg);

void //
r_logger_file_device_set_filename(const char* msg);

#ifdef __cplusplus
}
#endif