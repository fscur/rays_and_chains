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
#include "engine/window/r_window.h"
#include "engine/window/r_window_api.h"
#include "engine/ui/r_ui.h"
#include "engine/ui/r_ui_api.h"
#include "engine/plugins/r_plugin.h"
#include "engine/string/r_string.h"
#include "engine/string/r_string_api.h"
#include "r_ui_imgui.c"

#pragma comment(lib, "cimgui.lib")
#pragma comment(lib, "glfw3dll.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "opengl32.lib")

internal void //
r_ui_imgui_begin(r_ui_api_t* this) {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  igNewFrame();
}

internal ImVec4
from(r_color_t color) {
  return (ImVec4){color.r, color.g, color.b, color.a};
}

internal void //
render_widget(imgui_t* this, r_ui_t* ui, r_ui_widget_t* widget);

internal void //
render_menu_item(imgui_t* this, r_ui_t* ui, r_ui_menu_item_t* menu_item) {
  if (igMenuItemBool(menu_item->label_ansi, menu_item->shortcut_ansi, false, menu_item->enabled)) {
    if (menu_item->callback)
      menu_item->callback(menu_item->context);
  }
}

internal void //
render_menu(imgui_t* this, r_ui_t* ui, r_ui_menu_t* menu) {

  r_ui_theme_t* theme = ui->active_theme;

  igPushStyleVarFloat(ImGuiStyleVar_PopupBorderSize, theme->border_size);
  igPushStyleVarFloat(ImGuiStyleVar_WindowRounding, 0.0f);
  igPushStyleColor(ImGuiCol_Border, from(theme->border_color));
  igPushStyleColor(ImGuiCol_WindowBg, from(theme->menu_background_color));
  igPushStyleColor(ImGuiCol_PopupBg, from(theme->menu_background_color));

  local bool is_open = true;
  if (igBeginMenu(menu->label_ansi, &is_open)) {
    for (size_t i = 0; i < menu->widget->item_count; i++) {
      render_widget(this, ui, menu->widget->items[i]);
    }
    igEndMenu();
  }

  igPopStyleColor(3);
  igPopStyleVar(2);
}

internal void //
render_main_menu(imgui_t* this, r_ui_t* ui, r_ui_menu_t* menu) {

  r_ui_theme_t* theme = ui->active_theme;

  igPushStyleVarFloat(ImGuiStyleVar_PopupBorderSize, theme->border_size);
  igPushStyleVarFloat(ImGuiStyleVar_WindowRounding, 0.0f);
  igPushStyleColor(ImGuiCol_Border, from(theme->border_color));
  igPushStyleColor(ImGuiCol_WindowBg, from(theme->menu_background_color));
  igPushStyleColor(ImGuiCol_PopupBg, from(theme->menu_background_color));

  if (igBeginMainMenuBar()) {

    for (size_t i = 0; i < menu->widget->item_count; i++) {
      render_widget(this, ui, menu->widget->items[i]);
    }

    igEndMainMenuBar();
  }

  igPopStyleColor(3);
  igPopStyleVar(2);
}

internal void //
render_frame(imgui_t* this, r_ui_t* ui, r_ui_frame_t* frame) {
  if (!frame->is_open)
    return;

  igBegin(frame->title_ansi, &frame->is_open, ImGuiWindowFlags_None);
  for (size_t i = 0; i < frame->widget->item_count; i++) {
    render_widget(this, ui, frame->widget->items[i]);
  }
  igEnd();
}

internal void //
render_demo_window(imgui_t* this, r_ui_t* ui, r_ui_frame_t* frame) {
  if (!frame->is_open)
    return;

  local bool is_open;
  igShowDemoWindow(&is_open);
}

internal void //
render_widget(imgui_t* this, r_ui_t* ui, r_ui_widget_t* widget) {
  r_ui_widget_type_t widget_type = widget->type;
  switch (widget_type) {
  case R_UI_WIDGET_TYPE_FRAME:
    render_frame(this, ui, (r_ui_frame_t*)widget->data);
    break;
  case R_UI_WIDGET_TYPE_MAIN_MENU:
    render_main_menu(this, ui, (r_ui_menu_t*)widget->data);
    break;
  case R_UI_WIDGET_TYPE_MENU:
    render_menu(this, ui, (r_ui_menu_t*)widget->data);
    break;
  case R_UI_WIDGET_TYPE_MENU_ITEM:
    render_menu_item(this, ui, (r_ui_menu_item_t*)widget->data);
    break;
  }
}

internal void //
render_widgets(imgui_t* this, r_ui_t* ui) {
  r_ui_widget_t* root = ui->root;
  for (size_t i = 0; i < root->item_count; i++) {
    r_ui_widget_t* child = root->items[i];
    render_widget(this, ui, child);
  }
}

internal void //
r_ui_imgui_render(r_ui_api_t* ui_api) {
  imgui_t* this = ui_api->impl_state;
  render_widgets(this, ui_api->ui);
}

internal void //
r_ui_imgui_end(r_ui_api_t* ui_api) {
  igRender();
  ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
}

void //
imgui_init(imgui_t* this, r_api_db_t* api_db) {
  this->debug_api = api_db->apis[R_DEBUG_API_ID];
  this->window_api = api_db->apis[R_WINDOW_API_ID];
  this->ui_api = api_db->apis[R_UI_API_ID];

  r_window_t* window = this->window_api->window;
  assert(window->handle);

  this->ui_api->impl_state = this;

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
  // ImFontAtlas_AddFontFromFileTTF(
  //     this->io->Fonts, "../res/fonts/UbuntuMono-Regular.ttf", 16.0f, 0, 0);

  // ImFontAtlas_AddFontFromFileTTF(
  //     this->io->Fonts, "../res/fonts/UbuntuMono-Regular.ttf", 14.0f, 0, 0);

  // ImFontAtlas_AddFontFromFileTTF(
  //     this->io->Fonts, "../res/fonts/UbuntuMono-Regular.ttf", 12.0f, 0, 0);

  ImFontAtlas_AddFontFromFileTTF(this->io->Fonts, "../res/fonts/SegoeUI-Regular.ttf", 18.0f, 0, 0);

  this->ui_api->begin = &r_ui_imgui_begin;
  this->ui_api->render = &r_ui_imgui_render;
  this->ui_api->end = &r_ui_imgui_end;
}

void //
imgui_destroy(imgui_t* this) {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  igDestroyContext(this->context);
}