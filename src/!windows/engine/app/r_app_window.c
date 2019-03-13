#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine/app/r_app_window.h"

internal void //
error_callback(const int error, const char* description) {
  fprintf(stderr, "Error %d: %s\n", error, description);
}

void //
r_app_window_create(r_app_window_t* window) {
  printf("Created window.");
  // todo: how to create window with app state????
  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    return;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window->handle =
      (void*)glfwCreateWindow(window->width, window->height, window->title, NULL, NULL);

  glfwMakeContextCurrent(window->handle);

  i32 success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  if (!success)
    printf("[ERROR]");

  glfwSwapInterval(0);
}

void
r_app_window_input(r_app_window_t* window) {
  glfwPollEvents();
}

void
r_app_window_update(r_app_window_t* window) {
  window->should_close = glfwWindowShouldClose(window->handle);
  glfwGetFramebufferSize(window->handle, &window->width, &window->height);
}

void
r_app_window_render(r_app_window_t* window) {
  glViewport(0, 0, window->width, window->height);

  r_color_t clear_color = window->back_color;
  glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void
r_app_window_swapbuffers(r_app_window_t* window) {
  glfwSwapBuffers(window->handle);
}

void //
r_app_window_destroy(r_app_window_t* window) {
  glfwTerminate();
}