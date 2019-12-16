#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_LOGGER_MAX_DEVICES 2

typedef struct r_logger_device_i r_logger_device_i;
typedef struct r_logger_t
{
  r_frame_info_t* frame_info;
  const r_logger_device_i* devices[R_LOGGER_MAX_DEVICES];
  u8 device_count;
} r_logger_t;

global r_logger_t* logger_instance = NULL;

void //
r_logger_create(r_frame_info_t* frame_info);

void //
r_logger_add_device(const r_logger_device_i* device);

void //
r_logger_debug(const char* format, ...);

void //
r_logger_warn(const char* format, ...);

void //
r_logger_error(const char* format, ...);

void //
r_logger_destroy();

#ifdef __cplusplus
}
#endif