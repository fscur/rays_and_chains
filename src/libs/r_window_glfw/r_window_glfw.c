#include "engine/plugins/r_plugin.h"
#include "r_window_glfw.h"

u32 //
get_id_r_window_glfw(void) {
  return GLFW_API_ID;
}

size_t //
get_size_r_window_glfw(void) {
  return sizeof(glfw_t);
}

void //
load_r_window_glfw(r_lib_load_info_t* load_info) {
  r_lib_t* lib = (r_lib_t*)load_info->lib_memory_addr;
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "glfw_init");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "glfw_destroy");
}