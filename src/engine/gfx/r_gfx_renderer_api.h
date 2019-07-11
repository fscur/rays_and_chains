#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_GFX_RENDERER_API_ID 4
#define R_GFX_RENDERER_API_NAME "r_gfx_renderer"

typedef struct r_gfx_renderer_t r_gfx_renderer_t;

typedef void (*R_GFX_RENDERER_ADD_CMD)(r_gfx_renderer_t* renderer, r_gfx_cmd_t* cmd);
typedef r_gfx_cmd_t* (*R_GFX_RENDERER_CREATE_CLEAR_COLOR_CMD)(r_gfx_renderer_t* renderer);
typedef void (*R_GFX_RENDERER_CLEAR)(r_gfx_renderer_t* renderer);
typedef void (*R_GFX_RENDERER_SORT)(r_gfx_renderer_t* renderer);
typedef void (*R_GFX_RENDERER_SUBMIT)(r_gfx_renderer_t* renderer);

typedef struct r_gfx_renderer_api_t {
  r_gfx_renderer_t* renderer;
  R_GFX_RENDERER_ADD_CMD add_cmd;
  R_GFX_RENDERER_CREATE_CLEAR_COLOR_CMD create_clear_color_cmd;
  R_GFX_RENDERER_CLEAR clear;
  R_GFX_RENDERER_SORT sort;
  R_GFX_RENDERER_SUBMIT submit;
} r_gfx_renderer_api_t;

#ifdef __cplusplus
}
#endif