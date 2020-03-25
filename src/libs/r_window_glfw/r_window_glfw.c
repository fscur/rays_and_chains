#include <stdio.h>
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

internal void //
r_window_glfw_error_callback(const int error, const char* description) {
  Logger->error("[glfw][%d] %s\n", error, description);
}

internal r_window_t* //
r_window_glfw_create(r_window_desc_t* window_descriptor) {

  r_window_t* window = calloc(1, sizeof(r_window_t));

  glfwSetErrorCallback(r_window_glfw_error_callback);

  if (!glfwInit())
    return NULL;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  char title[R_SHORT_STRING_LENGTH] = {0};
  String->to_ansi(window_descriptor->title, title, R_SHORT_STRING_LENGTH);

  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  window->handle = (void*)glfwCreateWindow(window_descriptor->width, window_descriptor->height, title, NULL, NULL);

  glfwGetWindowSize((GLFWwindow*)window->handle, &window->width, &window->height);
  window->should_close = false;
  String->copy_wide(window_descriptor->title, window->title);

  glfwSetWindowPos(window->handle, window_descriptor->x, window_descriptor->y);
  glfwMakeContextCurrent(window->handle);

  i32 success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  if (!success)
    printf("[ERROR] Could not load glad.");

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
r_window_glfw_set_back_color(r_window_t* window, const r_color_t color) {
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

internal void //
r_window_glfw_destroy_impl() {
  glfwTerminate();
}

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