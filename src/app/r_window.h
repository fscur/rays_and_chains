#pragma once

#include "r_types.h"

typedef struct App_Window {
  void* handle;
  char* title;
  i32 width;
  i32 height;
  Color back_color;
  bool should_close;
} App_Window;

void window_create(App_Window* window);
void window_input(App_Window* window);
void window_update(App_Window* window);
void window_render(App_Window* window);
void window_swapbuffers(App_Window* window);
void window_destroy(App_Window* window);