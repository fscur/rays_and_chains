#include "hammer.h"
#include "engine/app/r_app.h"

u32 //
get_id_hammer() {
  return 0;
}

size_t //
get_size_hammer() {
  return sizeof(hammer_t);
}

void //
load_hammer(r_lib_load_info_t* load_info) {
  r_lib_t* lib = (r_lib_t*)load_info->lib_memory_addr;
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "hammer_init");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "hammer_run");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "hammer_destroy");
}