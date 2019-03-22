#include "engine/core/r_core_types.h"
#include "engine/string/r_string.h"
#include "engine/io/r_directory.h"
#include "engine/io/r_path.h"
#include "engine/io/r_file.h"
#include "r_plugin_manager.h"
#include "r_plugin_loader.h"
#include "r_plugin.h"

#include <stdio.h>

internal void //
r_plugin_manager_load_plugin(r_file_info_a_t file_info, r_plugin_manager_t* this) {
  r_plugin_t* plugin = r_plugin_loader_load_plugin(this->memory, file_info.full_name);
  r_plugin_manager_add_plugin(this, plugin);
}

void //
r_plugin_manager_init(r_plugin_manager_t* this) {
  r_directory_a_foreach_file(".\\plugins", "*.dll", (void*)r_plugin_manager_load_plugin, this);

  for (int i = 0; i < this->init_count; ++i) {
    u8 index = this->init[i];
    r_plugin_t* plugin = this->plugins[index];
    plugin->init(
        plugin->state_addr, (R_PLUGIN_MANAGER_FIND_PLUGIN)&r_plugin_manager_find_plugin, this);
  }
}

r_plugin_manager_t* //
r_plugin_manager_create(r_memory_t* memory) {
  return NULL;
}

dll_export void //
r_plugin_manager_reload_plugin(r_plugin_manager_t* this, r_plugin_t* plugin) {
  r_plugin_t* new_plugin = r_plugin_loader_reload_plugin(plugin);
  printf("%s", new_plugin->name);
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
}

void //
r_plugin_manager_remove_plugin(r_plugin_manager_t* this, r_plugin_t* plugin) {}

// void //
// r_plugin_manager_insert_plugin(r_plugin_manager_t* this, r_plugin_t* plugin) {
//   for (u32 i = 0; i < this->plugin_count; ++i) {
//     if (!r_string_cmp(this->plugins[i]->name, plugin->name)) {
//       this->plugins[this->plugin_count] = plugin;
//       break;
//     }
//   }
// }

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