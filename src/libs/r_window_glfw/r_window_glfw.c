#include "glad.c"
#include <GLFW/glfw3.h>
#include "engine/app/r_api_db_i.h"
#include "engine/app/r_api_db.h"
#include "engine/logger/r_logger_i.h"
#include "engine/string/r_string_i.h"
#include "engine/window/r_window_i.h"
#include "engine/window/r_window.h"
#include "engine/string/r_string.h"
#include "r_window_glfw.h"
#include "engine/lib/r_lib.h"
#include "r_window_glfw_i.h"

r_logger_i* Logger = NULL;
r_string_i* String = NULL;

internal void //
r_window_glfw_error_callback(const int error, const char* description) {
  Logger->error("[glfw][%d] %s\n", error, description);
}

internal r_window_t* //
r_window_glfw_create(r_window_desc_t* window_descriptor) {

  r_window_t* window = calloc(1, sizeof(r_window_t));

  glfwSetErrorCallback(r_window_glfw_error_callback);

  if (!glfwInit()) {
    Logger->fatal("[glfw] glfwInit failed.");
    exit(1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  char title[R_SHORT_STRING_LENGTH] = {0};
  String->to_ansi(window_descriptor->title, title, R_SHORT_STRING_LENGTH);

  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  window->handle = (void*)glfwCreateWindow(window_descriptor->width, window_descriptor->height, title, NULL, NULL);

  glfwGetWindowSize((GLFWwindow*)window->handle, &window->width, &window->height);
  window->should_close = false;
  String->copy_wide(window->title, window_descriptor->title);

  // glfwSetWindowPos(window->handle, window_descriptor->x, window_descriptor->y);
  glfwMakeContextCurrent(window->handle);

  i32 success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  if (!success) {
    Logger->fatal("[glfw] Could not load glad.");
    exit(1);
  }

  glfwSwapInterval(0);

  return window;
}

internal void //
r_window_glfw_show(r_window_t* window) {}

internal void //
r_window_glfw_hide(r_window_t* window) {}

internal void //
r_window_glfw_process_input(r_window_t* window) {
  glfwPollEvents();

  window->should_close = glfwWindowShouldClose(window->handle);
  glfwGetFramebufferSize(window->handle, &window->width, &window->height);
}

internal void //
r_window_glfw_set_title(r_window_t* window, const wchar_t* title) {
  char ansi_title[R_SHORT_STRING_LENGTH] = {0};
  String->to_ansi(window->title, ansi_title, R_SHORT_STRING_LENGTH);
  glfwSetWindowTitle(window->handle, ansi_title);
}

internal void //
r_window_glfw_set_backcolor(r_window_t* window, const r_color_t color) {
  // todo: filipe.scur@gmail.com | 1/3/2020
  // remove dependency and use gfx renderer functions
  glViewport(0, 0, window->width, window->height);
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

internal void //
r_window_glfw_swap_buffers(const r_window_t* window) {
  glfwSwapBuffers(window->handle);
}

internal char* //
r_window_glfw_get_api_name(void) {
  return R_WINDOW_GLFW_API_NAME;
}

internal void //
r_window_glfw_init(r_window_glfw_i* api, r_api_db_i* api_db) {
  String = (r_string_i*)api_db->find_by_name(api_db->instance, R_STRING_API_NAME);
  Logger = (r_logger_i*)api_db->find_by_name(api_db->instance, R_LOGGER_API_NAME);
}

internal void //
r_window_glfw_destroy(r_window_t* window) {
  glfwTerminate();
}

size_t //
r_window_glfw_get_size(void) {
  return 0;
}

size_t //
r_window_glfw_get_api_size(void) {
  return sizeof(r_window_glfw_i);
}

void //
r_window_glfw_load(r_lib_load_info_t* load_info) {
  r_window_glfw_i* api = (r_window_glfw_i*)load_info->api_memory_addr;
  api->get_api_name = &r_window_glfw_get_api_name;
  api->init = &r_window_glfw_init;
  api->destroy = &r_window_glfw_destroy;
  api->create = &r_window_glfw_create;
  api->show = &r_window_glfw_show;
  api->set_title = &r_window_glfw_set_title;
  api->set_backcolor = &r_window_glfw_set_backcolor;
  api->process_input = &r_window_glfw_process_input;
  api->swap_buffers = &r_window_glfw_swap_buffers;
}