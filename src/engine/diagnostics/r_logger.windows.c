#include <windows.h>
#include <stdio.h>
#include "r_logger.c"
#include "r_logger_device_i.h"

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
          logger->frame_info->frame_count,
          logger->frame_info->now / 1000.0f,
          msg);

  for (i8 i = 0; i < logger->device_count; ++i) {
    logger->devices[i]->debug(output);
  }

  // freopen(R_LOGGER_LOG_FILENAME, "a+", stdout);
  // printf(msg);
  // fclose(stdout);

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
          logger->frame_info->frame_count,
          logger->frame_info->now / 1000.0f,
          msg);

  for (i8 i = 0; i < R_LOGGER_MAX_DEVICES; ++i) {
    logger->devices[i]->warn(output);
  }

  // freopen(R_LOGGER_LOG_FILENAME, "a+", stdout);
  // printf(msg);
  // fclose(stdout);
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
          logger->frame_info->frame_count,
          logger->frame_info->now / 1000.0f,
          msg);

  for (i8 i = 0; i < R_LOGGER_MAX_DEVICES; ++i) {
    logger->devices[i]->error(output);
  }

  // freopen(R_LOGGER_LOG_FILENAME, "a+", stdout);
  // printf(msg);
  // fclose(stdout);
}