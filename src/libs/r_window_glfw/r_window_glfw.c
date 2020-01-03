#include "engine\window\r_window_i.h"
#include "engine\window\r_window.h"
#include "engine\string\r_string_i.h"
#include "engine\logger\r_logger_i.h"
#include "r_window_glfw.h"
#include "r_window_glfw.impl.h"

size_t //
r_window_glfw_get_size(void) {
  return 0;
}

size_t //
r_window_glfw_get_api_size() {
  return sizeof(r_window_i);
}

void //
r_window_glfw_load(r_lib_load_info_t* load_info) {
  R_LIB_LOADER_FN fn = load_info->fn;
  void* handle = load_info->handle;
  r_lib_i* lib_api = (r_lib_i*)load_info->api_memory_addr;
  lib_api->init = (R_LIB_INIT)fn(handle, "r_window_glfw_init");
  lib_api->destroy = (R_LIB_DESTROY)fn(handle, "r_window_glfw_destroy");
}

void //
r_window_glfw_init(r_window_t* window, r_api_db_i* api_db) {

  local r_window_i api;
  api.create = &r_window_glfw_create;
  api.show = &r_window_glfw_show;
  api.set_title = &r_window_glfw_set_title;
  api.set_back_color = &r_window_glfw_set_back_color;
  api.process_input = &r_window_glfw_process_input;
  api.swap_buffers = &r_window_glfw_swap_buffers;

  api_db->add(api_db->instance, R_WINDOW_GLFW_API_NAME, &api);

  String = (r_string_i*)api_db->find_by_name(api_db->instance, "r_string");
  Logger = (r_logger_i*)api_db->find_by_name(api_db->instance, "r_logger");
}

void //
r_window_glfw_destroy(r_window_t* window) {
  r_window_glfw_destroy_impl();
}