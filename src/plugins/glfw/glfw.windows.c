#include <stdio.h>
#include "glad.c"
#include <GLFW/glfw3.h>

#include "engine/app/r_api_db.h"
#include "engine/diagnostics/r_debug_api.h"
#include "engine/string/r_string_api.h"
#include "engine/window/r_window_api.h"
#include "engine/window/r_window.h"
#include "engine/plugins/r_plugin.h"
#include "engine/string/r_string.h"
#include "plugins/glfw/glfw.c"

#pragma comment(lib, "glfw3dll.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "opengl32.lib")

internal void //
glfw_error_callback(const int error, const char* description) {
  fprintf(stderr, "Error %d: %s\n", error, description);
}

internal void //
set_glfw_window_title(r_window_t* window) {
  glfw_t* state = (glfw_t*)window->impl_state;
  char ansi_title[SHORT_STRING_LENGTH] = {0};
  state->string_api->to_ansi(window->title, ansi_title, SHORT_STRING_LENGTH);
  glfwSetWindowTitle(window->handle, ansi_title);
}

internal void //
glfw_clear_color(const r_window_t* window) {
  glViewport(0, 0, window->width, window->height);
  glClearColor(
      window->back_color.r, window->back_color.g, window->back_color.b, window->back_color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

internal void //
glfw_swap_buffers(const r_window_t* window) {
  glfwSwapBuffers(window->handle);
}

internal void //
glfw_input(const r_window_t* window) {
  glfwPollEvents();
}

internal void //
glfw_update(r_window_t* window) {
  window->should_close = glfwWindowShouldClose(window->handle);
  glfwGetFramebufferSize(window->handle, &window->width, &window->height);
}

void //
glfw_init(glfw_t* this, r_api_db_t* api_db) {
  this->debug_api = api_db->apis[R_DEBUG_API_ID];
  this->window_api = api_db->apis[R_WINDOW_API_ID];
  this->string_api = api_db->apis[R_STRING_API_ID];

  r_window_t* window = this->window_api->window;
  window->title_changed_callback = &set_glfw_window_title;
  window->impl_state = this;

  this->window_api->clear_color = &glfw_clear_color;
  this->window_api->swap_buffers = &glfw_swap_buffers;
  this->window_api->update = &glfw_update;
  this->window_api->input = &glfw_input;

  glfwSetErrorCallback(glfw_error_callback);

  if (!glfwInit())
    return;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  char title[SHORT_STRING_LENGTH] = {0};

  this->string_api->to_ansi(window->title, title, SHORT_STRING_LENGTH);

  window->handle = (void*)glfwCreateWindow(window->width, window->height, title, NULL, NULL);

  glfwMakeContextCurrent(window->handle);

  i32 success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  if (!success)
    printf("[ERROR]");

  glfwSwapInterval(0);

  this->window = window;
}

void //
glfw_destroy(glfw_t* this) {
  glfwTerminate();
}