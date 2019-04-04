#include "engine/plugins/r_plugin.h"
#include "sandbox.h"

u32 //
get_id_sandbox() {
  return SANDBOX_API_ID;
}

size_t //
get_size_sandbox() {
  return sizeof(sandbox_t);
}

r_plugin_t* //
load_sandbox(r_plugin_load_info_t* load_info) {

  r_plugin_t* plugin = (r_plugin_t*)load_info->plugin_addr;
  sandbox_t* state = (sandbox_t*)load_info->memory_addr;

  plugin->handle = load_info->handle;
  plugin->api = NULL;
  plugin->state = state;

  plugin->init = (R_PLUGIN_INIT)load_info->fn(load_info->handle, "sandbox_init");
  plugin->input = (R_PLUGIN_INPUT)load_info->fn(load_info->handle, "sandbox_input");
  plugin->update = (R_PLUGIN_UPDATE)load_info->fn(load_info->handle, "sandbox_update");
  plugin->render = (R_PLUGIN_RENDER)load_info->fn(load_info->handle, "sandbox_render");
  plugin->destroy = (R_PLUGIN_DESTROY)load_info->fn(load_info->handle, "sandbox_destroy");

  return plugin;
}