#include "r_app.h"

u32
get_int() {
  return 31415;
}

App_State*
app_init(App_Memory* memory) {
  assert(sizeof(App_State) <= memory->permanent_storage_size);

  App_State* state = (App_State*)memory->permanent_storage_addr;
  state->memory = memory;
  state->image = r_create_image(400, 300);
  state->clear_color = (Color){0.3f, 0.4, 0.8, 1.0};
  state->dt = 0.0;

  r_clear_image(state->image, state->clear_color);
  return state;
}

void
app_destroy(App_State* state) {}