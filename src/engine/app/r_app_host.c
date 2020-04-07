#include "engine/time/r_datetime.h"
#include "engine/io/r_file.h"
#include "engine/io/r_file_info.h"

#include "engine/logger/r_logger.h"
#include "engine/logger/r_logger_i.h"
#include "engine/logger/r_logger_device_i.h"
#include "engine/logger/r_logger_file_device.h"
#include "engine/logger/r_logger_file_device_i.h"

#include "engine/window/r_window.h"
#include "engine/window/r_window_i.h"

#include "engine/string/r_string.h"
#include "engine/string/r_string_i.h"

#include "engine/ui/r_ui.h"
#include "engine/ui/r_ui_i.h"

#include "r_api_db.h"
#include "r_app.h"
#include "r_app_i.h"
#include "r_api_db_i.h"
#include "r_app_host.h"
#include "r_app_host_reload.c"

internal size_t //
r_app_host_get_apis_size() {
  return                               //
      sizeof(r_logger_i) +             //
      sizeof(r_logger_file_device_i) + //
      sizeof(r_string_i) + //
      sizeof(r_window_i) + //
      sizeof(r_ui_i);
}

size_t //
r_app_host_get_size(void) {
  return sizeof(r_app_host_t) +       //
         sizeof(r_api_db_t) +         //
         r_app_host_get_apis_size() + //
         sizeof(r_lib_t) * R_MAX_LIB_COUNT;
}

internal void //
r_app_host_load_lib(r_file_info_a_t file_info, r_app_host_t* this) {
  r_lib_t* lib = r_lib_loader_load_lib(this->memory, file_info.full_name);
  r_lib_i* api = lib->api;
  r_api_db_add(this->api_db, api->get_api_name(), api);
  this->libs[this->lib_count++] = *lib;
}

internal void //
r_app_host_load_libs(r_app_host_t* this) {
  r_directory_a_foreach_file(this->libs_path, R_LIBS_EXTENSION, (void*)r_app_host_load_lib, this);
}

internal void //
r_app_host_init_apis(r_app_host_t* this) {
  size_t total_apis_size = r_app_host_get_apis_size();
  r_memory_arena_t* apis_arena = r_memory_add_arena(this->memory, total_apis_size);
  
  r_logger_register_api(this->api_db, apis_arena);
  r_logger_file_device_register_api(this->api_db, apis_arena);
  r_string_register_api(this->api_db, apis_arena);
  r_window_register_api(this->api_db, apis_arena);
  r_ui_register_api(this->api_db, apis_arena);
  r_gfx_renderer_register_api(this->api_db, apis_arena);

  local r_api_db_i api_db_api = {0};
  api_db_api.add = &r_api_db_add;
  api_db_api.find_by_name = &r_api_db_find_by_name;
  this->api_db_api = &api_db_api;
  this->api_db_api->instance = this->api_db;
}

r_app_host_t* //
r_app_host_create(r_memory_t* memory, r_frame_info_t* frame_info) {
  size_t total_memory = r_app_host_get_size();
  r_memory_arena_t* memory_arena = r_memory_add_arena(memory, total_memory);
  r_app_host_t* this = r_memory_arena_push_struct(memory_arena, r_app_host_t);
  this->api_db = r_api_db_create(memory_arena);

  r_string_copy_ansi(this->libs_path, R_LIBS_DIRECTORY);

  this->memory = memory;
  this->frame_info = frame_info;
  this->frame_info->desired_fps = 60.0;
  this->frame_info->desired_ms_per_frame = 1000.0 / 60.0;

  r_app_host_init_apis(this);

  this->running = true;

  return this;
}

void //
r_app_host_load_app(r_app_host_t* this, const char* filename) {

  r_lib_t* lib = r_lib_loader_load_lib(this->memory, filename);
  r_app_t* app = (r_app_t*)lib->state;
  this->app = app;
  this->app->lib = lib;
  this->app->memory_arena = lib->memory_arena;
  this->app_api = (r_app_i*)lib->api;

  r_app_info_t app_info = this->app_api->get_app_info();
  this->frame_info->desired_fps = app_info.desired_fps;

  if (!app_info.disable_log_to_file) {
    r_logger_file_device_i* logger_file_device = r_api_db_find_by_name(this->api_db, R_LOGGER_FILE_DEVICE_API_NAME);
    r_logger_add_device((r_logger_device_i*)logger_file_device);
  }
}

void //
r_app_host_init(r_app_host_t* this) {
  r_app_host_load_libs(this);

  for (i32 i = 0; i < this->lib_count; ++i) {
    r_lib_t lib = this->libs[i];
    r_lib_i* api = (r_lib_i*)lib.api;
    api->init(this->api_db_api);
  }

  this->app_api->init(this->app, this->api_db_api);
}

void //
r_app_host_run(r_app_host_t* this) {
  this->app_api->run(this->app, this->frame_info);
  this->running = this->app->running;
}

void //
r_app_host_destroy(const r_app_host_t* this) {
  for (i32 i = 0; i < this->lib_count; ++i) {
    r_lib_t lib = this->libs[i];
    r_lib_i* api = (r_lib_i*)lib.api;
    api->destroy(lib.state);
  }

  this->app_api->destroy(this->app);
}