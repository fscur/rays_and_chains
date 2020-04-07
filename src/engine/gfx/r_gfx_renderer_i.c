#include "engine/memory/r_memory_arena.h"
#include "engine/app/r_api_db.h"
#include "r_gfx_renderer.h"
#include "r_gfx_renderer_i.h"

void //
r_gfx_renderer_register_api(r_api_db_t* api_db, r_memory_arena_t* apis_arena) {
  r_gfx_renderer_i* gfx_renderer_api = r_memory_arena_push_struct(apis_arena, r_gfx_renderer_i);

  gfx_renderer_api->add_cmd = &r_gfx_renderer_add_cmd;
  gfx_renderer_api->sort = &r_gfx_renderer_sort;
  gfx_renderer_api->submit = &r_gfx_renderer_submit;
  gfx_renderer_api->clear = &r_gfx_renderer_clear;
  gfx_renderer_api->create_clear_color_cmd = &r_gfx_renderer_create_clear_color_buffer_cmd;

  r_api_db_add(api_db, R_GFX_RENDERER_API_NAME, gfx_renderer_api);
}