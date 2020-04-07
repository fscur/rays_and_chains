#include "glad.c"
#include "engine/app/r_api_db_i.h"
#include "engine/app/r_api_db.h"
#include "engine/logger/r_logger_i.h"
#include "engine/window/r_window_i.h"
#include "engine/window/r_window.h"
#include "engine/string/r_string_i.h"
#include "engine/string/r_string.h"
#include "engine/gfx/r_gfx_renderer.h"
#include "engine/gfx/r_gfx_renderer_i.h"
#include "r_gfx_opengl_i.h"
#include "r_gfx_opengl.h"
#include "engine/lib/r_lib.h"

r_logger_i* Logger = NULL;
r_string_i* String = NULL;

internal void //
r_gfx_opengl_clear_color(r_color_t color) {
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

internal void //
r_gfx_opengl_clear_color_dispatcher(void* data) {
  r_gfx_clear_color_cmd_t* cmd = (r_gfx_clear_color_cmd_t*)data;
  r_gfx_opengl_clear_color(cmd->color);
}

internal void //
r_gfx_opengl_bind(r_gfx_renderer_t* renderer) {
  renderer->clear_color_dispatcher = &r_gfx_opengl_clear_color_dispatcher;
}

void //
r_gfx_opengl_init(r_api_db_i* api_db) {
  String = (r_string_i*)api_db->find_by_name(api_db->instance, R_STRING_API_NAME);
  Logger = (r_logger_i*)api_db->find_by_name(api_db->instance, R_LOGGER_API_NAME);
}

void //
r_gfx_opengl_destroy(void* this) {}

size_t //
r_gfx_opengl_get_size(void) {
  return 0;
}

char* //
r_gfx_opengl_get_api_name(void) {
  return R_GFX_OPENGL_API_NAME;
}

size_t //
r_gfx_opengl_get_api_size() {
  return sizeof(r_gfx_opengl_i);
}

void //
r_gfx_opengl_load(r_lib_load_info_t* load_info) {
  r_gfx_opengl_i* api = (r_gfx_opengl_i*)load_info->api_memory_addr;
  
  api->get_api_name = &r_gfx_opengl_get_api_name;
  api->init = &r_gfx_opengl_init;
  api->destroy = &r_gfx_opengl_destroy;
  api->bind = &r_gfx_opengl_bind;
}