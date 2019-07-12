#include "engine/app/r_api_db.h"
#include "engine/diagnostics/r_debug_api.h"
#include "engine/window/r_window.h"
#include "engine/window/r_window_api.h"
#include "engine/ui/r_ui_api.h"
#include "engine/string/r_string_api.h"
#include "apps/sandbox/sandbox.c"
#include "engine/gfx/r_gfx_renderer.h"
#include "engine/gfx/r_gfx_renderer_api.h"

void //
sandbox_init(sandbox_t* this, r_api_db_t* api_db) {
  this->debug_api = api_db->apis[R_DEBUG_API_ID];
  this->window_api = api_db->apis[R_WINDOW_API_ID];
  this->ui_api = api_db->apis[R_UI_API_ID];
  this->string_api = api_db->apis[R_STRING_API_ID];
  this->renderer_api = api_db->apis[R_GFX_RENDERER_API_ID];
}

void //
sandbox_run(sandbox_t* this, r_frame_info_t* frame_info) {
  r_window_t* window = this->window_api->window;
  //this->window_api->clear_color(window);
  this->window_api->input(window);
  this->window_api->update(window);

  r_ui_t* ui = this->ui_api->ui;
  this->ui_api->render(ui);

  r_gfx_renderer_t* renderer = this->renderer_api->renderer;
  r_gfx_cmd_t* cmd = this->renderer_api->create_clear_color_cmd(renderer);
  
  r_gfx_clear_color_cmd_t* clear_color_cmd = (r_gfx_clear_color_cmd_t*)cmd->data;
  clear_color_cmd->color = window->back_color;
  
  this->renderer_api->clear(renderer);
  this->renderer_api->add_cmd(renderer, cmd);
  this->renderer_api->sort(renderer);
  this->renderer_api->submit(renderer);
  this->window_api->swap_buffers(window);
}

void //
sandbox_destroy(sandbox_t* this) {}