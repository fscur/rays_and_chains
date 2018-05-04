#pragma once

#include "r_types.h"
#include "r_bitmap.h"
#include "r_math.h"
#include "r_render.h"

typedef struct App_State {
    Bitmap* image;
    f32 dt;
    Color clear_color;
} App_State;

App_State* 
app_init();

void app_destroy(App_State* state);