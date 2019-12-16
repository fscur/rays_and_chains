#include "engine/core/r_core_types.h"
#include "r_app_host.h"
#include "r_app.h"

internal bool //
r_app_host_should_reload_lib(r_lib_t* lib) {
  r_datetime_t last_modification = {0};
  if (r_file_a_get_last_modification(lib->file_name, &last_modification))
    return r_datetime_compare(&lib->last_modification, &last_modification) != 0;
  return false;
}

internal void //
r_app_host_reload_libs(r_app_host_t* this) {
  for (u8 i = 0; i < this->lib_count; ++i) {
    r_lib_t* lib = &this->libs[i];
    if (r_app_host_should_reload_lib(lib)) {
      r_lib_loader_destroy_lib(lib);
      r_lib_loader_reload_lib(lib);
      this->reloaded_libs[this->reloaded_lib_count++] = i;
    }
  }
}

internal void //
r_app_host_reload_app(r_app_host_t* this, r_app_t* app) {
  r_lib_t* lib = &app->lib;
  bool should_reload_app = r_app_host_should_reload_lib(lib);

  if (should_reload_app) {
    r_app_i* app_api = (r_app_i*)lib->api;
    app_api->destroy(app);
    r_lib_loader_reload_lib(lib);
    app_api->init(this->app, this->api_db_api);
  }
}

void //
r_app_host_reload(r_app_host_t* this) {

  r_app_host_reload_libs(this);

  for (u32 i = 0; i < this->reloaded_lib_count; ++i) {
    u8 index = this->reloaded_libs[i];
    r_lib_t lib = this->libs[index];
    r_lib_i* lib_api = (r_lib_i*)lib.api;
    lib_api->init(lib.state, this->api_db_api);
  }

  this->reloaded_lib_count = 0;

  r_app_host_reload_app(this, this->app);
}