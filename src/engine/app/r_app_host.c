#include "engine/io/r_path.h"
#include "engine/io/r_directory.h"
#include "engine/memory/r_memory_arena.h"
#include "engine/plugins/r_plugin_manager.h"
#include "engine/plugins/r_plugin_loader.h"
#include "engine/lib_loader/r_lib_loader.h"
#include "engine/plugins/r_plugin.h"
#include "engine/string/r_string.h"
#include "engine/time/r_datetime.h"
#include "engine/window/r_window.h"
#include "engine/ui/r_ui.h"
#include "engine/io/r_file.h"
#include "engine/diagnostics/r_logger.h"
#include "engine/diagnostics/r_logger_file_device.h"
#include "engine/gfx/r_gfx_renderer.h"

#include "engine/app/r_api_db_i.h"
#include "engine/diagnostics/r_logger_i.h"
#include "engine/diagnostics/r_logger_file_device_i.h"
#include "engine/string/r_string_i.h"
#include "engine/window/r_window_i.h"
#include "engine/ui/r_ui_i.h"
#include "engine/gfx/r_gfx_renderer_i.h"

#include "r_app.h"
#include "r_api_db.c"
#include "r_app_host.h"
#include "r_app_host_reload.c"

internal void //
r_app_host_load_lib(r_file_info_a_t file_info, r_app_host_t* this) {
  r_lib_t lib = {0};
  r_lib_loader_load_lib(this->memory, &lib, file_info.full_name);
  this->libs[lib.id - 256] = lib;
  this->lib_count++;
}

internal void //
r_app_host_load_libs(r_app_host_t* this) {
  r_directory_a_foreach_file(this->libs_path, "*.dll", (void*)r_app_host_load_lib, this);
}

internal void //
r_app_host_init_apis(r_app_host_t* this) {
  local r_logger_i debug_api = {0};
  debug_api.add_device = &r_logger_add_device;
  debug_api.debug = &r_logger_debug;
  debug_api.warn = &r_logger_warn;
  debug_api.error = &r_logger_error;

  local r_logger_file_device_i logger_file_device_api = {0};
  logger_file_device_api.print = &r_logger_file_device_print;
  logger_file_device_api.set_filename = &r_logger_file_device_set_filename;

  local r_window_i window_api = {0};
  window_api.instance = this->window;
  window_api.set_back_color = &r_window_set_back_color;
  window_api.set_title = &r_window_set_title;

  local r_string_i string_api = {0};
  string_api.to_ansi = &r_string_to_ansi;

  local r_ui_i ui_api = {0};
  ui_api.instance = this->ui;
  ui_api.create_main_menu = &r_ui_create_main_menu;
  ui_api.create_menu = &r_ui_create_menu;
  ui_api.create_menu_item = &r_ui_create_menu_item;
  ui_api.create_button = &r_ui_create_button;
  ui_api.create_frame = &r_ui_create_frame;

  local r_gfx_renderer_i renderer_api = {0};
  renderer_api.instance = this->renderer;
  renderer_api.add_cmd = &r_gfx_renderer_add_cmd;
  renderer_api.sort = &r_gfx_renderer_sort;
  renderer_api.submit = &r_gfx_renderer_submit;
  renderer_api.clear = &r_gfx_renderer_clear;
  renderer_api.create_clear_color_cmd = &r_gfx_renderer_create_clear_color_buffer_cmd;

  local r_api_db_i api_db_api = {0};
  api_db_api.add = &r_api_db_add;
  api_db_api.find_by_name = &r_api_db_find_by_name;
  this->api_db_api = &api_db_api;
  this->api_db_api->instance = this->api_db;

  r_api_db_add(this->api_db, R_LOGGER_API_ID, R_LOGGER_API_NAME, &debug_api);
  r_api_db_add(this->api_db, R_LOGGER_FILE_DEVICE_API_ID, R_LOGGER_FILE_DEVICE_API_NAME, &logger_file_device_api);
  r_api_db_add(this->api_db, R_WINDOW_API_ID, R_WINDOW_API_NAME, &window_api);
  r_api_db_add(this->api_db, R_STRING_API_ID, R_STRING_API_NAME, &string_api);
  r_api_db_add(this->api_db, R_UI_API_ID, R_UI_API_NAME, &ui_api);
  r_api_db_add(this->api_db, R_GFX_RENDERER_API_ID, R_GFX_RENDERER_API_NAME, &renderer_api);
}

