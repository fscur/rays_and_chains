#include "engine/plugins/r_plugin.h"
#include "glfw.h"

u32 //
get_id_glfw() {
  return GLFW_API_ID;
}

size_t //
get_size_glfw() {
  return sizeof(glfw_t);
}

r_plugin_t* //
load_glfw(r_plugin_load_info_t* load_info) {

  r_plugin_t* plugin = (r_plugin_t*)load_info->plugin_addr;
  glfw_t* state = (glfw_t*)load_info->memory_addr;

  plugin->handle = load_info->handle;
  plugin->api = NULL;
  plugin->state = state;

  plugin->init = (R_PLUGIN_INIT)load_info->fn(load_info->handle, "glfw_init");
  plugin->input = (R_PLUGIN_INPUT)load_info->fn(load_info->handle, "glfw_input");
  plugin->update = (R_PLUGIN_UPDATE)load_info->fn(load_info->handle, "glfw_update");
  plugin->render = (R_PLUGIN_RENDER)load_info->fn(load_info->handle, "glfw_render");
  plugin->destroy = (R_PLUGIN_DESTROY)load_info->fn(load_info->handle, "glfw_destroy");

  return plugin;
}