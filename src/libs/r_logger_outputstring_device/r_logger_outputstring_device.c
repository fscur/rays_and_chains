#include "engine/logger/r_logger_device_i.h"
#include "engine/logger/r_logger_i.h"
#include "engine/logger/r_logger.h"
#include "engine/app/r_api_db_i.h"
#include "engine/app/r_api_db.h"
#include "engine/lib/r_lib.h"
#include "r_logger_outputstring_device_i.h"
#include "r_logger_outputstring_device.h"
#include "r_logger_outputstring_device.impl.h"

#include <stdlib.h>

internal void //
r_logger_outputstring_device_init(r_logger_outputstring_device_i* api, r_api_db_i* api_db) {}

internal void //
r_logger_outputstring_device_destroy(void* this) {}

r_logger_device_i* //
r_logger_outputstring_device_create(void) {
  r_logger_device_i* device = calloc(1, sizeof(r_logger_device_i));
  device->print = &r_logger_outputstring_device_print;
  return device;
}

size_t //
r_logger_outputstring_device_get_size(void) {
  return 0;
}

char* //
r_logger_outputstring_device_get_api_name(void) {
  return R_LOGGER_OUTPUTSTRING_DEVICE_API_NAME;
}

size_t //
r_logger_outputstring_device_get_api_size(void) {
  return sizeof(r_logger_outputstring_device_i);
}

void //
r_logger_outputstring_device_load(r_lib_load_info_t* load_info) {

  r_logger_outputstring_device_i* api = (r_logger_outputstring_device_i*)load_info->api_memory_addr;
  api->get_api_name = &r_logger_outputstring_device_get_api_name;
  api->init = &r_logger_outputstring_device_init;
  api->destroy = &r_logger_outputstring_device_destroy;
  api->create = &r_logger_outputstring_device_create;
}