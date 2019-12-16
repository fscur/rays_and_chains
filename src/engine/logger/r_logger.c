#include <stdio.h>
#include "r_logger.h"
#include "r_logger_device_i.h"

void //
r_logger_create(r_frame_info_t* frame_info) {
  logger_instance = (r_logger_t*)calloc(1, sizeof(r_logger_t));
  logger_instance->frame_info = frame_info;
}

void //
r_logger_add_device(const r_logger_device_i* device) {
  assert(logger_instance->device_count <= R_LOGGER_MAX_DEVICES);
  logger_instance->devices[logger_instance->device_count++] = device;
}

internal void //
r_logger_print(const char* msg) {
  for (i8 i = 0; i < logger_instance->device_count; ++i) {
    logger_instance->devices[i]->print(msg);
  }
}

void //
r_logger_debug(const char* format, ...) {
#if _DEBUG
  char msg[1024] = {0};
  va_list vl;
  va_start(vl, format);
  vsprintf(msg, format, vl);
  va_end(vl);

  char output[2048] = {0};
  sprintf(output,
          "[%010I64d][%08.3f][DEBUG] %s\n",
          logger_instance->frame_info->frame_count,
          logger_instance->frame_info->now / 1000.0f,
          msg);

  r_logger_print(output);

#endif
}

void //
r_logger_warn(const char* format, ...) {
  char msg[1024] = {0};
  va_list vl;
  va_start(vl, format);
  vsprintf(msg, format, vl);
  va_end(vl);

  char output[2048] = {0};
  sprintf(output,
          "[%010I64d][%08.3f][WARN] %s\n",
          logger_instance->frame_info->frame_count,
          logger_instance->frame_info->now / 1000.0f,
          msg);

  r_logger_print(output);
}

void //
r_logger_error(const char* format, ...) {
  char msg[1024] = {0};
  va_list vl;
  va_start(vl, format);
  vsprintf(msg, format, vl);
  va_end(vl);

  char output[2048] = {0};
  sprintf(output,
          "[%010I64d][%08.3f][ERROR] %s\n",
          logger_instance->frame_info->frame_count,
          logger_instance->frame_info->now / 1000.0f,
          msg);

  r_logger_print(output);
}

void
r_logger_destroy() {
  assert(logger_instance != NULL);
  free(logger_instance);
  logger_instance = NULL;
}