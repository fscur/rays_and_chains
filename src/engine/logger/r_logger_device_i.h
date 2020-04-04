#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_logger_device_i {
  void (*print)(const char* msg);
} r_logger_device_i;

#ifdef __cplusplus
}
#endif