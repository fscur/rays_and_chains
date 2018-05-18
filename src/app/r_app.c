#include "r_app.h"
#include "r_memory.c"

App_State*
app_create(App_Memory* memory) {
  assert(sizeof(App_State) <= memory->permanent_size);

  App_Memory_Arena arena = {};
  arena_init(&arena, memory->permanent_addr, memory->permanent_size);

  App_State* state = arena_push_struct(&arena, App_State);
  state->window = arena_push_struct(&arena, App_Window);
  state->ui = arena_push_struct(&arena, App_Ui);
  state->memory = memory;
  state->running = true;
  state->dt = 0.0;

  Color color = (Color){0.08f, 0.09f, 0.12f, 1.00f};

  App_Window* window = state->window;
  window->title = "rays and chains";
  window->width = 1280;
  window->height = 720;
  window->back_color = color;

  App_Ui* ui = state->ui;
  ui->clear_color = color;
  ui->image = r_create_image(400, 300);
  ui->window = state->window;

  r_clear_image(ui->image, ui->clear_color);
  return state;
}

void
app_init(App_State* state) {
  ui_init(state->ui);
}

void
app_load(App_State* state) {
  ui_load(state->ui);
}

void
app_input(App_State* state) {
  window_input(state->window);
}

void
app_update(App_State* state) {
  state->dt = 0.1;
  Color color = (Color){0.08f, 0.09f, 0.12f, 1.00f};
  state->window->back_color = color;
  state->ui->clear_color = color;
  state->ui->dt = state->dt;
  state->running = !state->window->should_close;
  window_update(state->window);
}

void
app_render(const App_State* state) {
  window_render(state->window);
  ui_render(state->ui);
  window_swapbuffers(state->window);
}

void
app_unload(const App_State* state) {
  ui_unload(state->ui);
}

void
app_destroy(const App_State* state) {
  window_destroy(state->window);
}