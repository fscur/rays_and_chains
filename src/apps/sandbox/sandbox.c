#include "sandbox.h"
#include "engine/app/r_app.h"
#include "engine/app/r_api_db.h"
#include "engine/app/r_api_db_i.h"
#include "engine/diagnostics/r_logger_i.h"
#include "engine/window/r_window.h"
#include "engine/window/r_window_i.h"
#include "engine/ui/r_ui.h"
#include "engine/ui/r_ui_i.h"
#include "engine/ui/r_ui_renderer_i.h"
#include "engine/string/r_string_i.h"
#include "engine/gfx/r_gfx_renderer.h"
#include "engine/gfx/r_gfx_renderer_i.h"
#include "engine/memory/r_memory_arena.h"
#include "libs/r_logger_outputstring_device/r_logger_outputstring_device.h"
#include "libs/r_ui_imgui/r_ui_imgui.h"
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
sandbox_init(r_app_t* app, r_api_db_i* api_db) {

  sandbox_t* this = (sandbox_t*)app->state;

  this->debug = api_db->find_by_name(api_db->instance, R_LOGGER_OUTPUT_API_NAME);
  this->window = api_db->find_by_name(api_db->instance, R_WINDOW_API_NAME);
  this->ui = api_db->find_by_name(api_db->instance, R_UI_API_NAME);
  this->string = api_db->find_by_name(api_db->instance, R_STRING_API_NAME);
  this->renderer = api_db->find_by_name(api_db->instance, R_GFX_RENDERER_API_NAME);
  this->ui_renderer = api_db->find_by_name(api_db->instance, R_UI_RENDERER_IMGUI_API_NAME);
  sandbox_ui_init(this, app->memory_arena);
}

void //
sandbox_run(sandbox_t* this, r_frame_info_t* frame_info) {
  r_window_t* window = this->window->instance;

  this->window->input(window);
  this->window->update(window);

  r_gfx_renderer_t* renderer = this->renderer->instance;
  r_gfx_cmd_t* cmd = this->renderer->create_clear_color_cmd(renderer);

  r_gfx_clear_color_cmd_t* clear_color_cmd = (r_gfx_clear_color_cmd_t*)cmd->data;
  clear_color_cmd->color = (r_color_t){0.0f, 0.04f, 0.054f, 1.00f};

  this->renderer->clear(renderer);
  this->renderer->add_cmd(renderer, *cmd);
  this->renderer->sort(renderer);
  this->renderer->submit(renderer);

  r_ui_renderer_t* ui_renderer = this->ui_renderer->instance;
  this->ui_renderer->render(ui_renderer);

  this->window->swap_buffers(window);
  this->debug->print_test(this->debug->instance, "%d teste lala");
}

void //
sandbox_destroy(sandbox_t* this) {}