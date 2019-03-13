#include "engine/memory/r_memory_arena.h"
#include "r_app_window.h"
#include "r_app_ui.h"
#include "r_app.h"
#include "engine/media/r_media_bitmap.h"

r_app_state_t* //
r_app_create(r_memory_arena_t* memory_arena) {

  r_app_state_t* state = R_MEMORY_ARENA_PUSH_STRUCT(memory_arena, r_app_state_t);
  state->window = R_MEMORY_ARENA_PUSH_STRUCT(memory_arena, r_app_window_t);
  state->ui = R_MEMORY_ARENA_PUSH_STRUCT(memory_arena, r_app_ui_t);
  state->memory_arena = memory_arena;
  state->running = true;
  state->dt = 0.0;

  r_color_t color = (r_color_t){0.08f, 0.09f, 0.12f, 1.00f};

  r_app_window_t* window = state->window;
  window->title = "rays and chains";
  window->width = 1280;
  window->height = 720;
  window->back_color = color;

  r_app_ui_t* ui = state->ui;
  ui->clear_color = color;
  ui->image = r_media_create_image(400, 300);
  ui->window = state->window;

  r_media_clear_image(ui->image, ui->clear_color);
  return state;
}

void
r_app_init(r_app_state_t* state) {
  r_app_window_create(state->window);
  r_app_ui_init(state->ui);
}

void
r_app_load(r_app_state_t* state) {
  r_app_ui_load(state->ui);
}

void
r_app_input(r_app_state_t* state) {
  r_app_window_input(state->window);
}

void
r_app_update(r_app_state_t* state) {
  state->dt = 0.1f;
  r_color_t color = (r_color_t){0.08f, 0.09f, 0.12f, 1.00f};
  state->window->back_color = color;
  state->ui->clear_color = color;
  state->ui->dt = state->dt;
  state->running = !state->window->should_close;
  r_app_window_update(state->window);
}

void
r_app_render(const r_app_state_t* state) {
  r_app_window_render(state->window);
  r_app_ui_render(state->ui);
  r_app_window_swapbuffers(state->window);
}

void
r_app_unload(const r_app_state_t* state) {
  r_app_ui_unload(state->ui);
}

void
r_app_destroy(const r_app_state_t* state) {
  r_app_window_destroy(state->window);
}