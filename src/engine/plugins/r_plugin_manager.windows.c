#include "engine/plugins/r_plugin_manager.c"
#include "engine/plugins/r_plugin.h"
#include "engine/time/r_datetime.h"
#include "engine/io/r_file.h"

bool //
r_plugin_manager_should_reload(r_plugin_manager_t* this, r_plugin_t* plugin) {
  r_datetime_t last_modification = {0};
  if (r_file_a_get_last_modification(plugin->file_name, &last_modification))
    return r_datetime_compare(&plugin->last_modification, &last_modification) != 0;
  return false;
}