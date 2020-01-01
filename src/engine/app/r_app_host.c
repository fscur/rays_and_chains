#include "engine/io/r_path.h"
#include "engine/io/r_directory.h"
#include "engine/memory/r_memory_arena.h"
#include "engine/lib_loader/r_lib_loader.h"
#include "engine/time/r_datetime.h"
#include "engine/io/r_file.h"

#include "engine/logger/r_logger.h"
#include "engine/logger/r_logger_i.h"
#include "engine/logger/r_logger_device_i.h"
#include "engine/logger/r_logger_file_device.h"
#include "engine/logger/r_logger_file_device_i.h"

#include "engine/window/r_window.h"
#include "engine/window/r_window_i.h"

#include "engine/string/r_string.h"
#include "engine/string/r_string_i.h"

#include "engine/app/r_api_db_i.h"

#include "r_app.h"
#include "r_app_i.h"
#include "r_api_db.c"
#include "r_app_host.h"
#include "r_app_host_reload.c"

internal void //
r_app_host_load_lib(r_file_info_a_t file_info, r_app_host_t* this) {
  r_lib_t* lib = r_lib_loader_load_lib(this->memory, file_info.full_name);
  this->libs[this->lib_count++] = *lib;
}

internal void //
r_app_host_load_libs(r_app_host_t* this) {
  r_directory_a_foreach_file(this->libs_path, "*.dll", (void*)r_app_host_load_lib, this);
}

internal void //
r_app_host_init_logger_apis(r_app_host_t* this) {
  local r_logger_i logger = {0};
  logger.add_device = &r_logger_add_device;
  logger.debug = &r_logger_debug;
  logger.warn = &r_logger_warn;
  logger.error = &r_logger_error;

  local r_logger_file_device_i logger_file_device = {0};
  logger_file_device.print = &r_logger_file_device_print;
  logger_file_device.set_filename = &r_logger_file_device_set_filename;

  r_api_db_add(this->api_db, R_LOGGER_API_NAME, &logger);
  r_api_db_add(this->api_db, R_LOGGER_FILE_DEVICE_API_NAME, &logger_file_device);
}

internal void //
r_app_host_init_window_apis(r_app_host_t* this) {
  local r_window_i window = {0};
  window.set_back_color = &r_window_set_back_color;
  window.set_title = &r_window_set_title;
  window.create = &r_window_create;
  window.show = &r_window_show;
  window.process_input = &r_window_process_input;

  r_api_db_add(this->api_db, R_WINDOW_API_NAME, &window);
}

internal void //
r_app_host_init_string_apis(r_app_host_t* this) {
  local r_string_i string_api = {0};
  string_api.to_ansi = &r_string_to_ansi;
  string_api.copy_ansi = &r_string_copy_ansi;
  string_api.copy_wide = &r_string_copy_wide;
  r_api_db_add(this->api_db, R_STRING_API_NAME, &string_api);
}

internal void //
r_app_host_init_apis(r_app_host_t* this) {
  r_app_host_init_logger_apis(this);
  r_app_host_init_string_apis(this);
  r_app_host_init_window_apis(this);

  // local r_ui_i ui_api = {0};
  // ui_api.instance = this->ui;
  // ui_api.create_main_menu = &r_ui_create_main_menu;
  // ui_api.create_menu = &r_ui_create_menu;
  // ui_api.create_menu_item = &r_ui_create_menu_item;
  // ui_api.create_button = &r_ui_create_button;
  // ui_api.create_frame = &r_ui_create_frame;
  // r_api_db_add(this->api_db, R_UI_API_ID, R_UI_API_NAME, &ui_api);

  // local r_gfx_renderer_i renderer_api = {0};
  // renderer_api.instance = this->renderer;
  // renderer_api.add_cmd = &r_gfx_renderer_add_cmd;
  // renderer_api.sort = &r_gfx_renderer_sort;
  // renderer_api.submit = &r_gfx_renderer_submit;
  // renderer_api.clear = &r_gfx_renderer_clear;
  // renderer_api.create_clear_color_cmd = &r_gfx_renderer_create_clear_color_buffer_cmd;
  // r_api_db_add(this->api_db, R_GFX_RENDERER_API_ID, R_GFX_RENDERER_API_NAME, &renderer_api);

  local r_api_db_i api_db_api = {0};
  api_db_api.add = &r_api_db_add;
  api_db_api.find_by_name = &r_api_db_find_by_name;
  this->api_db_api = &api_db_api;
  this->api_db_api->instance = this->api_db;
}

size_t
r_app_host_get_size(void) {
  return sizeof(r_app_host_t) +   //
         sizeof(r_api_db_t) +     //
         sizeof(r_frame_info_t) + //
         sizeof(r_lib_t) * R_MAX_LIB_COUNT;
}

r_app_host_t* //
r_app_host_create(r_memory_t* memory, r_frame_info_t* frame_info) {

  size_t total_memory = r_app_host_get_size();
  r_memory_arena_t* memory_arena = r_memory_add_arena(memory, total_memory);
  r_app_host_t* this = r_memory_arena_push_struct(memory_arena, r_app_host_t);
  this->api_db = r_api_db_create();

  r_string_copy_ansi(this->libs_path, ".\\libs");

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
  this->app->lib = *lib;
  this->app->memory_arena = lib->memory_arena;
  this->app_api = (r_app_i*)lib->api;

  r_app_info_t app_info = this->app_api->get_app_info();
  this->frame_info->desired_fps = app_info.desired_fps;

  if (!app_info.disable_log_to_file) {
    r_logger_file_device_i* logger_file_device =
        r_api_db_find_by_name(this->api_db, R_LOGGER_FILE_DEVICE_API_NAME);
    r_logger_add_device((r_logger_device_i*)logger_file_device);
  }
}

void //
r_app_host_init(r_app_host_t* this) {
  r_app_host_load_libs(this);

  for (i32 i = 0; i < this->lib_count; ++i) {
    r_lib_t lib = this->libs[i];
    r_lib_i* api = (r_lib_i*)lib.api;
    api->init(lib.state, this->api_db_api);
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