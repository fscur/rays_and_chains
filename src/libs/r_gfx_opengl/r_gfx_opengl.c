#include "glad.c"
#include "engine/app/r_api_db.h"
#include "engine/app/r_api_db_i.h"
#include "engine/plugins/r_plugin.h"
#include "engine/gfx/r_gfx_renderer.h"
#include "engine/gfx/r_gfx_renderer_i.h"
#include "engine/diagnostics/r_debug_i.h"
#include "r_gfx_opengl.h"

#pragma comment(lib, "opengl32.lib")

u32 //
r_gfx_opengl_get_id(void) {
  return OPENGL_API_ID;
}

size_t //
r_gfx_opengl_get_size(void) {
  return sizeof(opengl_t);
}

void //
r_gfx_opengl_load(r_lib_load_info_t* load_info) {
  r_lib_t* lib = (r_lib_t*)load_info->lib_memory_addr;
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "r_gfx_opengl_init");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "r_gfx_opengl_destroy");
}

internal void //
opengl_clear_color(r_color_t color) {
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

internal void //
opengl_clear_color_dispatcher(void* data) {
  r_gfx_clear_color_cmd_t* cmd = (r_gfx_clear_color_cmd_t*)data;
  opengl_clear_color(cmd->color);
}

void //
r_gfx_opengl_init(opengl_t* this, r_api_db_i* api_db) {
  this->debug = api_db->instance->apis[R_DEBUG_API_ID];
  this->renderer = api_db->instance->apis[R_GFX_RENDERER_API_ID];

  r_gfx_renderer_t* renderer = this->renderer->instance;
  renderer->clear_color_dispatcher = &opengl_clear_color_dispatcher;

  i32 success = gladLoadGL();

  if (!success)
    printf("[ERROR] Could not load glad.");
}

void //
r_gfx_opengl_destroy(opengl_t* this) {}