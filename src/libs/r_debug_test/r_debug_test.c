#include "r_debug_test.h"
#include "engine\diagnostics\r_debug_i.h"
#include "engine\diagnostics\r_debug.h"
#include "engine\app\r_api_db_i.h"
#include "engine\app\r_api_db.h"

#include "r_debug_test_impl.c"

u32 //
r_debug_test_get_id(void) {
  return R_DEBUG_TEST_API_ID;
}

size_t //
r_debug_test_get_size(void) {
  return sizeof(r_debug_t);
}

void //
r_debug_test_load(r_lib_load_info_t* load_info){
  r_lib_t* lib = (r_lib_t*)load_info->lib_memory_addr;
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "r_debug_test_init");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "r_debug_test_destroy");
}

dll_export void //
r_debug_test_init(r_debug_t* this, r_api_db_i* api_db)
{
  local r_debug_i debug_api;
  
  debug_api.instance = this;
  debug_api.print_test = &r_debug_test_print_test;
  api_db->add(api_db->instance, R_DEBUG_TEST_API_ID, R_DEBUG_TEST_API_NAME, &debug_api);
}

dll_export void //
r_debug_test_destroy(r_debug_t* this)
{

}