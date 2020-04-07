#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_LOGGER_OUTPUTSTRING_DEVICE_API_NAME "r_logger_outputstring_device"

typedef struct r_lib_load_info_t r_lib_load_info_t;
typedef struct r_logger_outputstring_device_i r_logger_outputstring_device_i;
typedef struct r_logger_device_i r_logger_device_i;

typedef struct r_logger_outputstring_device_i {
  size_t (*get_size)(void);
  char* (*get_api_name)(void);
  void (*init)(r_api_db_i* db);
  void (*destroy)(void* state);
  r_logger_device_i* (*create)(void);
} r_logger_outputstring_device_i;

#ifdef __cplusplus
}
#endif