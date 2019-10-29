#include "sandbox.h"
#include "engine/app/r_app.h"
#include "engine/app/r_api_db.h"
#include "engine/diagnostics/r_debug_api.h"
#include "engine/window/r_window.h"
#include "engine/window/r_window_api.h"
#include "engine/ui/r_ui.h"
#include "engine/ui/r_ui_api.h"
#include "engine/string/r_string_api.h"
#include "engine/gfx/r_gfx_renderer.h"
#include "engine/gfx/r_gfx_renderer_api.h"
#include "engine/memory/r_memory_block.h"
#include "sandbox_ui.c"

u32 //
sandbox_get_id(void) {
  return 0;
}

size_t //
sandbox_get_size(void) {
  return sizeof(sandbox_t) + //
         sandbox_get_sizeof_ui();
}

void //
sandbox_load(r_lib_load_info_t* load_info) {
  r_lib_t* lib = (r_lib_t*)load_info->lib_memory_addr;
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "sandbox_get_app_info");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "sandbox_init");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "sandbox_run");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "sandbox_destroy");
}

r_app_info_t //
sandbox_get_app_info(void) {

  r_app_info_t app_info = {
      .title = L"sandbox app", .width = 1280, .height = 720, .desired_fps = 30.0};

  return app_info;
}

void //
sandbox_init(r_app_t* app, r_api_db_t* api_db) {

  sandbox_t* this = (sandbox_t*)app->state;

  this->debug_api = api_db->apis[R_DEBUG_API_ID];
  this->window_api = api_db->apis[R_WINDOW_API_ID];
  this->ui_api = api_db->apis[R_UI_API_ID];
  this->string_api = api_db->apis[R_STRING_API_ID];
  this->renderer_api = api_db->apis[R_GFX_RENDERER_API_ID];

  init_ui(this, app->memory_block);
}

void //
sandbox_run(sandbox_t* this, r_frame_info_t* frame_info) {
  r_window_t* window = this->window_api->window;

  this->window_api->input(window);
  this->window_api->update(window);

  r_gfx_renderer_t* renderer = this->renderer_api->renderer;
  r_gfx_cmd_t* cmd = this->renderer_api->create_clear_color_cmd(renderer);

  r_gfx_clear_color_cmd_t* clear_color_cmd = (r_gfx_clear_color_cmd_t*)cmd->data;
  clear_color_cmd->color = (r_color_t){0.0f, 0.04f, 0.054f, 1.00f};

  this->renderer_api->clear(renderer);
  this->renderer_api->add_cmd(renderer, cmd);
  this->renderer_api->sort(renderer);
  this->renderer_api->submit(renderer);

  this->ui_api->begin(this->ui_api);
  this->ui_api->render(this->ui_api);
  this->ui_api->end(this->ui_api);

  this->window_api->swap_buffers(window);
}

void //
sandbox_destroy(sandbox_t* this) {}