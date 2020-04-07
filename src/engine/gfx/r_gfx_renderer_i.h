#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_GFX_RENDERER_API_NAME "r_gfx_renderer"

typedef struct r_gfx_renderer_t r_gfx_renderer_t;

typedef struct r_gfx_renderer_i {
  r_gfx_renderer_t* (*create)();
  void (*add_cmd)(r_gfx_renderer_t* instance, r_gfx_cmd_t cmd);
  r_gfx_cmd_t* (*create_clear_color_cmd)(const r_gfx_renderer_t* instance);
  void (*clear)(r_gfx_renderer_t* instance);
  void (*sort)(r_gfx_renderer_t* instance);
  void (*submit)(const r_gfx_renderer_t* instance);
} r_gfx_renderer_i;

void //
r_string_register_api(r_api_db_t* api_db, r_memory_arena_t* apis_arena);

#ifdef __cplusplus
}
#endif