#include <stdio.h>

#include "glad.c"
#include <GLFW/glfw3.h>
#include "engine/window/r_window.h"

#include "engine/media/r_media_bitmap.c"
#include "engine/gfx/r_gfx_raytracer.c"
#include "!windows/engine/string/r_string.windows.c"

#pragma comment(lib, "../lib/windows/x64/release/glfw3dll.lib")
#pragma comment(lib, "../lib/windows/x64/release/cimgui.lib")

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "opengl32.lib")

internal void //
error_callback(const int error, const char* description) {
  fprintf(stderr, "Error %d: %s\n", error, description);
}

void //
r_window_create(r_window_t* this) {
  // todo: how to create window with app state????
  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    return;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  char title[MAX_FILE_NAME_LENGTH] = {0};

  r_string_to_ansi(this->title, title, MAX_FILE_NAME_LENGTH);

  this->handle = (void*)glfwCreateWindow(this->width, this->height, title, NULL, NULL);

  glfwMakeContextCurrent(this->handle);

  i32 success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  if (!success)
    printf("[ERROR]");

  glfwSwapInterval(0);
}

void
r_window_input(r_window_t* this) {
  glfwPollEvents();
}

void
r_window_update(r_window_t* this) {
  this->should_close = glfwWindowShouldClose(this->handle);
  glfwGetFramebufferSize(this->handle, &this->width, &this->height);
}

void
r_window_render(r_window_t* this) {
  glViewport(0, 0, this->width, this->height);
  glClearColor(this->back_color.r, this->back_color.g, this->back_color.b, this->back_color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void
r_window_swapbuffers(r_window_t* this) {
  glfwSwapBuffers(this->handle);
}

void //
r_window_destroy(r_window_t* this) {
  glfwTerminate();
}

void //
r_window_set_title(r_window_t* this, const wchar_t* title) {
  wsprintf(this->title, title);
  char ansi_title[MAX_FILE_NAME_LENGTH] = {0};
  r_string_to_ansi(this->title, ansi_title, MAX_FILE_NAME_LENGTH);
  glfwSetWindowTitle(this->handle, ansi_title);
}

void //
r_window_set_back_color(r_window_t* this, const r_color_t color) {
  this->back_color = color;
}