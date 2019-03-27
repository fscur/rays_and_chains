#include <stdio.h>

#include "engine/app/r_api_db.h"
#include "engine/plugins/r_plugin.h"
#include "engine/diagnostics/r_debug_api.h"
#include "plugins/plugin_a/plugin_a_api.h"
#include "plugin_b_api.h"
#include "plugin_b.h"

u32 //
get_id_plugin_b() {
  return PLUGIN_B_API_ID; 
}

size_t //
get_size_plugin_b() {
  return sizeof(plugin_b_api_t) + sizeof(r_plugin_t) + sizeof(plugin_b_t);
}

r_plugin_t* //
load_plugin_b(r_plugin_load_info_t* load_info) {
  size_t total_memory = sizeof(plugin_b_api_t) + sizeof(plugin_b_t);
  
  plugin_b_t* state = (plugin_b_t*)load_info->memory_addr;
  r_plugin_t* plugin = (r_plugin_t*)((char*)state + sizeof(plugin_b_t));
  plugin_b_api_t* api = (plugin_b_api_t*)((char*)plugin + sizeof(r_plugin_t));

  api->print_sum = (PLUGIN_B_PRINT_SUM_PN)load_info->fn(load_info->handle, "plugin_b_print_sum");

  plugin->api = api;
  plugin->state = state;
  plugin->memory_size = total_memory;
  plugin->init = (R_PLUGIN_INIT)load_info->fn(load_info->handle, "plugin_b_init");
  plugin->render = (R_PLUGIN_RENDER)load_info->fn(load_info->handle, "plugin_b_render");

  return plugin;
}

void //
plugin_b_init(plugin_b_t* this, r_api_db_t* api_db) {
  //this->debug_api = api_db->find_api_function(api_db, R_DEBUG_API_ID);
  //this->plugin_a_api = api_db->find_api_function(api_db, PLUGIN_A_API_ID);
  this->debug_api = api_db->apis[R_DEBUG_API_ID];
  this->plugin_a_api = api_db->apis[PLUGIN_A_API_ID];
}

void
plugin_b_render(plugin_b_t* this) {
  plugin_b_print_sum(this, 2, 4);
}

void
plugin_b_print_sum(plugin_b_t* this, i32 a, i32 b) {
  plugin_a_api_t* api = this->plugin_a_api;
  this->debug_api->print("%d + %d = %d", a, b, api->add(a, b));
}