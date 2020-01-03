#include "engine\logger\r_logger_device_i.h"
#include "engine\logger\r_logger_i.h"
#include "engine\logger\r_logger.h"
#include "engine\app\r_api_db_i.h"
#include "engine\app\r_api_db.h"

#include "r_logger_outputstring_device.h"
#include "r_logger_outputstring_device.impl.h"

size_t //
r_logger_outputstring_device_get_size(void) {
  return 0;
}

size_t //
r_logger_outputstring_device_get_api_size(void) {
  return sizeof(r_logger_device_i);
}

void //
r_logger_outputstring_device_load(r_lib_load_info_t* load_info) {
  R_LIB_LOADER_FN fn = load_info->fn;
  void* handle = load_info->handle;

  r_lib_i* lib_api = (r_lib_i*)load_info->api_memory_addr;
  lib_api->init = (R_LIB_INIT)fn(handle, "r_logger_outputstring_device_init");
  lib_api->destroy = (R_LIB_DESTROY)fn(handle, "r_logger_outputstring_device_destroy");
}

void //
r_logger_outputstring_device_init(r_logger_t* this, r_api_db_i* api_db) {
  local r_logger_device_i api;
  api.print = &r_logger_outputstring_device_print;
  api_db->add(api_db->instance, R_LOGGER_OUTPUTSTRING_DEVICE_API_NAME, &api);
}

void //
r_logger_outputstring_device_destroy(void* this) {}