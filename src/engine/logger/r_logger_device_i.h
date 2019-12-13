#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef void (*R_LOGGER_DEVICE_PRINT)(const char* msg);

typedef struct r_logger_device_i {
  R_LOGGER_DEVICE_PRINT print;
} r_logger_device_i;

#ifdef __cplusplus
}
#endif