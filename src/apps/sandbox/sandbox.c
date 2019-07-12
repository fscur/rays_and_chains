#include "sandbox.h"
#include "engine/app/r_app.h"
#include "engine/app/r_api_db.h"
#include "engine/diagnostics/r_debug_api.h"
#include "engine/window/r_window.h"
#include "engine/window/r_window_api.h"
#include "engine/ui/r_ui_api.h"
#include "engine/string/r_string_api.h"
#include "engine/gfx/r_gfx_renderer.h"
#include "engine/gfx/r_gfx_renderer_api.h"

u32 //
get_id_sandbox() {
  return 0;
}

size_t //
get_size_sandbox() {
  return sizeof(sandbox_t);
}

void //
load_sandbox(r_lib_load_info_t* load_info) {
  r_lib_t* lib = (r_lib_t*)load_info->lib_memory_addr;
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "sandbox_init");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "sandbox_run");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "sandbox_destroy");
}

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

  r_gfx_renderer_t* renderer = this->renderer_api->renderer;
  r_gfx_cmd_t* cmd = this->renderer_api->create_clear_color_cmd(renderer);
  
  r_gfx_clear_color_cmd_t* clear_color_cmd = (r_gfx_clear_color_cmd_t*)cmd->data;
  clear_color_cmd->color = window->back_color;
  
  this->renderer_api->clear(renderer);
  this->renderer_api->add_cmd(renderer, cmd);
  this->renderer_api->sort(renderer);
  this->renderer_api->submit(renderer);

  r_ui_t* ui = this->ui_api->ui;
  this->ui_api->render(ui);

  this->window_api->swap_buffers(window);
}

void //
sandbox_destroy(sandbox_t* this) {}