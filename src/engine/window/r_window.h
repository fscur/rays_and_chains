#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"
typedef struct r_window_t r_window_t;

typedef void (*R_WINDOW_TITLE_CHANGED_CALLBACK)(r_window_t* window);
typedef void (*R_WINDOW_BACK_COLOR_CHANGED_CALLBACK)(r_window_t* window);

typedef enum r_window_type_e {
  R_WINDOW_TYPE_DEFAULT,
  R_WINDOW_TYPE_TOOL,
  R_WINDOW_TYPE_MODAL
} r_window_type_e;

typedef enum r_window_start_position_e {
  R_WINDOW_START_POSITION_DEFAULT,
  R_WINDOW_START_POSITION_MANUAL,
  R_WINDOW_START_POSITION_CENTER,
} r_window_start_position_e;

typedef enum r_window_state_e {
  R_WINDOW_STATE_NORMAL,
  R_WINDOW_STATE_MINIMIZED,
  R_WINDOW_STATE_MAXIMIZED,
} r_window_state_e;

typedef struct r_window_desc_t {
  wchar_t title[R_SHORT_STRING_LENGTH];
  i32 x;
  i32 y;
  i32 width;
  i32 height;
  r_color_t back_color;
  r_window_type_e type;
  r_window_start_position_e start_position;
  r_window_state_e state;
} r_window_desc_t;

typedef struct r_window_t {
  void* handle;
  wchar_t title[R_SHORT_STRING_LENGTH];
  i32 x;
  i32 y;
  i32 width;
  i32 height;
  r_color_t back_color;
  r_window_state_e state;
  bool should_close;
  R_WINDOW_TITLE_CHANGED_CALLBACK title_changed_callback;
  R_WINDOW_BACK_COLOR_CHANGED_CALLBACK back_color_changed_callback;
} r_window_t;

r_window_t* //
r_window_create(r_window_desc_t* window_descriptor);

void //
r_window_show(r_window_t* window);

void //
r_window_hide(r_window_t* window);

void //
r_window_process_input(r_window_t* window);

void //
r_window_set_title(r_window_t* window, const wchar_t* title);

void //
r_window_set_backcolor(r_window_t* window, const r_color_t color);

#ifdef __cplusplus
}
#endif