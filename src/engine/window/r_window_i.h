#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_WINDOW_API_ID 2
#define R_WINDOW_API_NAME "r_window"

typedef struct r_window_t r_window_t;

typedef void (*R_WINDOW_SET_BACK_COLOR)(r_window_t* instance, const r_color_t color);
typedef void (*R_WINDOW_SET_TITLE)(r_window_t* instance, const wchar_t* title);
typedef void (*R_WINDOW_SWAP_BUFFERS)(const r_window_t* instance);
typedef void (*R_WINDOW_CLEAR_COLOR)(const r_window_t* instance);
typedef void (*R_WINDOW_INPUT)(const r_window_t* instance);
typedef void (*R_WINDOW_UPDATE)(r_window_t* instance);

typedef struct r_window_i {
  r_window_t* instance;
  R_WINDOW_SET_BACK_COLOR set_back_color;
  R_WINDOW_SET_TITLE set_title;
  R_WINDOW_SWAP_BUFFERS swap_buffers;
  R_WINDOW_CLEAR_COLOR clear_color;
  R_WINDOW_INPUT input;
  R_WINDOW_UPDATE update;
} r_window_i;

#ifdef __cplusplus
}
#endif