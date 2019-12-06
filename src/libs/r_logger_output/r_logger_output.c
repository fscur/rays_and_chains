#include "r_logger_output.h"

u32 //
r_logger_output_get_id(void) {
  return R_LOGGER_OUTPUT_API_ID;
}

size_t //
r_logger_output_get_size(void) {
  return 0;
}

void //
r_logger_output_load(r_lib_load_info_t* load_info) {
  r_lib_t* lib = (r_lib_t*)load_info->lib_memory_addr;
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "r_logger_output_init");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "r_logger_output_destroy");
}

void //
r_logger_output_destroy(void* this) {}