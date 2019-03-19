#include <stdio.h>
#include "plugin_b.h"
#include "engine/plugins/r_plugin_loader.h"
#include "engine/plugins/r_plugin_manager.h"
#include "engine/memory/r_memory.h"
#include "engine/memory/r_memory_arena.h"
#include "plugins/plugin_a/plugin_a.h"
#include "engine/plugins/r_plugin.h"

r_plugin_t* //
load_plugin_b(r_memory_t* memory, void* handle) {
  local r_plugin_t plugin = {0};

  size_t total_memory = sizeof(plugin_b_api_t) + sizeof(plugin_b_t);
  r_memory_arena_t* memory_arena = r_memory_add_arena(memory, total_memory);
  plugin_b_api_t* api = R_MEMORY_ARENA_PUSH_STRUCT(memory_arena, plugin_b_api_t);
  plugin_b_t* state = R_MEMORY_ARENA_PUSH_STRUCT(memory_arena, plugin_b_t);

  api->handle = handle;
  api->init = (PLBINITFN)r_plugin_loader_fn(handle, "plugin_b_init");
  api->update = (PLBUPDATEFN)r_plugin_loader_fn(handle, "plugin_b_update");
  api->print_sum = (PRINTSUMFN)r_plugin_loader_fn(handle, "plugin_b_print_sum");

  plugin.api = api;
  plugin.state_addr = state;
  plugin.memory_size = total_memory;
  plugin.init = (PLUGINAINITFN)api->init;
  plugin.update = (PLUGINAUPDATEFN)api->update;

  return &plugin;
}

void
plugin_b_init(plugin_b_t* plugin_b, r_plugin_manager_t* plugin_manager) {
  plugin_b->plugin_a_api = r_plugin_manager_find(plugin_manager, PLUGIN_A_NAME)->api;
}

void
plugin_b_update(plugin_b_t* plugin_b, f64 dt) {
  plugin_b_print_sum(plugin_b, 2, 4);
}

void
plugin_b_print_sum(plugin_b_t* plugin_b, i32 a, i32 b) {
  plugin_a_api_t* api = plugin_b->plugin_a_api;
  printf("%d + %d = %d", a, b, api->add(a, b));
}