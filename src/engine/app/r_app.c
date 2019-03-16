#include "r_app.h"
#include "engine/window/r_window.h"
#include "engine/memory/r_memory_arena.h"
#include "engine/plugins/r_plugin_manager.h"
#include "engine/time/r_time.h"

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
r_app_init(r_app_t* state) {}

void
r_app_load(r_app_t* state) {}

void
r_app_input(r_app_t* state) {
  r_window_input(state->window);
}

void
r_app_update(r_app_t* state) {
  state->time->dt = 0.1f;
  r_color_t color = (r_color_t){0.08f, 0.09f, 0.12f, 1.00f};
  state->window->back_color = color;
  state->running = !state->window->should_close;
  r_window_update(state->window);
}

void
r_app_render(const r_app_t* state) {
  r_window_render(state->window);
  r_window_swapbuffers(state->window);
}

void
r_app_unload(const r_app_t* state) {}

void
r_app_destroy(const r_app_t* state) {
  r_window_destroy(state->window);
}

void //
r_app_run(r_app_t* state) {
  r_app_input(state);
  r_app_update(state);
  r_app_render(state);
}