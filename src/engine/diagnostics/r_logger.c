#include "r_logger.h"

void //
r_logger_init(r_frame_info_t* frame_info) {
  logger = (r_logger_t*)calloc(1, sizeof(r_logger_t));
  logger->frame_info = frame_info;
}

void //
r_logger_add_device(const r_logger_device_i* device) {
  assert(logger->device_count <= R_LOGGER_MAX_DEVICES);
  logger->devices[logger->device_count++] = device;
}

void
r_logger_destroy() {
  assert(logger != NULL);
  free(logger);
  logger = NULL;
}