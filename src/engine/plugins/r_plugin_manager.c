#include "engine/core/r_core_types.h"
#include "engine/string/r_string.h"
#include "engine/io/r_directory.h"
#include "engine/io/r_path.h"
#include "r_plugin_manager.h"
#include "r_plugin_loader.h"
#include "r_plugin.h"

// important: remove this!
#include <stdio.h>
#include <string.h>

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

internal void //
r_plugin_manager_load_plugin(r_file_info_w_t file_info, r_plugin_manager_t* this) {

  void* plugin_handle = r_plugin_loader_load_plugin(file_info.full_name);
  char plugin_file_name[MAX_FILE_NAME_LENGTH] = {0};
  char plugin_name[MAX_FILE_NAME_LENGTH - 4] = {0};

  r_string_to_ansi(file_info.name, plugin_file_name, MAX_FILE_NAME_LENGTH);
  r_path_a_get_file_name_without_extension(plugin_file_name, plugin_name);

  char load_function_name[MAX_FILE_NAME_LENGTH] = {"load_"};
  strcat(load_function_name, plugin_name);

  R_PLUGIN_LOAD load_function =
      (R_PLUGIN_LOAD)r_plugin_loader_fn(plugin_handle, load_function_name);

  r_plugin_t* plugin = load_function(&r_plugin_loader_fn, this->memory, plugin_handle);
  sprintf(plugin->name, "%s", plugin_name);

  r_string_to_ansi(file_info.full_name, plugin->file_name, MAX_FILE_NAME_LENGTH);
  r_plugin_manager_add_plugin(this, plugin);
}

void //
r_plugin_manager_init(r_plugin_manager_t* this) {

  r_directory_w_foreach_file(L".\\plugins", L"*.dll", (void*)r_plugin_manager_load_plugin, this);

  for (int i = 0; i < this->init_count; ++i) {
    u8 index = this->init[i];
    r_plugin_t* plugin = this->plugins[index];
    plugin->init(plugin->state_addr, (R_PLUGIN_MANAGER_FIND_PLUGIN)&r_plugin_manager_find_plugin, this);
  }
}

r_plugin_manager_t* //
r_plugin_manager_create(r_memory_t* memory) {
  return NULL;
}

void //
r_plugin_manager_add_plugin(r_plugin_manager_t* this, r_plugin_t* plugin) {
  assert(this != NULL && plugin != NULL);

  this->plugins[this->plugin_count] = plugin;

  if (plugin->init)
    this->init[this->init_count++] = this->plugin_count;

  if (plugin->input)
    this->input[this->input_count++] = this->plugin_count;

  if (plugin->update)
    this->update[this->update_count++] = this->plugin_count;

  if (plugin->render)
    this->render[this->render_count++] = this->plugin_count;

  if (plugin->unload)
    this->unload[this->unload_count++] = this->plugin_count;

  if (plugin->destroy)
    this->destroy[this->destroy_count++] = this->plugin_count;

  this->plugin_count++;
  // if (plugin->init)
  //   this->init[this->init_count++] = (void*)plugin->init;

  // if (plugin->input)
  //   this->input[this->input_count++] = (void*)plugin->input;

  // if (plugin->update)
  //   this->update[this->update_count++] = (void*)plugin->update;

  // if (plugin->render)
  //   this->render[this->render_count++] = (void*)plugin->render;

  // if (plugin->unload)
  //   this->unload[this->unload_count++] = (void*)plugin->unload;

  // if (plugin->destroy)
  //   this->destroy[this->destroy_count++] = (void*)plugin->destroy;
}

void //
r_plugin_manager_remove_plugin(r_plugin_manager_t* this, r_plugin_t* plugin) {
  return;
}

r_plugin_t* //
r_plugin_manager_find_plugin(r_plugin_manager_t* this, const char* name) {
  r_plugin_t* plugin = NULL;

  for (u32 i = 0; i < this->plugin_count; ++i) {
    if (!r_string_cmp(this->plugins[i]->name, name)) {
      plugin = this->plugins[i];
      break;
    }
  }

  assert(plugin != NULL);
  return plugin;
}