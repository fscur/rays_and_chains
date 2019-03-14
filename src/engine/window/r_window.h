#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_window_t {
  void* handle;
  char* title;
  i32 width;
  i32 height;
  r_color_t back_color;
  bool should_close;
} r_window_t;

dll_export void //
r_window_create(r_window_t* window);
dll_export void //
r_window_input(r_window_t* window);
dll_export void //
r_window_update(r_window_t* window);
dll_export void //
r_window_render(r_window_t* window);
dll_export void //
r_window_swapbuffers(r_window_t* window);
dll_export void //
r_window_destroy(r_window_t* window);

#ifdef __cplusplus
}
#endif