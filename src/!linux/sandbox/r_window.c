#include <gl3w/GL/gl3w.c>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "../app/r_window.h"

static void
error_callback(const int error, const char* description) {
  fprintf(stderr, "Error %d: %s\n", error, description);
}

void
window_create(App_Window* window) {
  // todo: how to create window with app state????
  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    return;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window->handle = (void*)glfwCreateWindow(
      window->width, window->height, window->title, NULL, NULL);

  glfwMakeContextCurrent(window->handle);
  glfwSwapInterval(0);
  gl3wInit();
}

void
window_input(App_Window* window) {
  glfwPollEvents();
}

void
window_update(App_Window* window) {
  window->should_close = glfwWindowShouldClose(window->handle);
  glfwGetFramebufferSize(window->handle, &window->width, &window->height);
}

void
window_render(App_Window* window) {
  glViewport(0, 0, window->width, window->height);

  Color clear_color = window->back_color;
  glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void
window_swapbuffers(App_Window* window) {
  glfwSwapBuffers(window->handle);
}

void
window_destroy(App_Window* window) {
  glfwTerminate();
}