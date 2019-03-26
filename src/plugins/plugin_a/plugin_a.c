#include <stdio.h>
#include "plugin_a.h"
#include "engine/plugins/r_plugin_loader.h"
#include "engine/plugins/r_plugin.h"
#include "engine/diagnostics/r_debug.h"

u32 //
get_id_plugin_a() {
  return 256;
}

size_t //
get_size_plugin_a() {
  return sizeof(plugin_a_api_t) + sizeof(r_plugin_t) + sizeof(plugin_a_t);
}

r_plugin_t* //
load_plugin_a(R_PLUGIN_LOADER_FN fn, void* memory_addr, void* handle) {
  plugin_a_t* state = (plugin_a_t*)memory_addr;
  r_plugin_t* plugin = (r_plugin_t*)((char*)state + sizeof(plugin_a_t));
  plugin_a_api_t* api = (plugin_a_api_t*)((char*)plugin + sizeof(r_plugin_t));

  api->handle = handle;
  api->init = (R_PLUGIN_INIT)fn(handle, "plugin_a_init");
  api->update = (R_PLUGIN_UPDATE)fn(handle, "plugin_a_update");
  api->add = (ADDFN)fn(handle, "plugin_a_add");
  api->sub = (SUBFN)fn(handle, "plugin_a_sub");
  api->mul = (MULFN)fn(handle, "plugin_a_mul");
  api->div = (DIVFN)fn(handle, "plugin_a_div");

  plugin->handle = handle;
  plugin->api = api;
  plugin->state_addr = state;
  plugin->init = (R_PLUGIN_INIT)api->init;
  plugin->update = (R_PLUGIN_UPDATE)api->update;

  return plugin;
}

void //
plugin_a_init(plugin_a_t* plugin_a,
              R_APP_FIND_API find_api_function,
              r_app_api_register_t* api_register) {

  plugin_a->debug = find_api_function(api_register, 0);
  ;
  plugin_a->debug->print("CARALEEEEOOO");
}

void //
plugin_a_update(plugin_a_t* plugin_a, f64 dt) {
  int a = 8;
  int b = 2;
  int c = 5;
  int d = a + b + c;

  plugin_a->debug->print("update: %d", d);
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