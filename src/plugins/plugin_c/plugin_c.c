#include <stdio.h>
#include "engine/app/r_api_db.h"
#include "engine/diagnostics/r_debug_api.h"
#include "engine/window/r_window_api.h"
#include "engine/plugins/r_plugin.h"
#include "plugin_c_api.h"
#include "plugin_c.h"

u32 //
get_id_plugin_c() {
  return PLUGIN_C_API_ID;
}

size_t //
get_size_plugin_c() {
  return sizeof(plugin_c_api_t) + sizeof(plugin_c_t);
}

r_plugin_t* //
load_plugin_c(r_plugin_load_info_t* load_info) {

  r_plugin_t* plugin = (r_plugin_t*)load_info->plugin_addr;
  plugin_c_t* state = (plugin_c_t*)load_info->memory_addr;
  plugin_c_api_t* api = (plugin_c_api_t*)((u8*)state + sizeof(plugin_c_t));

  api->add = (PLUGIN_C_ADD_FN)load_info->fn(load_info->handle, "plugin_c_add");
  api->sub = (PLUGIN_C_SUB_FN)load_info->fn(load_info->handle, "plugin_c_sub");

  plugin->handle = load_info->handle;
  plugin->api = api;
  plugin->state = state;

  plugin->init = (R_PLUGIN_INIT)load_info->fn(load_info->handle, "plugin_c_init");
  plugin->update = (R_PLUGIN_UPDATE)load_info->fn(load_info->handle, "plugin_c_update");

  return plugin;
}

void //
plugin_c_init(plugin_c_t* this, r_api_db_t* api_db) {

  this->debug_api = api_db->apis[R_DEBUG_API_ID];
  this->window_api = api_db->apis[R_WINDOW_API_ID];
}

void //
plugin_c_update(plugin_c_t* this, f64 dt) {
  int a = 0;
  int b = 2;
  int c = 1;
  int d = a + b + c;

  this->debug_api->print("update: %d\n", d);
}

i32 //
plugin_c_add(i32 a, i32 b) {
  return a + b;
}

i32 //
plugin_c_sub(i32 a, i32 b) {
  return a - b;
}