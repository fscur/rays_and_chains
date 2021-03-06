#include "engine/io/r_path.h"
#include "engine/io/r_directory.h"
#include "engine/memory/r_memory_block.h"
#include "engine/plugins/r_plugin_manager.h"
#include "engine/plugins/r_plugin_loader.h"
#include "engine/lib_loader/r_lib_loader.h"
#include "engine/plugins/r_plugin.h"
#include "engine/string/r_string.h"
#include "engine/time/r_datetime.h"
#include "engine/window/r_window.h"
#include "engine/ui/r_ui.h"
#include "engine/io/r_file.h"
#include "engine/diagnostics/r_debug.h"
#include "engine/gfx/r_gfx_renderer.h"

#include "engine/app/r_api_db_i.h"
#include "engine/diagnostics/r_debug_i.h"
#include "engine/string/r_string_i.h"
#include "engine/window/r_window_i.h"
#include "engine/ui/r_ui_i.h"
#include "engine/gfx/r_gfx_renderer_i.h"

#include "r_app.h"
#include "r_api_db.c"
#include "r_app_host.h"

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

r_app_host_t* //
r_app_host_create(r_memory_t* memory, r_frame_info_t* frame_info) {

  size_t total_memory = r_app_host_get_size();
  r_memory_block_t* memory_block = r_memory_add_block(memory, total_memory);

  r_app_host_t* this = r_memory_block_push_struct(memory_block, r_app_host_t);
  this->app = r_memory_block_push_struct(memory_block, r_app_t);
  this->window = r_memory_block_push_struct(memory_block, r_window_t);
  this->ui = r_memory_block_push_struct(memory_block, r_ui_t);
  this->api_db = r_memory_block_push_struct(memory_block, r_api_db_t);
  this->renderer = r_memory_block_push_struct(memory_block, r_gfx_renderer_t);

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
  this->app->memory_block = this->app->lib.memory_block;
  this->app->state = this->app->lib.state;
  this->app->api = *(r_app_api_t*)this->app->lib.functions;

  r_app_info_t app_info = this->app->api.get_app_info();
  this->frame_info->desired_fps = app_info.desired_fps;
  this->window->width = app_info.width;
  this->window->height = app_info.height;
  r_string_w_copy(app_info.title, this->window->title);
}

void //
r_app_host_init_apis(r_app_host_t* this) {
  local r_debug_i debug_api = {0};
  debug_api.print = &r_debug_print;

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

  r_api_db_add(this->api_db, R_DEBUG_API_ID, R_DEBUG_API_NAME, &debug_api);
  r_api_db_add(this->api_db, R_WINDOW_API_ID, R_WINDOW_API_NAME, &window_api);
  r_api_db_add(this->api_db, R_STRING_API_ID, R_STRING_API_NAME, &string_api);
  r_api_db_add(this->api_db, R_UI_API_ID, R_UI_API_NAME, &ui_api);
  r_api_db_add(this->api_db, R_GFX_RENDERER_API_ID, R_GFX_RENDERER_API_NAME, &renderer_api);
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
r_app_host_reload_app(r_app_host_t* this) {
  r_lib_t* app_lib = &this->app->lib;
  bool should_reload_app = r_app_host_should_reload_lib(app_lib);

  if (should_reload_app) {
    r_lib_loader_destroy_lib(app_lib);
    r_lib_loader_reload_lib(app_lib);
    R_LIB_INIT init_fn = (R_LIB_INIT)app_lib->functions[1];
    init_fn(this->app, this->api_db_api);
  }
}

void //
r_app_host_reload(r_app_host_t* this) {

  r_app_host_reload_libs(this);

  for (u32 i = 0; i < this->reloaded_lib_count; ++i) {
    u8 index = this->reloaded_libs[i];
    r_lib_t lib = this->libs[index];
    R_LIB_INIT init_fn = (R_LIB_INIT)lib.functions[0];
    init_fn(lib.state, this->api_db_api);
  }

  this->reloaded_lib_count = 0;

  r_app_host_reload_app(this);
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

void //
r_app_host_run(r_app_host_t* this) {
  this->app->api.run(this->app->state, this->frame_info);
  r_app_host_reload(this);
  this->running = !this->window->should_close;
}