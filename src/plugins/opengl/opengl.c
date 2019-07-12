#include "glad.c"
#include "engine/app/r_api_db.h"
#include "engine/plugins/r_plugin.h"
#include "engine/gfx/r_gfx_renderer.h"
#include "engine/gfx/r_gfx_renderer_api.h"
#include "engine/diagnostics/r_debug_api.h"
#include "opengl.h"

#pragma comment(lib, "opengl32.lib")

u32 //
get_id_opengl() {
  return OPENGL_API_ID;
}

size_t //
get_size_opengl() {
  return sizeof(opengl_t);
}

r_plugin_t* //
load_opengl(r_plugin_load_info_t* load_info) {

  r_plugin_t* plugin = (r_plugin_t*)load_info->plugin_memory_addr;
  opengl_t* state = (opengl_t*)load_info->state_memory_addr;

  plugin->handle = load_info->handle;
  plugin->api = NULL;
  plugin->state = state;

  plugin->init = (R_PLUGIN_INIT)load_info->fn(load_info->handle, "opengl_init");
  plugin->destroy = (R_PLUGIN_DESTROY)load_info->fn(load_info->handle, "opengl_destroy");

  return plugin;
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
opengl_init(opengl_t* this, r_api_db_t* api_db) {
  this->debug_api = api_db->apis[R_DEBUG_API_ID];
  this->renderer_api = api_db->apis[R_GFX_RENDERER_API_ID];

  r_gfx_renderer_t* renderer = this->renderer_api->renderer;
  renderer->clear_color_dispatcher = &opengl_clear_color_dispatcher;
  
  i32 success = gladLoadGL();

  if (!success)
    printf("[ERROR]");
}

void //
opengl_destroy(opengl_t* this) {}