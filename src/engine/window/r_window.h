#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"
typedef struct r_window_t r_window_t;

typedef void (*R_WINDOW_TITLE_CHANGED_CALLBACK)(r_window_t* window);
typedef void (*R_WINDOW_BACK_COLOR_CHANGED_CALLBACK)(r_window_t* window);

typedef struct r_window_t {
  void* handle;
  wchar_t* title;
  i32 width;
  i32 height;
  r_color_t back_color;
  bool should_close;
  void* impl_state;
  R_WINDOW_TITLE_CHANGED_CALLBACK title_changed_callback;
  R_WINDOW_BACK_COLOR_CHANGED_CALLBACK back_color_changed_callback;
} r_window_t;

dll_export void //
r_window_set_title(r_window_t* this, const wchar_t* title);

dll_export void //
r_window_set_back_color(r_window_t* this, const r_color_t color);

#ifdef __cplusplus
}
#endif