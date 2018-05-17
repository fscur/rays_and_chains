#pragma once
#include "r_types.h"
#include "r_bitmap.h"
#include "r_window.h"

typedef struct App_Ui {
  App_Window* window;
  Bitmap* image;
  u32 texture_id;
  Color clear_color;
  f32 dt;
} App_Ui;

void ui_init(App_Ui* ui);
void ui_load(App_Ui* ui);
void ui_render(App_Ui* ui);
void ui_unload(App_Ui* ui);
