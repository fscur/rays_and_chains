#include "r_app.h"
#include "engine/window/r_window.h"
#include "engine/memory/r_memory_arena.h"
#include "engine/plugins/r_plugin_manager.h"
#include "engine/plugins/r_plugin_loader.h"
#include "engine/plugins/r_plugin.h"
#include "engine/time/r_time.h"
#include "engine/io/r_directory.h"

r_app_t* //
r_app_create(r_memory_t* memory, r_app_info_t* info) {

  size_t total_memory = sizeof(r_app_t) +    //
                        sizeof(r_window_t) + //
                        sizeof(r_plugin_manager_t) + sizeof(r_time_t);

  r_memory_arena_t* memory_arena = r_memory_add_arena(memory, total_memory);

  r_app_t* state = R_MEMORY_ARENA_PUSH_STRUCT(memory_arena, r_app_t);
  state->window = R_MEMORY_ARENA_PUSH_STRUCT(memory_arena, r_window_t);
  state->plugin_manager = R_MEMORY_ARENA_PUSH_STRUCT(memory_arena, r_plugin_manager_t);
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
r_app_load_plugin(r_file_info_t file_info, r_app_t* state) {
  r_plugin_manager_t* plugin_manager = state->plugin_manager;
  r_memory_t* memory = state->memory;

  void* plugin_a_handle = r_plugin_loader_load_plugin(file_info.full_name);

  char* load_function_name_a = "load_plugin_a";
  R_PLUGIN_LOAD load_function_a =
      (R_PLUGIN_LOAD)r_plugin_loader_fn(plugin_a_handle, load_function_name_a);

  r_plugin_t* plugin_a = load_function_a(memory, plugin_a_handle);
  plugin_a->name = file_info.name;
  plugin_a->file_name = file_info.full_name;

  r_plugin_manager_add_plugin(plugin_manager, plugin_a);
}

internal void //
r_app_init_plugin_manager(r_app_t* state) {

  r_directory_foreach_file(L".\\plugins", L"*.dll", (void*)r_app_load_plugin, state);

  r_plugin_manager_t* plugin_manager = state->plugin_manager;

  for (int i = 0; i < plugin_manager->plugin_count; ++i) {
    r_plugin_t* plugin = plugin_manager->plugins[i];
    ((R_PLUGIN_INIT)plugin_manager->init[i])(plugin->state_addr, plugin_manager);
  }
}

void
r_app_init(r_app_t* state) {
  r_app_init_plugin_manager(state);
}

void
r_app_load(r_app_t* state) {}

void
r_app_input(r_app_t* state) {
  r_window_input(state->window);

  r_plugin_manager_t* plugin_manager = state->plugin_manager;
  for (int i = 0; i < plugin_manager->plugin_count; ++i) {
    r_plugin_t* plugin = plugin_manager->plugins[i];
    ((R_PLUGIN_UPDATE)plugin_manager->update[i])(plugin->state_addr, state->time->dt);
  }
}

void
r_app_update(r_app_t* state) {

  state->running = !state->window->should_close;
  r_window_update(state->window);

  r_plugin_manager_t* plugin_manager = state->plugin_manager;
  for (int i = 0; i < plugin_manager->plugin_count; ++i) {
    r_plugin_t* plugin = plugin_manager->plugins[i];
    ((R_PLUGIN_UPDATE)plugin_manager->update[i])(plugin->state_addr, state->time->dt);
  }
}

void
r_app_render(const r_app_t* state) {

  r_plugin_manager_t* plugin_manager = state->plugin_manager;
  for (int i = 0; i < plugin_manager->plugin_count; ++i) {
    r_plugin_t* plugin = plugin_manager->plugins[i];
    ((R_PLUGIN_RENDER)plugin_manager->render[i])(plugin);
  }

  r_window_render(state->window);
  r_window_swapbuffers(state->window);
}

void
r_app_unload(const r_app_t* state) {
  r_plugin_manager_t* plugin_manager = state->plugin_manager;
  for (int i = 0; i < plugin_manager->plugin_count; ++i) {
    r_plugin_t* plugin = plugin_manager->plugins[i];
    ((R_PLUGIN_UNLOAD)plugin_manager->unload[i])(plugin);
  }
}

void
r_app_destroy(const r_app_t* state) {
  r_window_destroy(state->window);

  r_plugin_manager_t* plugin_manager = state->plugin_manager;
  for (int i = 0; i < plugin_manager->plugin_count; ++i) {
    r_plugin_t* plugin = plugin_manager->plugins[i];
    ((R_PLUGIN_DESTROY)plugin_manager->destroy[i])(plugin);
  }
}

void //
r_app_run(r_app_t* state) {
  r_app_input(state);
  r_app_update(state);
  r_app_render(state);
}