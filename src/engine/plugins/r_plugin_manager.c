#include "engine/core/r_core_types.h"
#include "engine/string/r_string.h"
#include "engine/io/r_directory.h"
#include "engine/io/r_path.h"
#include "engine/io/r_file.h"
#include "engine/memory/r_memory_block.h"
#include "r_plugin_manager.h"
#include "r_plugin_loader.h"
#include "r_plugin.h"

#include <stdio.h>
internal void //
r_plugin_manager_load_plugin(r_file_info_a_t file_info, r_plugin_manager_t* this) {

  r_plugin_t* plugin =
      r_plugin_loader_load_plugin(this->memory, this->plugins, file_info.full_name);

  r_plugin_manager_add_plugin(this, plugin);
}

void //
r_plugin_manager_init(r_plugin_manager_t* this) {
  r_directory_a_foreach_file(".\\plugins", "*.dll", (void*)r_plugin_manager_load_plugin, this);
}

void //
r_plugin_manager_reload_plugins(r_plugin_manager_t* this) {
  for (u8 i = 0; i < this->plugin_count; ++i) {
    if (r_plugin_manager_should_reload(this, &this->plugins[i])) {
      r_plugin_manager_destroy_plugin(this, &this->plugins[i]);
      r_plugin_manager_reload_plugin(this, &this->plugins[i]);
      this->reloaded_plugins[this->reloaded_count++] = i;
    }
  }
}

void //
r_plugin_manager_destroy_plugin(r_plugin_manager_t* this, r_plugin_t* plugin) {
  r_plugin_loader_destroy_plugin(plugin);
}

void //
r_plugin_manager_reload_plugin(r_plugin_manager_t* this, r_plugin_t* plugin) {
  r_plugin_loader_reload_plugin(this->memory, plugin);
}

void //
r_plugin_manager_add_plugin(r_plugin_manager_t* this, r_plugin_t* plugin) {
  assert(this != NULL && plugin != NULL);

  if (plugin->init)
    this->init[this->init_count++] = this->plugin_count;

  if (plugin->input)
    this->input[this->input_count++] = this->plugin_count;

  if (plugin->update)
    this->update[this->update_count++] = this->plugin_count;

  if (plugin->render)
    this->render[this->render_count++] = this->plugin_count;

  if (plugin->destroy)
    this->destroy[this->destroy_count++] = this->plugin_count;

  this->plugin_count++;
}

void //
r_plugin_manager_remove_plugin(r_plugin_manager_t* this, r_plugin_t* plugin) {}

r_plugin_t* //
r_plugin_manager_find_plugin(r_plugin_manager_t* this, const char* name) {
  r_plugin_t* plugin = NULL;

  for (u32 i = 0; i < this->plugin_count; ++i) {
    if (!r_string_cmp(this->plugins[i].name, name)) {
      plugin = &this->plugins[i];
      break;
    }
  }

  assert(plugin != NULL);
  return plugin;
}