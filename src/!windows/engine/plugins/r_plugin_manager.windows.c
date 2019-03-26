#include "engine/plugins/r_plugin_manager.c"
#include "engine/plugins/r_plugin.h"
#include "engine/time/r_time.h"
#include "engine/io/r_file.h"

bool //
r_plugin_manager_should_reload(r_plugin_manager_t* this, r_plugin_t* plugin) {
  r_time_t last_modification = {0};
  r_file_a_get_last_modification(plugin->file_name, &last_modification);
  bool a = r_time_compare(&plugin->last_modification, &last_modification) != 0;
  return a;
}