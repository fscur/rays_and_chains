#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_LOGGER_API_NAME "r_logger"

typedef struct r_logger_t r_logger_t;
typedef struct r_logger_device_i r_logger_device_i;

typedef void (*R_LOGGER_ADD_DEVICE)(const r_logger_device_i* device);
typedef void (*R_LOGGER_DEBUG)(const char* format, ...);
typedef void (*R_LOGGER_WARN)(const char* format, ...);
typedef void (*R_LOGGER_ERROR)(const char* format, ...);
typedef void (*R_LOGGER_FATAL)(const char* format, ...);

typedef struct r_logger_i {
  R_LOGGER_ADD_DEVICE add_device;
  R_LOGGER_DEBUG debug;
  R_LOGGER_WARN warn;
  R_LOGGER_ERROR error;
  R_LOGGER_FATAL fatal;
} r_logger_i;

#ifdef __cplusplus
}
#endif