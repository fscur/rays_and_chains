#include <stdio.h>
#include "engine/app/r_api_db.h"
#include "engine/diagnostics/r_debug_api.h"
#include "engine/window/r_window_api.h"
#include "engine/plugins/r_plugin.h"
#include "plugin_a_api.h"
#include "plugin_a.h"

u32 //
get_id_plugin_a() {
  return PLUGIN_A_API_ID;
}

size_t //
get_size_plugin_a() {
  return sizeof(plugin_a_api_t) + sizeof(r_plugin_t) + sizeof(plugin_a_t);
}

r_plugin_t* //
load_plugin_a(r_plugin_load_info_t* load_info) {

  plugin_a_t* state = (plugin_a_t*)load_info->memory_addr;
  r_plugin_t* plugin = (r_plugin_t*)((char*)state + sizeof(plugin_a_t));
  plugin_a_api_t* api = (plugin_a_api_t*)((char*)plugin + sizeof(r_plugin_t));

  api->add = (PLUGIN_A_ADD_FN)load_info->fn(load_info->handle, "plugin_a_add");
  api->sub = (PLUGIN_A_SUB_FN)load_info->fn(load_info->handle, "plugin_a_sub");
  api->mul = (PLUGIN_A_MUL_FN)load_info->fn(load_info->handle, "plugin_a_mul");
  api->div = (PLUGIN_A_DIV_FN)load_info->fn(load_info->handle, "plugin_a_div");

  plugin->handle = load_info->handle;
  plugin->api = api;
  plugin->state = state;
  plugin->init = (R_PLUGIN_INIT)load_info->fn(load_info->handle, "plugin_a_init");
  plugin->update = (R_PLUGIN_UPDATE)load_info->fn(load_info->handle, "plugin_a_update");

  return plugin;
}

void //
plugin_a_init(plugin_a_t* this, r_api_db_t* api_db) {

  this->debug_api = api_db->apis[R_DEBUG_API_ID];
  this->window_api = api_db->apis[R_WINDOW_API_ID];
}

void //
plugin_a_update(plugin_a_t* this, f64 dt) {
  int a = 0;
  int b = 2;
  int c = 1;
  int d = a + b + c;

  this->debug_api->print("update: %d\n", d);
  
  this->window_api->set_title(this->window_api->window, L"filipe");
  this->window_api->set_back_color(this->window_api->window, (r_color_t){0.0f, 0.8f, 1.0f, 1.0f});
}

i32 //
plugin_a_add(i32 a, i32 b) {
  return a + b;
}

i32 //
plugin_a_sub(i32 a, i32 b) {
  return a - b;
}

i32
plugin_a_mul(i32 a, i32 b) {
  return a * b;
}

i32 //
plugin_a_div(i32 a, i32 b) {
  return a / b;
}