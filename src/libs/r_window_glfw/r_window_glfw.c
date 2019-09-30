#include "engine/plugins/r_plugin.h"
#include "r_window_glfw.h"

u32 //
r_window_glfw_get_id(void) {
  return GLFW_API_ID;
}

size_t //
r_window_glfw_get_size(void) {
  return sizeof(glfw_t);
}

void //
r_window_glfw_load(r_lib_load_info_t* load_info) {
  r_lib_t* lib = (r_lib_t*)load_info->lib_memory_addr;
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "r_window_glfw_init");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "r_window_glfw_destroy");
}