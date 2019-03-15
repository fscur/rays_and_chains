#include "engine/core/r_core_types.h"
#include "r_plugin_manager.h"

// r_plugin_manager_api_t //
// load_plugin_manager_api() {
//   r_plugin_manager_api_t api = {0};
//   api.handle = r_plugin_loader_load_plugin(R_PLUGIN_MANAGER_API);
//   api.create = (R_PLUGIN_MANAGER_CREATE)r_plugin_loader_fn(api.handle,
//   R_PLUGIN_MANAGER_API_CREATE); api.add = (R_PLUGIN_MANAGER_ADD)r_plugin_loader_fn(api.handle,
//   R_PLUGIN_MANAGER_API_ADD); api.remove = (R_PLUGIN_MANAGER_REMOVE)r_plugin_loader_fn(api.handle,
//   R_PLUGIN_MANAGER_API_REMOVE); api.find = (R_PLUGIN_MANAGER_FIND)r_plugin_loader_fn(api.handle,
//   R_PLUGIN_MANAGER_API_FIND); return api;
// }

void //
r_plugin_manager_add(r_plugin_manager_t* state,
                     char* file_name,
                     void* plugin_handle,
                     size_t memory_size) {

  // u8 index = state->plugin_count++;
  // state->plugins[index].file_name = file_name;
  // state->plugins[index].handle = plugin_handle;
  // state->plugins[index].state_addr = state->memory->current_addr;
  // state->plugins[index].memory_size = memory_size;
}

void //
r_plugin_manager_remove(r_plugin_manager_t* state, void* api) {
  return;
}

void* //
r_plugin_manager_find(r_plugin_manager_t* state, char* file_name) {
  return NULL;
}