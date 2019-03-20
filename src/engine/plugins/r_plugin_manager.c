#include "engine/core/r_core_types.h"
#include "engine/string/r_string.h"
#include "r_plugin_manager.h"
#include "r_plugin_loader.h"
#include "r_plugin.h"

r_plugin_manager_api_t //
load_plugin_manager_api() {
  r_plugin_manager_api_t api = {0};
  api.handle = r_plugin_loader_load_plugin(R_PLUGIN_MANAGER_API);
  api.create = (R_PLUGIN_MANAGER_CREATE)r_plugin_loader_fn(api.handle, R_PLUGIN_MANAGER_API_CREATE);
  api.add_plugin =
      (R_PLUGIN_MANAGER_ADD_PLUGIN)r_plugin_loader_fn(api.handle, R_PLUGIN_MANAGER_API_ADD_PLUGIN);
  api.remove_plugin = (R_PLUGIN_MANAGER_REMOVE_PLUGIN)r_plugin_loader_fn(
      api.handle, R_PLUGIN_MANAGER_API_REMOVE_PLUGIN);
  api.find_plugin = (R_PLUGIN_MANAGER_FIND_PLUGIN)r_plugin_loader_fn(
      api.handle, R_PLUGIN_MANAGER_API_FIND_PLUGIN);
  return api;
}

void //
r_plugin_manager_add_plugin(r_plugin_manager_t* state, r_plugin_t* plugin) {
  assert(state != NULL && plugin != NULL);

  state->plugins[state->plugin_count++] = plugin;

  if (plugin->init)
    state->init[state->init_count++] = (void*)plugin->init;

  if (plugin->input)
    state->input[state->input_count++] = (void*)plugin->input;

  if (plugin->update)
    state->update[state->update_count++] = (void*)plugin->update;

  if (plugin->render)
    state->render[state->render_count++] = (void*)plugin->render;

  if (plugin->unload)
    state->unload[state->unload_count++] = (void*)plugin->unload;

  if (plugin->destroy)
    state->destroy[state->destroy_count++] = (void*)plugin->destroy;
}

void //
r_plugin_manager_remove_plugin(r_plugin_manager_t* state, r_plugin_t* plugin) {
  return;
}

r_plugin_t* //
r_plugin_manager_find_plugin(r_plugin_manager_t* state, const wchar_t* file_name) {
  r_plugin_t* plugin = NULL;
  for (u32 i = 0; i < state->plugin_count; ++i)
    if (!r_string_wcmp(state->plugins[i]->file_name, file_name)) {
      plugin = state->plugins[i];
      break;
    }

  assert(plugin != NULL);
  return plugin;
}