#include "sandbox.h"
#include "engine/app/r_app.h"

u32 //
get_id_sandbox() {
  return 0;
}

size_t //
get_size_sandbox() {
  return sizeof(sandbox_t);
}

void //
load_sandbox(r_lib_load_info_t* load_info) {
  r_lib_t* lib = (r_lib_t*)load_info->lib_memory_addr;
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "sandbox_init");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "sandbox_run");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "sandbox_destroy");
}