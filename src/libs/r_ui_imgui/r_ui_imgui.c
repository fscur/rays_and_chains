#include "engine/plugins/r_plugin.h"
#include "r_ui_imgui.h"

u32 //
get_id_r_ui_imgui() {
  return IMGUI_API_ID;
}

size_t //
get_size_r_ui_imgui() {
  return sizeof(imgui_t);
}

void //
load_r_ui_imgui(r_lib_load_info_t* load_info) {
  r_lib_t* lib = (r_lib_t*)load_info->lib_memory_addr;
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "imgui_init");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "imgui_destroy");
}