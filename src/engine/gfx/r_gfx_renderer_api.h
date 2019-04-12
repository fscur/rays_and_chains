#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_GFX_RENDERER_API_ID 4
#define R_GFX_RENDERER_API_NAME "r_gfx_renderer"

typedef struct r_gfx_renderer_t r_gfx_renderer_t;

typedef void (*R_GFX_RENDERER_ADD_CMD)(r_gfx_renderer_t* renderer, u64 cmd);

typedef struct r_gfx_renderer_api_t {
  r_gfx_renderer_t* renderer;
  R_GFX_RENDERER_ADD_CMD add_cmd;
} r_gfx_renderer_api_t;

#ifdef __cplusplus
}
#endif