#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_WINDOW_API_NAME "r_window"

typedef struct r_window_t r_window_t;
typedef struct r_window_desc_t r_window_desc_t;

typedef struct r_window_i {
  r_window_t* (*create)(r_window_desc_t* window_description);
  void (*show)(r_window_t* window);
  void (*process_input)(r_window_t* window);
  void (*swap_buffers)(const r_window_t* window);
  void (*set_backcolor)(r_window_t* window, const r_color_t color);
  void (*set_title)(r_window_t* window, const wchar_t* title);
} r_window_i;

void //
r_window_register_api(r_api_db_t* api_db, r_memory_arena_t* apis_arena);

#ifdef __cplusplus
}
#endif