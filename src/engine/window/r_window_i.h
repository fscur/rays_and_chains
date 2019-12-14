#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_WINDOW_API_ID 2
#define R_WINDOW_API_NAME "r_window"

typedef struct r_window_t r_window_t;

typedef void (*R_WINDOW_SET_BACK_COLOR)(r_window_t* window, const r_color_t color);
typedef void (*R_WINDOW_SET_TITLE)(r_window_t* window, const wchar_t* title);
typedef r_window_t* (*R_WINDOW_CREATE)();
typedef void (*R_WINDOW_SHOW)(r_window_t* window);
typedef void (*R_WINDOW_PROCESS_INPUT)(r_window_t* window);
typedef void (*R_WINDOW_SWAP_BUFFERS)(const r_window_t* window);

typedef struct r_window_i {
  R_WINDOW_CREATE create;
  R_WINDOW_SHOW show;
  R_WINDOW_PROCESS_INPUT process_input;
  R_WINDOW_SWAP_BUFFERS swap_buffers;
  R_WINDOW_SET_BACK_COLOR set_back_color;
  R_WINDOW_SET_TITLE set_title;
} r_window_i;

#ifdef __cplusplus
}
#endif