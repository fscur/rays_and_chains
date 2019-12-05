#include "r_logger_output.h"
#include "engine\diagnostics\r_logger_i.h"
#include "engine\diagnostics\r_logger.h"
#include "engine\app\r_api_db_i.h"
#include "engine\app\r_api_db.h"

#include "r_logger_output_impl.c"

u32 //
r_logger_output_get_id(void) {
  return R_LOGGER_OUTPUT_API_ID;
}

size_t //
r_logger_output_get_size(void) {
  return sizeof(r_logger_t);
}

void //
r_logger_output_load(r_lib_load_info_t* load_info) {
  r_lib_t* lib = (r_lib_t*)load_info->lib_memory_addr;
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "r_logger_output_init");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "r_logger_output_destroy");
}

dll_export void //
r_logger_output_init(r_logger_t* this, r_api_db_i* api_db) {
  local r_logger_i debug_api;

  debug_api.instance = this;
  debug_api.print_test = &r_logger_output_print_test;
  api_db->add(api_db->instance, R_LOGGER_OUTPUT_API_ID, R_LOGGER_OUTPUT_API_NAME, &debug_api);
}

dll_export void //
r_logger_output_destroy(r_logger_t* this) {}