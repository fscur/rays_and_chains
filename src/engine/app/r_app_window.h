#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_app_window_t {
  void* handle;
  char* title;
  i32 width;
  i32 height;
  r_color_t back_color;
  bool should_close;
} r_app_window_t;

void r_app_window_create(r_app_window_t* window);
void r_app_window_input(r_app_window_t* window);
void r_app_window_update(r_app_window_t* window);
void r_app_window_render(r_app_window_t* window);
void r_app_window_swapbuffers(r_app_window_t* window);
void r_app_window_destroy(r_app_window_t* window);

#ifdef __cplusplus
}
#endif