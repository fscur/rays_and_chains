#include <stdio.h>

// Helper Macros
#ifndef IM_ASSERT
#define IM_ASSERT(_EXPR)            assert(_EXPR)                               // You can override the default assert handler by editing imconfig.h
#endif
#if defined(__clang__) || defined(__GNUC__)
#define IM_FMTARGS(FMT)             __attribute__((format(printf, FMT, FMT+1))) // Apply printf-style warnings to user functions.
#define IM_FMTLIST(FMT)             __attribute__((format(printf, FMT, 0)))
#else
#define IM_FMTARGS(FMT)
#define IM_FMTLIST(FMT)
#endif
#define IM_ARRAYSIZE(_ARR)          ((int)(sizeof(_ARR)/sizeof(*_ARR)))         // Size of a static C-style array. Don't use on pointers!
#define IM_OFFSETOF(_TYPE,_MEMBER)  ((size_t)&(((_TYPE*)0)->_MEMBER))           // Offset of _MEMBER within _TYPE. Standardized as offsetof() in modern C++.
#define IM_UNUSED(_VAR)             ((void)_VAR)                                // Used to silence "unused variable warnings". Often useful as asserts may be stripped out from final builds.

#include "glad.c"
#include <GLFW/glfw3.h>
#include "engine/window/r_window.h"

#pragma comment(lib, "../lib/windows/x64/release/glfw3.lib")
#pragma comment(lib, "../lib/windows/x64/release/cimgui.lib")

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "opengl32.lib")

#include "r_ui.c"

internal void //
error_callback(const int error, const char* description) {
  fprintf(stderr, "Error %d: %s\n", error, description);
}

void //
r_window_create(r_window_t* window) {
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

  GLuint texture_id;
  glGenTextures(1, &texture_id);

  glfwSwapInterval(0);
}

void
r_window_input(r_window_t* window) {
  glfwPollEvents();
}

void
r_window_update(r_window_t* window) {
  window->should_close = glfwWindowShouldClose(window->handle);
  glfwGetFramebufferSize(window->handle, &window->width, &window->height);
}

void
r_window_render(r_window_t* window) {
  glViewport(0, 0, window->width, window->height);

  r_color_t clear_color = window->back_color;
  //glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
  glClearColor(1.0f, clear_color.g, clear_color.b, clear_color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void
r_window_swapbuffers(r_window_t* window) {
  glfwSwapBuffers(window->handle);
}

void //
r_window_destroy(r_window_t* window) {
  glfwTerminate();
}