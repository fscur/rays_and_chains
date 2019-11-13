#include "engine/plugins/r_plugin.h"
#include "r_ui_imgui.h"

u32 //
r_ui_imgui_get_id(void) {
  return R_UI_RENDERER_IMGUI_API_ID;
}

size_t //
r_ui_imgui_get_size(void) {
  return sizeof(r_ui_renderer_t);
}

void //
r_ui_imgui_load(r_lib_load_info_t* load_info) {
  r_lib_t* lib = (r_lib_t*)load_info->lib_memory_addr;
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "r_ui_imgui_init");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "r_ui_imgui_destroy");
}