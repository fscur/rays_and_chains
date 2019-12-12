#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_LOGGER_FILE_DEVICE_API_ID 7
#define R_LOGGER_FILE_DEVICE_API_NAME "r_logger_file_device"

typedef void (*R_LOGGER_DEVICE_PRINT)(const char* msg);
typedef void (*R_LOGGER_FILE_DEVICE_SET_FILENAME)(const char* filename);

typedef struct r_logger_file_device_i {
  R_LOGGER_DEVICE_PRINT print;
  R_LOGGER_FILE_DEVICE_SET_FILENAME set_filename;
} r_logger_file_device_i;

#ifdef __cplusplus
}
#endif