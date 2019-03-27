#include "engine/io/r_path.h"
#include "engine/io/r_directory.h"
#include "engine/memory/r_memory_arena.h"
#include "engine/plugins/r_plugin_manager.h"
#include "engine/plugins/r_plugin_loader.h"
#include "engine/plugins/r_plugin.h"
#include "engine/string/r_string.h"
#include "engine/time/r_time.h"
#include "engine/window/r_window.h"
#include "engine/diagnostics/r_debug.h"
#include "engine/diagnostics/r_debug_api.h"
#include "engine/window/r_window_api.h"
#include "r_api_db.c"
#include "r_app.h"

r_app_t* //
r_app_create(r_memory_t* memory, r_app_info_t* info) {

  size_t total_memory = sizeof(r_app_t) + //
                        sizeof(r_window_t) + //
                        sizeof(r_time_info_t) + //
                        sizeof(r_plugin_manager_t) + //
                        sizeof(r_api_db_t);

  r_memory_arena_t* memory_arena = r_memory_add_arena(memory, total_memory);

  r_app_t* this = R_MEMORY_ARENA_PUSH_STRUCT(memory_arena, r_app_t);
  this->window = R_MEMORY_ARENA_PUSH_STRUCT(memory_arena, r_window_t);
  this->plugin_manager = R_MEMORY_ARENA_PUSH_STRUCT(memory_arena, r_plugin_manager_t);
  this->api_db = R_MEMORY_ARENA_PUSH_STRUCT(memory_arena, r_api_db_t);
  this->plugin_manager->memory = memory;
  this->time_info = info->time_info;
  this->memory = memory;
  this->time_info->desired_fps = info->desired_fps;
  this->time_info->desired_ms_per_frame = 1000.0 / info->desired_fps;
  this->running = true;

  r_window_t* window = this->window;
  window->title = info->title;
  window->width = info->width;
  window->height = info->height;
  window->back_color = info->back_color;

  return this;
}

void //
r_app_init_apis(r_app_t* this) {
  local r_debug_api_t r_debug_api = {0};
  r_debug_api.print = (R_DEBUG_PRINT)&r_debug_print;

  local r_window_api_t r_window_api = {0};
  r_window_api.window = this->window;
  r_window_api.set_back_color = (R_WINDOW_SET_BACK_COLOR)&r_window_set_back_color;
  r_window_api.set_title = (R_WINDOW_SET_TITLE)&r_window_set_title;

  this->api_db->apis[R_DEBUG_API_ID] = &r_debug_api;
  this->api_db->apis[R_WINDOW_API_ID] = &r_window_api;
  this->api_db->find = (R_API_DB_FIND_API_FN)&r_api_db_find_api;
}

void
r_app_init(r_app_t* this) {

  r_app_init_apis(this);

  r_plugin_manager_t* plugin_manager = this->plugin_manager;
  r_plugin_manager_init(plugin_manager);

  for (int i = 0; i < plugin_manager->init_count; ++i) {
    u8 index = plugin_manager->init[i];
    r_plugin_t* plugin = plugin_manager->plugins[index];
    u32 id = plugin->id;

    this->api_db->apis[id] = plugin->api;

    plugin->init(plugin->state, this->api_db);
  }
}

void
r_app_load(r_app_t* this) {}

void
r_app_input(r_app_t* this) {
  r_window_input(this->window);

  r_plugin_manager_t* plugin_manager = this->plugin_manager;

  for (int i = 0; i < plugin_manager->input_count; ++i) {
    u8 index = plugin_manager->input[i];
    r_plugin_t* plugin = plugin_manager->plugins[index];
    plugin->input(plugin->state);
  }
}

typedef i32 (*PLUGIN_A_ADD_FN)(i32, i32);

void
r_app_update(r_app_t* this) {

  this->running = !this->window->should_close;
  r_window_update(this->window);

  r_plugin_manager_t* plugin_manager = this->plugin_manager;

  for (int i = 0; i < plugin_manager->update_count; ++i) {
    u8 index = plugin_manager->update[i];
    r_plugin_t* plugin = plugin_manager->plugins[index];
    plugin->update(plugin->state, this->time_info->dt);
  }
}

void
r_app_render(const r_app_t* this) {

  r_plugin_manager_t* plugin_manager = this->plugin_manager;

  for (int i = 0; i < plugin_manager->render_count; ++i) {
    u8 index = plugin_manager->render[i];
    r_plugin_t* plugin = plugin_manager->plugins[index];
    plugin->render(plugin->state);
  }

  r_window_render(this->window);
  r_window_swapbuffers(this->window);
}

void
r_app_unload(const r_app_t* this) {
  r_plugin_manager_t* plugin_manager = this->plugin_manager;

  for (int i = 0; i < plugin_manager->unload_count; ++i) {
    u8 index = plugin_manager->unload[i];
    r_plugin_t* plugin = plugin_manager->plugins[index];
    plugin->unload(plugin->state);
  }
}

void
r_app_destroy(const r_app_t* this) {
  r_window_destroy(this->window);

  r_plugin_manager_t* plugin_manager = this->plugin_manager;

  for (int i = 0; i < plugin_manager->destroy_count; ++i) {
    u8 index = plugin_manager->destroy[i];
    r_plugin_t* plugin = plugin_manager->plugins[index];
    plugin->destroy(plugin->state);
  }
}

void //
r_app_run(r_app_t* this) {

  r_app_input(this);
  r_app_update(this);
  r_app_render(this);

  r_plugin_manager_reload_plugins(this->plugin_manager);
}