#include <stdio.h>
#include "plugin_a.h"
#include "engine/plugins/r_plugin_loader.h"
#include "engine/plugins/r_plugin.h"

size_t get_size_plugin_a() {
  return sizeof(plugin_a_api_t) + sizeof(r_plugin_t);
}

r_plugin_t* //
load_plugin_a(R_PLUGIN_LOADER_FN fn, void* memory_addr, void* handle) {
  r_plugin_t* plugin = (r_plugin_t*)memory_addr;
  plugin_a_api_t* api = (plugin_a_api_t*)((char*)memory_addr + sizeof(r_plugin_t));

  api->handle = handle;
  api->init = (R_PLUGIN_INIT)fn(handle, "plugin_a_init");
  api->update = (R_PLUGIN_UPDATE)fn(handle, "plugin_a_update");
  api->add = (ADDFN)fn(handle, "plugin_a_add");
  api->sub = (SUBFN)fn(handle, "plugin_a_sub");
  api->mul = (MULFN)fn(handle, "plugin_a_mul");
  api->div = (DIVFN)fn(handle, "plugin_a_div");

  plugin->handle = handle;
  plugin->api = api;
  plugin->state_addr = memory_addr;
  plugin->init = (R_PLUGIN_INIT)api->init;
  plugin->update = (R_PLUGIN_UPDATE)api->update;

  return plugin;
}

void //
plugin_a_init(void* plugin_a, R_PLUGIN_MANAGER_FIND_PLUGIN find_plugin_api, r_plugin_manager_t* plugin_manager) {
  printf("init");
}

void
plugin_a_update(void* plugin_a, f64 dt) {
  int a = 1;
  int b = 2;
  int c = 3;
  int d = a+b+c;

  printf("update: %d", d);
}

i32
plugin_a_add(i32 a, i32 b) {
  return a + b;
}

i32
plugin_a_sub(i32 a, i32 b) {
  return a - b;
}

i32
plugin_a_mul(i32 a, i32 b) {
  return a * b;
}

i32
plugin_a_div(i32 a, i32 b) {
  return a / b;
}