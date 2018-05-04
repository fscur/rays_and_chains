#include "r_app.h"

App_State* 
app_init() {
    App_State* state = (App_State*)malloc(sizeof(App_State));
    state->image = r_create_image(400, 300);
    state->clear_color = (Color) { 0.3f, 0.4, 0.8, 1.0 };
    state->dt = 0.0;

    r_clear_image(state->image, state->clear_color);
    return state;
}

void 
app_destroy(App_State* state)
{
    r_destroy_image(state->image);
}