#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_UI_RENDERER_API_ID 6
#define R_UI_RENDERER_API_NAME "r_ui_renderer"

typedef struct r_ui_renderer_t r_ui_renderer_t;

typedef void (*R_UI_RENDERER_RENDER)(r_ui_renderer_t* this);

typedef struct r_ui_renderer_i {
  r_ui_renderer_t* instance;
  R_UI_RENDERER_RENDER render;
} r_ui_renderer_i;

#ifdef __cplusplus
}
#endif