#include "hammer.h"
#include "engine/app/r_app.h"
#include "engine/app/r_api_db_i.h"
#include "engine/window/r_window.h"
#include "engine/window/r_window_i.h"

#include "engine/diagnostics/r_logger_i.h"
#include "engine/diagnostics/r_logger_device_i.h"
#include "engine/diagnostics/r_logger_file_device_i.h"
#include "libs/r_logger_outputstring_device/r_logger_outputstring_device.h"


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
                           .desired_fps = 60.0};

  return app_info;
}

void //
hammer_load(r_lib_load_info_t* load_info) {
  r_lib_t* lib = (r_lib_t*)load_info->lib_memory_addr;
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "hammer_get_app_info");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "hammer_init");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "hammer_run");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "hammer_destroy");
}

void //
hammer_init(r_app_t* app, r_api_db_i* api_db) {
  hammer_t* this = (hammer_t*)app->state;
  this->debug_api = api_db->find_by_name(api_db->instance, R_LOGGER_API_NAME);

  r_logger_device_i* outputstring_device =
      api_db->find_by_name(api_db->instance, R_LOGGER_OUTPUTSTRING_DEVICE_API_NAME);

  this->debug_api->add_device(outputstring_device);

  this->window_api = api_db->find_by_name(api_db->instance, R_WINDOW_API_NAME);
}

void //
hammer_run(hammer_t* this, r_frame_info_t* frame_info) {
  this->debug_api->debug("Running.");
  r_window_t* window = this->window_api->instance;
  this->window_api->input(window);
  this->window_api->update(window);
  this->window_api->swap_buffers(window);
}

void //
hammer_destroy(hammer_t* this) {}