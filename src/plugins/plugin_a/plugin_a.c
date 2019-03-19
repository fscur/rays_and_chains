#include <stdio.h>
#include "plugin_a.h"
#include "engine/plugins/r_plugin_loader.h"
#include "engine/plugins/r_plugin.h"
#include "engine/memory/r_memory.h"
#include "engine/memory/r_memory_arena.h"

r_plugin_t* //
load_plugin_a(r_memory_t* memory, void* handle) {
  local r_plugin_t plugin = {0};

  size_t total_memory = sizeof(plugin_a_api_t);
  r_memory_arena_t* memory_arena = r_memory_add_arena(memory, total_memory);
  plugin_a_api_t* api = R_MEMORY_ARENA_PUSH_STRUCT(memory_arena, plugin_a_api_t);

  api->handle = handle;
  api->init = (PLUGINAINITFN)r_plugin_loader_fn(handle, "plugin_a_init");
  api->update = (PLUGINAUPDATEFN)r_plugin_loader_fn(handle, "plugin_a_update");
  api->add = (ADDFN)r_plugin_loader_fn(handle, "plugin_a_add");
  api->sub = (SUBFN)r_plugin_loader_fn(handle, "plugin_a_sub");
  api->mul = (MULFN)r_plugin_loader_fn(handle, "plugin_a_mul");
  api->div = (DIVFN)r_plugin_loader_fn(handle, "plugin_a_div");

  plugin.api = api;
  plugin.state_addr = memory_arena->base_addr;
  plugin.memory_size = total_memory;
  plugin.init = (PLUGINAINITFN)api->init;
  plugin.update = (PLUGINAUPDATEFN)api->update;

  return &plugin;
}

void
plugin_a_init(void* plugin_a, r_plugin_manager_t* plugin_manager) {
  printf("init");
}

void
plugin_a_update(void* plugin_a, f64 dt) {
  printf("update: %lf", dt);
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