#include <stdio.h>
#include "glad.c"
// clang-format off
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
// clang-format on

#include "imgui_impl_opengl3.c"
#include "imgui_impl_glfw.c"

#include "engine/app/r_api_db.h"
#include "engine/diagnostics/r_debug_api.h"
#include "engine/window/r_window_api.h"
#include "engine/window/r_window.h"
#include "engine/plugins/r_plugin.h"
#include "engine/string/r_string.h"
#include "plugins/imgui/imgui.c"

#pragma comment(lib, "cimgui.lib")
#pragma comment(lib, "glfw3dll.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "opengl32.lib")

void //
imgui_init(imgui_t* this, r_api_db_t* api_db) {
  this->debug_api = api_db->apis[R_DEBUG_API_ID];
  this->window_api = api_db->apis[R_WINDOW_API_ID];

  r_window_t* window = this->window_api->window;
  assert(window->handle);

  i32 success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  if (!success)
    this->debug_api->print("[ERROR]");
    
  const char* glsl_version = "#version 130";
  this->context = igCreateContext(NULL);

  ImGui_ImplOpenGL3_Init(glsl_version);
  ImGui_ImplGlfw_InitForOpenGL(window->handle, true);

  struct ImGuiStyle* style = igGetStyle();
  igStyleColorsDark(style);

  this->io = igGetIO();

  // todo: embed the default font into the dll
  ImFontAtlas_AddFontFromFileTTF(
      this->io->Fonts, "../res/fonts/UbuntuMono-Regular.ttf", 16.0f, 0, 0);
}

void //
imgui_render(imgui_t* this) {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  igNewFrame();

  local bool open = true;
  igShowDemoWindow(&open);

  igRender();
  ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
}

void //
imgui_destroy(imgui_t* this) {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  igDestroyContext(this->context);
}