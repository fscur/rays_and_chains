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
#include "engine/diagnostics/r_debug.h"

#include "engine/diagnostics/r_debug_api.h"
#include "engine/string/r_string_api.h"
#include "engine/window/r_window_api.h"

#include "r_app.h"
#include "r_api_db.c"
#include "r_app_context.h"

size_t
r_app_get_size() {
  return sizeof(r_app_context_t) +    //
         sizeof(r_app_t) +
         sizeof(r_api_db_t) + 
         sizeof(r_window_t) +         //
         sizeof(r_frame_info_t) +     //
         sizeof(r_plugin_manager_t) + //
         sizeof(r_plugin_t) * MAX_PLUGINS_COUNT;
}

r_app_context_t* //
r_app_context_create(r_memory_t* memory, r_app_info_t* info) {

  size_t total_memory = r_app_get_size();
  r_memory_block_t* memory_block = r_memory_add_block(memory, total_memory);

  r_app_context_t* this = r_memory_block_push_struct(memory_block, r_app_context_t);
  this->app = r_memory_block_push_struct(memory_block, r_app_t);
  this->window = r_memory_block_push_struct(memory_block, r_window_t);
  this->plugin_manager = r_memory_block_push_struct(memory_block, r_plugin_manager_t);
  this->api_db = r_memory_block_push_struct(memory_block, r_api_db_t);

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
r_app_context_init_apis(r_app_context_t* this) {
  local r_debug_api_t r_debug_api = {0};
  r_debug_api.print = (R_DEBUG_PRINT)&r_debug_print;

  local r_window_api_t r_window_api = {0};
  r_window_api.window = this->window;
  r_window_api.set_back_color = (R_WINDOW_SET_BACK_COLOR)&r_window_set_back_color;
  r_window_api.set_title = (R_WINDOW_SET_TITLE)&r_window_set_title;

  local r_string_api_t r_string_api = {0};
  r_string_api.to_ansi = (R_STRING_TO_ANSI)&r_string_to_ansi;

  this->api_db->apis[R_DEBUG_API_ID] = &r_debug_api;
  this->api_db->apis[R_WINDOW_API_ID] = &r_window_api;
  this->api_db->apis[R_STRING_API_ID] = &r_string_api;
  this->api_db->find_api = (R_API_DB_FIND_API_FN)&r_api_db_find_api;
}

void //
r_app_context_init(r_app_context_t* this) {

  r_app_context_init_apis(this);

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
r_app_context_reload(r_app_context_t* this) {

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

// void //
// r_app_context_input(r_app_context_t* this) {
//   r_plugin_manager_t* plugin_manager = this->plugin_manager;

//   for (int i = 0; i < plugin_manager->input_count; ++i) {
//     u8 index = plugin_manager->input[i];
//     r_plugin_t plugin = plugin_manager->plugins[index];
//     plugin.input(plugin.state);
//   }
// }

// void //
// r_app_context_update(r_app_context_t* this) {

//   this->running = !this->window->should_close;

//   r_plugin_manager_t* plugin_manager = this->plugin_manager;

//   for (int i = 0; i < plugin_manager->update_count; ++i) {
//     u8 index = plugin_manager->update[i];
//     r_plugin_t plugin = plugin_manager->plugins[index];
//     plugin.update(plugin.state, this->frame_info->dt);
//   }
// }

// void //
// r_app_context_render(const r_app_context_t* this) {

//   r_plugin_manager_t* plugin_manager = this->plugin_manager;

//   for (int i = 0; i < plugin_manager->render_count; ++i) {
//     u8 index = plugin_manager->render[i];
//     r_plugin_t plugin = plugin_manager->plugins[index];
//     plugin.render(plugin.state);
//   }
// }

void //
r_app_context_destroy(const r_app_context_t* this) {

  r_plugin_manager_t* plugin_manager = this->plugin_manager;

  for (int i = 0; i < plugin_manager->destroy_count; ++i) {
    u8 index = plugin_manager->destroy[i];
    r_plugin_t plugin = plugin_manager->plugins[index];
    plugin.destroy(plugin.state);
  }

  this->app->api.destroy(this->app->state);
}

void //
r_app_context_run(r_app_context_t* this) {
  this->app->api.run(this->app->state, this->frame_info);
  // r_app_context_input(this);
  // r_app_context_update(this);
  // r_app_context_render(this);
  r_app_context_reload(this);
}