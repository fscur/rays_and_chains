#include "engine\logger\r_logger_device_i.h"
#include "engine\logger\r_logger_i.h"
#include "engine\logger\r_logger.h"
#include "engine\app\r_api_db_i.h"
#include "engine\app\r_api_db.h"

#include "r_logger_outputstring_device.h"
#include "r_logger_outputstring_device.impl.h"

u32 //
r_logger_outputstring_device_get_id(void) {
  return R_LOGGER_OUTPUTSTRING_DEVICE_API_ID;
}

size_t //
r_logger_outputstring_device_get_size(void) {
  return 0;
}

void //
r_logger_outputstring_device_load(r_lib_load_info_t* load_info) {
  r_lib_t* lib = (r_lib_t*)load_info->lib_memory_addr;

  lib->api.init = (R_LIB_INIT)load_info->fn(load_info->handle, "r_logger_outputstring_device_init");
  lib->api.destroy = (R_LIB_DESTROY)load_info->fn(load_info->handle, "r_logger_outputstring_device_destroy");
}

void //
r_logger_outputstring_device_init(r_logger_t* this, r_api_db_i* api_db) {
  local r_logger_device_i api;
  api.print = &r_logger_outputstring_device_print;
  api_db->add(api_db->instance,
              R_LOGGER_OUTPUTSTRING_DEVICE_API_ID,
              R_LOGGER_OUTPUTSTRING_DEVICE_API_NAME,
              &api);
}

void //
r_logger_outputstring_device_destroy(void* this) {}