#include "glad.c"
#include "imgui_impl_opengl3.c"
#include "imgui_impl_glfw.c"

#include "engine/app/r_api_db_i.h"
#include "engine/app/r_api_db.h"
#include "engine/window/r_window.h"
#include "engine/window/r_window_i.h"
#include "engine/logger/r_logger.h"
#include "engine/logger/r_logger_i.h"
#include "engine/ui/r_ui_i.h"
#include "engine/ui/r_ui.h"
#include "engine/ui/r_ui_renderer_i.h"
#include "engine/lib/r_lib.h"

#include "r_ui_renderer_imgui.h"
#include "r_ui_renderer_imgui_i.h"

typedef struct ImGuiContext ImGuiContext;
typedef struct ImGuiIO ImGuiIO;
typedef struct r_window_t r_window_t;
typedef struct r_ui_renderer_t {
  ImGuiContext* context;
  ImGuiIO* io;
  r_window_t* window;
} r_ui_renderer_t;

r_logger_i* Logger = NULL;
r_ui_i* Ui = NULL;

internal void //
r_ui_renderer_imgui_render(r_ui_renderer_t* this, r_ui_t* ui) {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();

  igNewFrame();

  r_ui_renderer_imgui_init_theme(ui);
  render_widgets(this, ui);

  if (ui->show_demo) {
    igShowDemoWindow(&ui->show_demo);
  }

  igRender();

  ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
}

internal r_ui_renderer_t* //
r_ui_renderer_imgui_create(r_window_t* window) {
  r_ui_renderer_t* ui_renderer = calloc(1, sizeof(r_ui_renderer_t));

  ui_renderer->context = igCreateContext(NULL);
  ui_renderer->io = igGetIO();

  // todo: filipe.scur@gmail.com
  // embed the default font into the dll

  ImFontAtlas_AddFontFromFileTTF(ui_renderer->io->Fonts, "../../res/fonts/SegoeUI-Regular.ttf", 18.0f, 0, 0);

  if (!glfwInit()) {
    exit(1);
  }

  if (!gladLoadGL()) {
    exit(1);
  }

  assert(window->handle);
  ImGui_ImplGlfw_InitForOpenGL(window->handle, true);

  const char* glsl_version = "#version 130";
  ImGui_ImplOpenGL3_Init(glsl_version);

  return ui_renderer;
}

void //
r_ui_renderer_imgui_init(r_ui_renderer_imgui_i* api, r_api_db_i* api_db) {
  Logger = (r_logger_i*)api_db->find_by_name(api_db->instance, R_LOGGER_API_NAME);
  Ui = (r_ui_i*)api_db->find_by_name(api_db->instance, R_UI_API_NAME);
}

void //
r_ui_renderer_imgui_destroy(r_ui_renderer_t* this) {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  igDestroyContext(this->context);
}

size_t //
r_ui_renderer_imgui_get_size(void) {
  return 0;
}

char* //
r_ui_renderer_imgui_get_api_name(void) {
  return R_UI_RENDERER_IMGUI_API_NAME;
}

size_t //
r_ui_renderer_imgui_get_api_size(void) {
  return sizeof(r_ui_renderer_imgui_i);
}

void //
r_ui_renderer_imgui_load(r_lib_load_info_t* load_info) {
  r_ui_renderer_imgui_i* api = (r_ui_renderer_imgui_i*)load_info->api_memory_addr;
  api->get_api_name = &r_ui_renderer_imgui_get_api_name;
  api->init = &r_ui_renderer_imgui_init;
  api->destroy = &r_ui_renderer_imgui_destroy;
  api->render = &r_ui_renderer_imgui_render;
  api->create = &r_ui_renderer_imgui_create;
}