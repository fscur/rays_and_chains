#include "hammer.h"
#include "engine/app/r_app.h"
#include "engine/app/r_app_i.h"
#include "engine/app/r_api_db_i.h"

#include "engine/string/r_string_i.h"

#include "engine/lib/r_lib.h"

#include "engine/logger/r_logger_i.h"
#include "engine/logger/r_logger_device_i.h"
#include "engine/logger/r_logger_file_device_i.h"

#include "engine/window/r_window.h"
#include "engine/window/r_window_i.h"

#include "engine/ui/r_ui.h"
#include "engine/ui/r_ui_i.h"

#include "libs/r_window_glfw/r_window_glfw.h"
#include "libs/r_logger_outputstring_device/r_logger_outputstring_device.h"

internal r_logger_i* Logger = NULL;
internal r_window_i* Window = NULL;
internal r_string_i* String = NULL;
internal r_ui_i* Ui = NULL;

internal hammer_t* _this = NULL;

float t = 0.0f;
bool invert = true;

size_t //
hammer_get_api_size(void) {
  return sizeof(r_app_i);
}

size_t //
hammer_get_size(void) {
  return sizeof(hammer_t);
}

r_app_info_t //
hammer_get_app_info(void) {

  r_app_info_t app_info = {.title = L"hammer app", //
                           .width = 1280,
                           .height = 720,
                           .desired_fps = 60.0,
                           .disable_log_to_file = true};

  return app_info;
}

void //
hammer_load(r_lib_load_info_t* load_info) {
  r_app_i* app_api = (r_app_i*)load_info->api_memory_addr;
  app_api->get_app_info = (R_APP_GET_APP_INFO)load_info->fn(load_info->handle, "hammer_get_app_info");
  app_api->init = (R_APP_INIT)load_info->fn(load_info->handle, "hammer_init");
  app_api->run = (R_APP_RUN)load_info->fn(load_info->handle, "hammer_run");
  app_api->destroy = (R_APP_DESTROY)load_info->fn(load_info->handle, "hammer_destroy");
}

internal void //
hammer_init_logger(r_api_db_i* api_db) {
  r_logger_device_i* outputstring_device =
      api_db->find_by_name(api_db->instance, R_LOGGER_OUTPUTSTRING_DEVICE_API_NAME);

  if (outputstring_device) {
    Logger->add_device(outputstring_device);
  }
}

internal void //
hammer_init_window() {
  r_app_info_t app_info = hammer_get_app_info();
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
hammer_init_globals(hammer_t* this, r_api_db_i* api_db) {
  _this = this;
  Window = api_db->find_by_name(api_db->instance, R_WINDOW_GLFW_API_NAME);
  String = api_db->find_by_name(api_db->instance, R_STRING_API_NAME);
  Logger = api_db->find_by_name(api_db->instance, R_LOGGER_API_NAME);
  Ui = api_db->find_by_name(api_db->instance, R_UI_API_NAME);
}

void //
hammer_init(hammer_t* this, r_api_db_i* api_db) {
  hammer_init_globals(this, api_db);
  hammer_init_logger(api_db);
  hammer_init_window();
  this->running = true;
}

void //
hammer_run(hammer_t* this, r_frame_info_t* frame_info) {
  Logger->debug("Running.");
  Window->process_input(this->main_window);
  Window->set_backcolor(this->main_window, (r_color_t){t, 0.0f, 0.0f, 1.0f});
  Window->swap_buffers(this->main_window);
  this->running = !this->main_window->should_close;

  if (invert) {
    t += 0.01f;
    if (t > 1.0) {
      invert = false;
    }
  } else {
    t -= 0.01f;
    if (t < 0.0) {
      invert = true;
    }
  }
}

void //
hammer_destroy(hammer_t* this) {}