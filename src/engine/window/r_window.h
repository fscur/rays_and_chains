#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_window_t {
  void* handle;
  wchar_t* title;
  i32 width;
  i32 height;
  r_color_t back_color;
  bool should_close;
} r_window_t;

dll_export void //
r_window_create(r_window_t* this);

dll_export void //
r_window_input(r_window_t* this);

dll_export void //
r_window_update(r_window_t* this);

dll_export void //
r_window_render(r_window_t* this);

dll_export void //
r_window_swapbuffers(r_window_t* this);

dll_export void //
r_window_destroy(r_window_t* this);

dll_export void //
r_window_set_title(r_window_t* this, const wchar_t* title);

dll_export void //
r_window_set_back_color(r_window_t* this, const r_color_t color);

#ifdef __cplusplus
}
#endif