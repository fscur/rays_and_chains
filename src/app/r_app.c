#include "r_app.h"

App_State*
app_init(App_Memory* memory) {
  assert(sizeof(App_State) <= memory->permanent_size);

  App_State* state = (App_State*)memory->permanent_addr;
  state->memory = memory;
  state->image = r_create_image(400, 300);
  state->clear_color = (Color){0.3f, 0.4, 0.8, 1.0};
  state->dt = 0.0;

  r_clear_image(state->image, state->clear_color);
  return state;
}

void
app_input(App_State* state) {
  printf("input.");
}

void
app_update(App_State* state) {
  state->dt = 100.0;
}

void
app_render(App_State* state) {
  printf("render.");
}

void
app_destroy(App_State* state) {}