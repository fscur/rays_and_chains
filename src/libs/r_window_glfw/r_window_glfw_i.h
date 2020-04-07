#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_WINDOW_GLFW_API_NAME "r_window_glfw"

typedef struct r_lib_load_info_t r_lib_load_info_t;
typedef struct r_api_db_i r_api_db_i;
typedef struct r_window_desc_t r_window_desc_t;
typedef struct r_window_t r_window_t;
typedef struct r_window_glfw_i r_window_glfw_i;

typedef struct r_window_glfw_i {
  size_t (*get_size)(void);
  char* (*get_api_name)(void);
  void (*init)(r_api_db_i* db);
  void (*destroy)(r_window_t* state);
  r_window_t* (*create)(r_window_desc_t* window_description);
  void (*show)(r_window_t* window);
  void (*process_input)(r_window_t* window);
  void (*swap_buffers)(const r_window_t* window);
  void (*set_backcolor)(r_window_t* window, const r_color_t color);
  void (*set_title)(r_window_t* window, const wchar_t* title);
} r_window_glfw_i;

#ifdef __cplusplus
}
#endif