#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_UI_RENDERER_API_ID 6
#define R_UI_RENDERER_API_NAME "r_ui_renderer"

typedef struct r_ui_renderer_t r_ui_renderer_t;
typedef struct r_window_t r_window_t;

typedef void (*R_UI_RENDERER_RENDER)(r_ui_renderer_t* this, r_ui_t* ui);
typedef r_ui_renderer_t* (*R_UI_RENDERER_CREATE)(r_window_t* window);

typedef struct r_ui_renderer_i {
  r_ui_renderer_t* instance;
  R_UI_RENDERER_CREATE create;
  R_UI_RENDERER_RENDER render;
} r_ui_renderer_i;

#ifdef __cplusplus
}
#endif