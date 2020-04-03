#include "sandbox.h"
#include "engine/app/r_app.h"
#include "engine/app/r_app_i.h"
#include "engine/app/r_api_db_i.h"
#include "engine/logger/r_logger_i.h"
#include "engine/logger/r_logger_device_i.h"
#include "engine/logger/r_logger_file_device_i.h"
#include "engine/string/r_string_i.h"
#include "engine/ui/r_ui_i.h"
#include "engine/ui/r_ui.h"
#include "engine/ui/r_ui_renderer_i.h"
#include "engine/window/r_window_i.h"
// todo: filipe.scur@gmail.com | 3/31/2020
// we should move all the types and headers away from the engine functions
// ie. move r_window_t to a new file, so that the consumers of the api
// dont have access to the r_window functions but can use its types
#include "engine/window/r_window.h"
#include "sandbox_ui.c"

#include "libs/r_logger_outputstring_device/r_logger_outputstring_device.h"
#include "libs/r_window_glfw/r_window_glfw.h"
#include "libs/r_ui_renderer_imgui/r_ui_renderer_imgui.h"
internal r_logger_i* Logger = NULL;
internal r_window_i* Window = NULL;
internal r_string_i* String = NULL;
internal r_ui_i* Ui = NULL;
internal r_ui_renderer_i* Ui_Renderer = NULL;

internal sandbox_t* _this = NULL;

internal void //
sandbox_init_globals(sandbox_t* this, r_api_db_i* api_db) {
  _this = this;
  Window = api_db->find_by_name(api_db->instance, R_WINDOW_GLFW_API_NAME);
  String = api_db->find_by_name(api_db->instance, R_STRING_API_NAME);
  Logger = api_db->find_by_name(api_db->instance, R_LOGGER_API_NAME);
  Ui = api_db->find_by_name(api_db->instance, R_UI_API_NAME);
  Ui_Renderer = api_db->find_by_name(api_db->instance, R_UI_RENDERER_IMGUI_API_NAME);
}

internal void //
sandbox_init_logger(r_api_db_i* api_db) {
  r_logger_device_i* outputstring_device =
      api_db->find_by_name(api_db->instance, R_LOGGER_OUTPUTSTRING_DEVICE_API_NAME);

  if (outputstring_device) {
    Logger->add_device(outputstring_device);
  }
}

internal void //
sandbox_init_window() {
  r_app_info_t app_info = sandbox_get_app_info();
  r_window_desc_t window_desc = {.x = 0,
                                 .y = 0,
                                 .width = app_info.width,
                                 .height = app_info.height,
                                 .back_color = (r_color_t){0.0f, 0.0f, 0.0f, 1.0f}};

  String->copy_wide(window_desc.title, app_info.title);
  _this->main_window = Window->create(&window_desc);
  Window->show(_this->main_window);
}

internal void //
sandbox_init_ui() {
  _this->ui = Ui->create();
  _this->ui_renderer = Ui_Renderer->create(_this->main_window);
  sandbox_ui_init(_this, Ui);
}

u32 //
sandbox_get_id(void) {
  return 0;
}

size_t //
sandbox_get_api_size(void) {
  return sizeof(r_app_i);
}

size_t //
sandbox_get_size(void) {
  return sizeof(sandbox_t) + sandbox_get_sizeof_ui();
}

void //
sandbox_load(r_lib_load_info_t* load_info) {
  r_app_i* app_api = (r_app_i*)load_info->api_memory_addr;
  app_api->get_app_info = (R_APP_GET_APP_INFO)load_info->fn(load_info->handle, "sandbox_get_app_info");
  app_api->init = (R_APP_INIT)load_info->fn(load_info->handle, "sandbox_init");
  app_api->run = (R_APP_RUN)load_info->fn(load_info->handle, "sandbox_run");
  app_api->destroy = (R_APP_DESTROY)load_info->fn(load_info->handle, "sandbox_destroy");
}

r_app_info_t //
sandbox_get_app_info(void) {

  r_app_info_t app_info = {//
                           .title = L"sandbox app",
                           .width = 1280,
                           .height = 720,
                           .desired_fps = 30.0,
                           .disable_log_to_file = true};

  return app_info;
}

void //
sandbox_init(sandbox_t* this, r_api_db_i* api_db) {
  sandbox_init_globals(this, api_db);
  sandbox_init_logger(api_db);
  sandbox_init_window();
  sandbox_init_ui();
  this->running = true;
}

void //
sandbox_run(sandbox_t* this, r_frame_info_t* frame_info) {

  Window->process_input(this->main_window);

  // r_gfx_renderer_t* renderer = this->renderer->instance;
  // r_gfx_cmd_t* cmd = this->renderer->create_clear_color_cmd(renderer);

  // r_gfx_clear_color_cmd_t* clear_color_cmd = (r_gfx_clear_color_cmd_t*)cmd->data;
  // clear_color_cmd->color = (r_color_t){0.0f, 0.04f, 0.054f, 1.00f};

  // this->renderer->clear(renderer);
  // this->renderer->add_cmd(renderer, *cmd);
  // this->renderer->sort(renderer);
  // this->renderer->submit(renderer);
  Window->set_backcolor(this->main_window, (r_color_t){1.0f, 0.0f, 0.0f, 1.0f});
  Ui_Renderer->render(this->ui_renderer, this->ui);
  Window->swap_buffers(this->main_window);
  this->running = !this->main_window->should_close;
}

void //
sandbox_destroy(sandbox_t* this) {
  printf("Destroy.\n");
}