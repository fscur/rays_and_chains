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
#include "engine/diagnostics/r_debug.h"
#include "engine/gfx/r_gfx_renderer.h"

#include "engine/diagnostics/r_debug_api.h"
#include "engine/string/r_string_api.h"
#include "engine/window/r_window_api.h"
#include "engine/ui/r_ui_api.h"
#include "engine/gfx/r_gfx_renderer_api.h"

#include "r_app.h"
#include "r_api_db.c"
#include "r_app_host.h"

size_t
r_app_host_get_size() {
  return sizeof(r_app_host_t) +       //
         sizeof(r_app_t) +            //
         sizeof(r_api_db_t) +         //
         sizeof(r_ui_t) +             //
         sizeof(r_window_t) +         //
         sizeof(r_frame_info_t) +     //
         sizeof(r_plugin_manager_t) + //
         sizeof(r_gfx_renderer_t) +   //
         sizeof(r_plugin_t) * MAX_PLUGINS_COUNT;
}

r_app_host_t* //
r_app_host_create(r_memory_t* memory, r_app_info_t* info) {

  size_t total_memory = r_app_host_get_size();
  r_memory_block_t* memory_block = r_memory_add_block(memory, total_memory);

  r_app_host_t* this = r_memory_block_push_struct(memory_block, r_app_host_t);
  this->app = r_memory_block_push_struct(memory_block, r_app_t);
  this->window = r_memory_block_push_struct(memory_block, r_window_t);
  this->ui = r_memory_block_push_struct(memory_block, r_ui_t);
  this->plugin_manager = r_memory_block_push_struct(memory_block, r_plugin_manager_t);
  this->api_db = r_memory_block_push_struct(memory_block, r_api_db_t);
  this->renderer = r_memory_block_push_struct(memory_block, r_gfx_renderer_t);

  r_string_a_copy(".\\libs", this->plugin_manager->libs_path);

  this->plugin_manager->plugins =
      (r_plugin_t*)r_memory_block_push_array(memory_block, r_plugin_t, MAX_PLUGINS_COUNT);

  this->plugin_manager->memory = memory;
  this->frame_info = info->frame_info;
  this->memory = memory;
  this->frame_info->desired_fps = info->desired_fps;
  this->frame_info->desired_ms_per_frame = 1000.0 / info->desired_fps;
  this->running = true;

  r_window_t* window = this->window;
  window->title = info->title;
  window->width = info->width;
  window->height = info->height;
  window->back_color = info->back_color;

  r_lib_loader_load_lib(this->memory, &this->app->lib, info->filename);
  this->app->state = this->app->lib.memory_block;
  this->app->api = *(r_app_api_t*)this->app->lib.functions;

  return this;
}

void //
r_app_host_init_apis(r_app_host_t* this) {
  local r_debug_api_t r_debug_api = {0};
  r_debug_api.print = (R_DEBUG_PRINT)&r_debug_print;

  local r_window_api_t r_window_api = {0};
  r_window_api.window = this->window;
  r_window_api.set_back_color = (R_WINDOW_SET_BACK_COLOR)&r_window_set_back_color;
  r_window_api.set_title = (R_WINDOW_SET_TITLE)&r_window_set_title;

  local r_string_api_t r_string_api = {0};
  r_string_api.to_ansi = (R_STRING_TO_ANSI)&r_string_to_ansi;

  local r_ui_api_t r_ui_api = {0};
  r_ui_api.ui = this->ui;

  local r_gfx_renderer_api_t r_gfx_renderer_api = {0};
  r_gfx_renderer_api.renderer = this->renderer;
  r_gfx_renderer_api.add_cmd = (R_GFX_RENDERER_ADD_CMD)&r_gfx_renderer_add_cmd;
  r_gfx_renderer_api.sort = (R_GFX_RENDERER_SORT)&r_gfx_renderer_sort;
  r_gfx_renderer_api.submit = (R_GFX_RENDERER_SUBMIT)&r_gfx_renderer_submit;
  r_gfx_renderer_api.clear = (R_GFX_RENDERER_CLEAR)&r_gfx_renderer_clear;
  r_gfx_renderer_api.create_clear_color_cmd =
      (R_GFX_RENDERER_CREATE_CLEAR_COLOR_CMD)&r_gfx_renderer_create_clear_color_buffer_cmd;

  this->api_db->apis[R_DEBUG_API_ID] = &r_debug_api;
  this->api_db->apis[R_WINDOW_API_ID] = &r_window_api;
  this->api_db->apis[R_STRING_API_ID] = &r_string_api;
  this->api_db->apis[R_UI_API_ID] = &r_ui_api;
  this->api_db->apis[R_GFX_RENDERER_API_ID] = &r_gfx_renderer_api;
  this->api_db->find_api = (R_API_DB_FIND_API_FN)&r_api_db_find_api;
}

void //
r_app_host_init(r_app_host_t* this) {

  r_app_host_init_apis(this);

  r_plugin_manager_t* plugin_manager = this->plugin_manager;
  r_plugin_manager_init(plugin_manager);

  for (int i = 0; i < plugin_manager->init_count; ++i) {
    u8 index = plugin_manager->init[i];
    r_plugin_t plugin = plugin_manager->plugins[index];
    this->api_db->apis[plugin.id] = plugin.api;
    plugin.init(plugin.state, this->api_db);
  }

  this->app->api.init(this->app->state, this->api_db);
}

void //
r_app_host_reload(r_app_host_t* this) {

  r_plugin_manager_t* plugin_manager = this->plugin_manager;

  r_plugin_manager_reload_plugins(plugin_manager);

  for (u32 i = 0; i < plugin_manager->reloaded_count; ++i) {
    u8 index = plugin_manager->reloaded_plugins[i];
    r_plugin_t plugin = plugin_manager->plugins[index];
    this->api_db->apis[plugin.id] = plugin.api;
    plugin.init(plugin.state, this->api_db);
  }

  plugin_manager->reloaded_count = 0;
}

void //
r_app_host_destroy(const r_app_host_t* this) {

  r_plugin_manager_t* plugin_manager = this->plugin_manager;

  for (int i = 0; i < plugin_manager->destroy_count; ++i) {
    u8 index = plugin_manager->destroy[i];
    r_plugin_t plugin = plugin_manager->plugins[index];
    plugin.destroy(plugin.state);
  }

  this->app->api.destroy(this->app->state);
}

void //
r_app_host_run(r_app_host_t* this) {
  this->app->api.run(this->app->state, this->frame_info);
  r_app_host_reload(this);
  this->running = !this->window->should_close;
}