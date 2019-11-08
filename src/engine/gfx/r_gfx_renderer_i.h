#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_GFX_RENDERER_API_ID 5
#define R_GFX_RENDERER_API_NAME "r_gfx_renderer"

typedef struct r_gfx_renderer_t r_gfx_renderer_t;

typedef void (*R_GFX_RENDERER_ADD_CMD)(r_gfx_renderer_t* instance, r_gfx_cmd_t cmd);
typedef r_gfx_cmd_t* (*R_GFX_RENDERER_CREATE_CLEAR_COLOR_CMD)(const r_gfx_renderer_t* instance);
typedef void (*R_GFX_RENDERER_CLEAR)(r_gfx_renderer_t* instance);
typedef void (*R_GFX_RENDERER_SORT)(r_gfx_renderer_t* instance);
typedef void (*R_GFX_RENDERER_SUBMIT)(const r_gfx_renderer_t* instance);

typedef struct r_gfx_renderer_i {
  r_gfx_renderer_t* instance;
  R_GFX_RENDERER_ADD_CMD add_cmd;
  R_GFX_RENDERER_CREATE_CLEAR_COLOR_CMD create_clear_color_cmd;
  R_GFX_RENDERER_CLEAR clear;
  R_GFX_RENDERER_SORT sort;
  R_GFX_RENDERER_SUBMIT submit;
} r_gfx_renderer_i;

#ifdef __cplusplus
}
#endif