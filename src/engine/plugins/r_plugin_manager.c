#include "engine/core/r_core_types.h"
#include "engine/string/r_string.h"
#include "r_plugin_manager.h"
#include "r_plugin.h"

// r_plugin_manager_api_t //
// load_plugin_manager_api() {
//   r_plugin_manager_api_t api = {0};
//   api.handle = load_plugin(R_PLUGIN_MANAGER_API);
//   api.create = (R_PLUGIN_MANAGER_CREATE)fn(api.handle, R_PLUGIN_MANAGER_API_CREATE);
//   api.add = (R_PLUGIN_MANAGER_ADD)fn(api.handle, R_PLUGIN_MANAGER_API_ADD);
//   api.remove = (R_PLUGIN_MANAGER_REMOVE)fn(api.handle, R_PLUGIN_MANAGER_API_REMOVE);
//   api.find = (R_PLUGIN_MANAGER_FIND)fn(api.handle, R_PLUGIN_MANAGER_API_FIND);
//   return api;
// }

void //
r_plugin_manager_add(r_plugin_manager_t* state, r_plugin_t* plugin) {

  u8 index = state->plugin_count++;
  state->init[index] = (void*)plugin->init;
  state->update[index] = (void*)plugin->update;
  state->plugins[index] = plugin;
}

void //
r_plugin_manager_remove(r_plugin_manager_t* state, r_plugin_t* plugin) {
  return;
}

r_plugin_t* //
r_plugin_manager_find(r_plugin_manager_t* state, char* file_name) {
  r_plugin_t* plugin = NULL;
  for (u32 i = 0; i < state->plugin_count; ++i)
    if (!r_string_cmp(state->plugins[i]->file_name, file_name)) {
      plugin = state->plugins[i];
      break;
    }

  assert(plugin != NULL);
  return plugin;
}