#include "r_logger_outputstring_device.h"

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
  lib->functions[lib->fn_count++] =
      load_info->fn(load_info->handle, "r_logger_outputstring_device_init");
  lib->functions[lib->fn_count++] =
      load_info->fn(load_info->handle, "r_logger_outputstring_device_destroy");
}

void //
r_logger_outputstring_device_destroy(void* this) {}