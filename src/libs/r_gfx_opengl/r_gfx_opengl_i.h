#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_GFX_OPENGL_API_NAME "r_gfx_opengl"

typedef struct r_gfx_renderer_t r_gfx_renderer_t;
typedef struct r_gfx_opengl_i r_gfx_opengl_i;

typedef struct r_gfx_opengl_i {
  size_t (*get_size)(void);
  char* (*get_api_name)(void);
  void (*init)(r_api_db_i* db);
  void (*destroy)(void* state);
  void (*bind)(r_gfx_renderer_t* renderer);
} r_gfx_opengl_i;

#ifdef __cplusplus
}
#endif