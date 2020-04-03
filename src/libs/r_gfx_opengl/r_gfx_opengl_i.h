#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_GFX_OPENGL_API_NAME "r_gfx_opengl"

typedef struct r_gfx_renderer_t r_gfx_renderer_t;

typedef struct r_gfx_opengl_i {
  void (*bind)(r_gfx_renderer_t* renderer);
} r_gfx_opengl_i;

#ifdef __cplusplus
}
#endif