size_t
r_app_host_get_size(void) {
  return sizeof(r_app_host_t) +     //
         sizeof(r_app_t) +          //
         sizeof(r_api_db_t) +       //
         sizeof(r_ui_t) +           //
         sizeof(r_window_t) +       //
         sizeof(r_frame_info_t) +   //
         sizeof(r_gfx_renderer_t) + //
         sizeof(r_lib_t) * MAX_PLUGINS_COUNT;
}

r_app_host_t* //
r_app_host_create(r_memory_t* memory, r_frame_info_t* frame_info) {

  size_t total_memory = r_app_host_get_size();
  r_memory_arena_t* memory_arena = r_memory_add_arena(memory, total_memory);

  r_app_host_t* this = r_memory_arena_push_struct(memory_arena, r_app_host_t);
  this->app = r_memory_arena_push_struct(memory_arena, r_app_t);
  this->window = r_memory_arena_push_struct(memory_arena, r_window_t);
  this->ui = r_memory_arena_push_struct(memory_arena, r_ui_t);
  this->api_db = r_memory_arena_push_struct(memory_arena, r_api_db_t);
  this->renderer = r_memory_arena_push_struct(memory_arena, r_gfx_renderer_t);

  r_string_a_copy(".\\libs", this->libs_path);

  this->memory = memory;
  this->frame_info = frame_info;
  this->frame_info->desired_fps = 60.0;
  this->frame_info->desired_ms_per_frame = 1000.0 / 60.0;
  this->running = true;

  r_window_t* window = this->window;
  r_string_w_copy(L"title", window->title);
  window->width = 1280;
  window->height = 720;
  window->back_color = R_COLOR_BLACK;

  r_ui_t* ui = this->ui;
  r_ui_set_theme(ui, 0);

  return this;
}

void //
r_app_host_load_app(r_app_host_t* this, const char* filename) {
  r_lib_loader_load_lib(this->memory, &this->app->lib, filename);
  this->app->memory_arena = this->app->lib.memory_arena;
  this->app->state = this->app->lib.state;
  this->app->api = *(r_app_api_t*)this->app->lib.functions;

  r_app_info_t app_info = this->app->api.get_app_info();
  this->frame_info->desired_fps = app_info.desired_fps;
  this->window->width = app_info.width;
  this->window->height = app_info.height;
  r_string_w_copy(app_info.title, this->window->title);
}

void //
r_app_host_init(r_app_host_t* this) {
  r_app_host_init_apis(this);
  r_app_host_load_libs(this);

  for (i32 i = 0; i < this->lib_count; ++i) {
    r_lib_t lib = this->libs[i];
    R_LIB_INIT init_fn = (R_LIB_INIT)lib.functions[0];
    init_fn(lib.state, this->api_db_api);
  }

  this->app->api.init(this->app, this->api_db_api);
}

void //
r_app_host_run(r_app_host_t* this) {
  this->app->api.run(this->app->state, this->frame_info);
  this->running = !this->window->should_close;
}

void //
r_app_host_destroy(const r_app_host_t* this) {
  for (i32 i = 0; i < this->lib_count; ++i) {
    r_lib_t lib = this->libs[i];
    R_LIB_DESTROY destroy_fn = (R_LIB_DESTROY)lib.functions[1];
    destroy_fn(lib.state);
  }

  this->app->api.destroy(this->app->state);
}