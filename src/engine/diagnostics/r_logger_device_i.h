#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef void (*R_LOGGER_DEVICE_DEBUG)(const char* msg);
typedef void (*R_LOGGER_DEVICE_WARN)(const char* msg);
typedef void (*R_LOGGER_DEVICE_ERROR)(const char* msg);

typedef struct r_logger_device_i {  
  R_LOGGER_DEVICE_DEBUG debug;
  R_LOGGER_DEVICE_WARN warn;
  R_LOGGER_DEVICE_ERROR error;
} r_logger_device_i;

#ifdef __cplusplus
}
#endif