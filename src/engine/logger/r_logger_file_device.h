#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

global char R_LOGGER_FILE_DEVICE_FILENAME[R_LONG_STRING_LENGTH] = "log.log";
global FILE* log_file = NULL;

void //
r_logger_file_device_print(const char* msg);

void //
r_logger_file_device_set_filename(const char* msg);

void //
r_logger_file_open();

void //
r_logger_file_close();

#ifdef __cplusplus
}
#endif