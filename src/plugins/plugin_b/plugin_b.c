#include <stdio.h>
#include "plugin_b.h"
#include "engine/plugins/r_plugin_loader.h"
#include "engine/plugins/r_plugin_manager.h"
#include "engine/memory/r_memory.h"
#include "engine/memory/r_memory_arena.h"
#include "plugins/plugin_a/plugin_a.h"
#include "engine/plugins/r_plugin.h"

r_plugin_t* //
load_plugin_b(R_PLUGIN_LOADER_FN fn, r_memory_t* memory, void* handle) {
  local r_plugin_t plugin = {0};

  size_t total_memory = sizeof(plugin_b_api_t) + sizeof(plugin_b_t);
  r_memory_arena_t* memory_arena = r_memory_add_arena(memory, total_memory);
  plugin_b_api_t* api = R_MEMORY_ARENA_PUSH_STRUCT(memory_arena, plugin_b_api_t);
  plugin_b_t* state = R_MEMORY_ARENA_PUSH_STRUCT(memory_arena, plugin_b_t);

  api->handle = handle;
  api->init = (R_PLUGIN_INIT)fn(handle, "plugin_b_init");
  api->render = (R_PLUGIN_RENDER)fn(handle, "plugin_b_render");
  api->print_sum = (PRINTSUMFN)fn(handle, "plugin_b_print_sum");

  plugin.api = api;
  plugin.state_addr = state;
  plugin.memory_size = total_memory;
  plugin.init = (R_PLUGIN_INIT)api->init;
  plugin.render = (R_PLUGIN_RENDER)api->render;

  return &plugin;
}

void //
plugin_b_init(plugin_b_t* plugin_b,
              R_PLUGIN_MANAGER_FIND_PLUGIN find_plugin_fn,
              r_plugin_manager_t* plugin_manager) {
  r_plugin_t* plugin_a = find_plugin_fn(plugin_manager, PLUGIN_A_NAME);
  plugin_b->plugin_a_api = plugin_a->api;
}

void
plugin_b_render(plugin_b_t* plugin_b) {
  plugin_b_print_sum(plugin_b, 2, 4);
}

void
plugin_b_print_sum(plugin_b_t* plugin_b, i32 a, i32 b) {
  plugin_a_api_t* api = plugin_b->plugin_a_api;
  printf("%d + %d = %d", a, b, api->add(a, b));
}