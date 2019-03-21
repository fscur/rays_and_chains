#include "engine/io/r_path.h"
#include "engine/io/r_directory.h"
#include "engine/memory/r_memory_arena.h"
#include "engine/plugins/r_plugin_manager.h"
#include "engine/plugins/r_plugin_loader.h"
#include "engine/plugins/r_plugin.h"
#include "engine/string/r_string.h"
#include "engine/time/r_time.h"
#include "engine/window/r_window.h"
#include "r_app.h"

r_app_t* //
r_app_create(r_memory_t* memory, r_app_info_t* info) {

  size_t total_memory = sizeof(r_app_t) +    //
                        sizeof(r_window_t) + //
                        sizeof(r_plugin_manager_t) + sizeof(r_time_t);

  r_memory_arena_t* memory_arena = r_memory_add_arena(memory, total_memory);

  r_app_t* state = R_MEMORY_ARENA_PUSH_STRUCT(memory_arena, r_app_t);
  state->window = R_MEMORY_ARENA_PUSH_STRUCT(memory_arena, r_window_t);
  state->plugin_manager = R_MEMORY_ARENA_PUSH_STRUCT(memory_arena, r_plugin_manager_t);
  state->plugin_manager->memory = memory;
  state->time = info->time;
  state->memory = memory;
  state->time->desired_fps = info->desired_fps;
  state->time->desired_ms_per_frame = 1000.0 / info->desired_fps;
  state->running = true;

  r_window_t* window = state->window;
  window->title = info->title;
  window->width = info->width;
  window->height = info->height;
  window->back_color = info->back_color;

  return state;
}

void
r_app_init(r_app_t* state) {
  r_plugin_manager_init(state->plugin_manager);
}

void
r_app_load(r_app_t* state) {}

void
r_app_input(r_app_t* state) {
  r_window_input(state->window);

  r_plugin_manager_t* plugin_manager = state->plugin_manager;

  for (int i = 0; i < plugin_manager->input_count; ++i) {
    u8 index = plugin_manager->input[i];
    r_plugin_t* plugin = plugin_manager->plugins[index];
    plugin->input(plugin->state_addr);
  }
}

void
r_app_update(r_app_t* state) {

  state->running = !state->window->should_close;
  r_window_update(state->window);

  r_plugin_manager_t* plugin_manager = state->plugin_manager;

  for (int i = 0; i < plugin_manager->update_count; ++i) {
    u8 index = plugin_manager->update[i];
    r_plugin_t* plugin = plugin_manager->plugins[index];
    plugin->update(plugin->state_addr, state->time->dt);
  }
}

void
r_app_render(const r_app_t* state) {

  r_plugin_manager_t* plugin_manager = state->plugin_manager;

  for (int i = 0; i < plugin_manager->render_count; ++i) {
    u8 index = plugin_manager->render[i];
    r_plugin_t* plugin = plugin_manager->plugins[index];
    plugin->render(plugin->state_addr);
  }

  r_window_render(state->window);
  r_window_swapbuffers(state->window);
}

void
r_app_unload(const r_app_t* state) {
  r_plugin_manager_t* plugin_manager = state->plugin_manager;

  for (int i = 0; i < plugin_manager->unload_count; ++i) {
    u8 index = plugin_manager->unload[i];
    r_plugin_t* plugin = plugin_manager->plugins[index];
    plugin->unload(plugin->state_addr);
  }
}

void
r_app_destroy(const r_app_t* state) {
  r_window_destroy(state->window);

  r_plugin_manager_t* plugin_manager = state->plugin_manager;

  for (int i = 0; i < plugin_manager->destroy_count; ++i) {
    u8 index = plugin_manager->destroy[i];
    r_plugin_t* plugin = plugin_manager->plugins[index];
    plugin->destroy(plugin->state_addr);
  }
}

void //
r_app_run(r_app_t* state) {
  r_app_input(state);
  r_app_update(state);
  r_app_render(state);
}