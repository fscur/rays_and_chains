#include "hammer.h"
#include "engine/app/r_app.h"
#include "engine/app/r_api_db_i.h"

#include "engine/string/r_string_i.h"

#include "engine/logger/r_logger_i.h"
#include "engine/logger/r_logger_device_i.h"
#include "engine/logger/r_logger_file_device_i.h"
#include "libs/r_logger_outputstring_device/r_logger_outputstring_device.h"

#include "engine/window/r_window.h"
#include "engine/window/r_window_i.h"

internal r_logger_i* _logger = NULL;
internal r_window_i* _window = NULL;
internal r_string_i* _string = NULL;
internal hammer_t* _this = NULL;

u32 //
hammer_get_id(void) {
  return 0;
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
  r_lib_t* lib = (r_lib_t*)load_info->lib_memory_addr;

  lib->api.init = load_info->fn(load_info->handle, "hammer_init");
  lib->api.destroy = load_info->fn(load_info->handle, "hammer_destroy");

  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "hammer_get_app_info");
  lib->functions[lib->fn_count++] = lib->api.init;
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "hammer_run");
  lib->functions[lib->fn_count++] = lib->api.destroy;
}

internal void //
hammer_init_logger(r_api_db_i* api_db) {
  r_logger_device_i* outputstring_device =
      api_db->find_by_name(api_db->instance, R_LOGGER_OUTPUTSTRING_DEVICE_API_NAME);

  _logger->add_device(outputstring_device);
}

internal void //
hammer_init_window() {
  r_app_info_t app_info = hammer_get_app_info();
  r_window_desc_t window_desc = {.x = 0,
                                 .y = 0,
                                 .width = app_info.width,
                                 .height = app_info.height,
                                 .back_color = (r_color_t){0.0f, 0.0f, 0.0f, 1.0f}};

  _string->copy_wide(window_desc.title, app_info.title);
  _this->main_window = _window->create(window_desc);
  _window->show(_this->main_window);
}

internal void //
hammer_init_globals(hammer_t* this, r_api_db_i* api_db) {
  _this = this;
  _window = api_db->find_by_name(api_db->instance, R_WINDOW_API_NAME);
  _string = api_db->find_by_name(api_db->instance, R_STRING_API_NAME);
  _logger = api_db->find_by_name(api_db->instance, R_LOGGER_API_NAME);
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

  _logger->debug("Running.");
  _window->process_input(this->main_window);
  this->running = !this->main_window->should_close;
}

void //
hammer_destroy(hammer_t* this) {}