#include <stdio.h>
#include "glad.c"

#include "imgui_impl_opengl3.c"
#include "imgui_impl_glfw.c"

#include "engine/app/r_api_db.h"
#include "engine/app/r_api_db_i.h"
#include "engine/diagnostics/r_debug_i.h"
#include "engine/window/r_window.h"
#include "engine/window/r_window_i.h"
#include "engine/ui/r_ui.h"
#include "engine/ui/r_ui_i.h"
#include "engine/plugins/r_plugin.h"
#include "engine/string/r_string.h"
#include "engine/string/r_string_i.h"
#include "engine/ui/r_ui_renderer_i.h"
#include "r_ui_imgui_render.c"
#include "r_ui_imgui.c"

#pragma comment(lib, "cimgui.lib")
#pragma comment(lib, "glfw3dll.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "opengl32.lib")

internal void //
r_ui_imgui_render(r_ui_renderer_t* this) {
  
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  igNewFrame();

  r_ui_t* ui = this->ui_api->instance;
  r_ui_imgui_init_theme(ui);
  render_widgets(this, ui);

  if (ui->show_demo) {
    bool open = true;
    igShowDemoWindow(&open);
  }

  igRender();
  ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
}

void //
r_ui_imgui_init(r_ui_renderer_t* this, r_api_db_i* api_db) {
  this->debug_api = api_db->instance->apis[R_DEBUG_API_ID];
  this->window_api = api_db->instance->apis[R_WINDOW_API_ID];
  this->ui_api = api_db->instance->apis[R_UI_API_ID];

  r_window_t* window = this->window_api->instance;
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

  ImFontAtlas_AddFontFromFileTTF(this->io->Fonts, "../res/fonts/SegoeUI-Regular.ttf", 18.0f, 0, 0);

  local r_ui_renderer_i ui_renderer;
  ui_renderer.instance = this;
  ui_renderer.render = &r_ui_imgui_render;

  api_db->add( //
      api_db->instance,
      R_UI_RENDERER_IMGUI_API_ID,
      R_UI_RENDERER_IMGUI_API_NAME,
      &ui_renderer);
}

void //
r_ui_imgui_destroy(r_ui_renderer_t* this) {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  igDestroyContext(this->context);
}