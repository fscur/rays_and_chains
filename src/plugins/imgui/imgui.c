#include "engine/plugins/r_plugin.h"
#include "imgui.h"

u32 //
get_id_imgui() {
  return IMGUI_API_ID;
}

size_t //
get_size_imgui() {
  return sizeof(imgui_t);
}

r_plugin_t* //
load_imgui(r_plugin_load_info_t* load_info) {

  r_plugin_t* plugin = (r_plugin_t*)load_info->plugin_memory_addr;
  imgui_t* state = (imgui_t*)load_info->state_memory_addr;

  plugin->handle = load_info->handle;
  plugin->api = NULL;
  plugin->state = state;

  plugin->init = (R_PLUGIN_INIT)load_info->fn(load_info->handle, "imgui_init");
  plugin->destroy = (R_PLUGIN_DESTROY)load_info->fn(load_info->handle, "imgui_destroy");

  return plugin;
}