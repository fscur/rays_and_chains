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

#define MAIN_BG_COLOR                                                                              \
  (ImVec4) { 0.12f, 0.14f, 0.18f, 1.00f }

#define MAIN_MENU_BG_COLOR                                                                         \
  (ImVec4) { 0.101f, 0.113f, 0.149f, 1.00f }

#define BORDER_COLOR                                                                               \
  (ImVec4) { 0.04f, 0.04f, 0.04f, 0.80f }

internal void //
r_ui_imgui_init_theme(r_ui_t* ui) {
  r_ui_theme_t* theme = ui->active_theme;

  struct ImGuiStyle* style = igGetStyle();

  // style->WindowPadding = (ImVec2){7, 7};
  // style->FramePadding = (ImVec2){5, 5};
  // style->ItemSpacing = (ImVec2){7, 7};
  // style->ItemInnerSpacing = (ImVec2){7, 6};

  style->WindowPadding = (ImVec2){5, 5};
  style->FramePadding = (ImVec2){5, 5};
  style->ItemSpacing = (ImVec2){7, 7};
  style->ItemInnerSpacing = (ImVec2){7, 6};
  style->IndentSpacing = 25.0f;
  style->GrabMinSize = 7.0f;
  style->ScrollbarSize = 14.0f;
  style->TabRounding = theme->frame_rounding;
  style->ScrollbarRounding = theme->frame_rounding;
  style->WindowRounding = theme->frame_rounding;
  style->FrameRounding = theme->frame_rounding;
  style->GrabRounding = theme->frame_rounding;
  style->FrameBorderSize = theme->border_size;
  style->ChildBorderSize = theme->border_size;
  style->PopupBorderSize = theme->border_size;
  style->TabBorderSize = theme->border_size;
  style->WindowBorderSize = theme->border_size;

  ImVec4 color01 = (ImVec4){0.04f, 0.04f, 0.057f, 1.00f};
  // ImVec4 color02 = (ImVec4){0.05f, 0.05f, 0.062f, 1.00f};
  ImVec4 color04 = (ImVec4){0.56f, 0.56f, 0.58f, 1.00f};
  ImVec4 color05 = (ImVec4){0.56f, 0.56f, 0.58f, 0.80f};
  ImVec4 color06 = (ImVec4){1.00f, 0.71f, 0.00f, 1.00f};
  ImVec4 color07 = (ImVec4){1.00f, 0.71f, 0.00f, 0.60f};
  ImVec4 color08 = (ImVec4){0.10f, 0.09f, 0.12f, 1.00f};
  ImVec4 color09 = (ImVec4){0.56f, 0.56f, 0.58f, 0.60f};
  ImVec4 color10 = (ImVec4){0.50f, 0.50f, 0.50f, 0.90f};
  // ImVec4 color11 = (ImVec4){0.062f, 0.062f, 0.082f, 1.0f};
  // ImVec4 color12 = (ImVec4){0.106f, 0.106f, 0.141f, 1.0f};

  style->Colors[ImGuiCol_Text] = (ImVec4){0.90f, 0.90f, 0.9f, 1.00f};
  style->Colors[ImGuiCol_TextDisabled] = (ImVec4){0.24f, 0.23f, 0.29f, 1.00f};
  style->Colors[ImGuiCol_WindowBg] = MAIN_BG_COLOR;
  style->Colors[ImGuiCol_ChildBg] = MAIN_BG_COLOR;
  style->Colors[ImGuiCol_PopupBg] = MAIN_BG_COLOR;
  style->Colors[ImGuiCol_Border] = BORDER_COLOR;
  style->Colors[ImGuiCol_BorderShadow] = (ImVec4){0.92f, 0.91f, 0.88f, 0.30f};
  style->Colors[ImGuiCol_FrameBg] = color08;
  style->Colors[ImGuiCol_FrameBgHovered] = color08;
  style->Colors[ImGuiCol_FrameBgActive] = color08;
  style->Colors[ImGuiCol_TitleBg] = MAIN_BG_COLOR;
  style->Colors[ImGuiCol_TitleBgCollapsed] = MAIN_MENU_BG_COLOR;
  style->Colors[ImGuiCol_TitleBgActive] = MAIN_MENU_BG_COLOR;
  style->Colors[ImGuiCol_MenuBarBg] = MAIN_MENU_BG_COLOR;
  style->Colors[ImGuiCol_ScrollbarBg] = MAIN_BG_COLOR;
  style->Colors[ImGuiCol_ScrollbarGrab] = color09;
  style->Colors[ImGuiCol_ScrollbarGrabHovered] = color05;
  style->Colors[ImGuiCol_ScrollbarGrabActive] = color04;
  style->Colors[ImGuiCol_CheckMark] = color04;
  style->Colors[ImGuiCol_SliderGrab] = color04;
  style->Colors[ImGuiCol_SliderGrabActive] = color05;
  style->Colors[ImGuiCol_Button] = MAIN_MENU_BG_COLOR;
  style->Colors[ImGuiCol_ButtonHovered] = color01;
  style->Colors[ImGuiCol_ButtonActive] = MAIN_MENU_BG_COLOR;
  style->Colors[ImGuiCol_Header] = MAIN_MENU_BG_COLOR;
  style->Colors[ImGuiCol_HeaderHovered] = MAIN_MENU_BG_COLOR;
  style->Colors[ImGuiCol_HeaderActive] = MAIN_MENU_BG_COLOR;
  style->Colors[ImGuiCol_ResizeGrip] = (ImVec4){0.00f, 0.00f, 0.00f, 0.00f};
  style->Colors[ImGuiCol_ResizeGripHovered] = color04;
  style->Colors[ImGuiCol_ResizeGripActive] = color01;
  style->Colors[ImGuiCol_PlotLines] = (ImVec4){0.40f, 0.39f, 0.38f, 0.63f};
  style->Colors[ImGuiCol_PlotLinesHovered] = (ImVec4){0.25f, 1.00f, 0.00f, 1.00f};
  style->Colors[ImGuiCol_PlotHistogram] = (ImVec4){0.40f, 0.39f, 0.38f, 0.63f};
  style->Colors[ImGuiCol_PlotHistogramHovered] = (ImVec4){0.25f, 1.00f, 0.00f, 1.00f};
  style->Colors[ImGuiCol_TextSelectedBg] = (ImVec4){0.25f, 1.00f, 0.00f, 0.43f};
  style->Colors[ImGuiCol_ModalWindowDimBg] = color10;
  style->Colors[ImGuiCol_Separator] = BORDER_COLOR;
  style->Colors[ImGuiCol_SeparatorActive] = color06;
  style->Colors[ImGuiCol_SeparatorHovered] = color06;
  style->Colors[ImGuiCol_Tab] = color07;
  style->Colors[ImGuiCol_TabActive] = color06;
  style->Colors[ImGuiCol_TabHovered] = color06;
}

internal void //
r_ui_imgui_begin(r_ui_api_t* this) {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  igNewFrame();
}

internal ImVec4
from_color(r_color_t color) {
  return (ImVec4){color.r, color.g, color.b, color.a};
}

internal ImVec2
from_v2(r_v2_t v2) {
  return (ImVec2){v2.x, v2.y};
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
render_button(imgui_t* this, r_ui_t* ui, r_ui_button_t* button) {
  igSetCursorPos(from_v2(button->position));
  if (igButton(button->label_ansi, from_v2(button->size))) {
    if (button->callback)
      button->callback(button->context);
  }
}

internal void //
render_menu(imgui_t* this, r_ui_t* ui, r_ui_menu_t* menu) {

  r_ui_theme_t* theme = ui->active_theme;

  igPushStyleVarFloat(ImGuiStyleVar_PopupBorderSize, theme->border_size);
  igPushStyleVarFloat(ImGuiStyleVar_WindowRounding, 0.0f);
  igPushStyleColor(ImGuiCol_Border, from_color(theme->border_color));
  igPushStyleColor(ImGuiCol_WindowBg, from_color(theme->menu_background_color));
  igPushStyleColor(ImGuiCol_PopupBg, from_color(theme->menu_background_color));

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
  igPushStyleColor(ImGuiCol_Border, from_color(theme->border_color));
  igPushStyleColor(ImGuiCol_WindowBg, from_color(theme->menu_background_color));
  igPushStyleColor(ImGuiCol_PopupBg, from_color(theme->menu_background_color));

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

  ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize;
  if (frame->frame_style == R_UI_FRAME_STYLE_NO_BORDER)
    flags |= ImGuiWindowFlags_NoTitleBar;

  igSetNextWindowSize(from_v2(frame->size), ImGuiCond_Always);
  igSetNextWindowPos(from_v2(frame->position), ImGuiCond_Always, (ImVec2){0.0, 0.0});
  igBegin(frame->title_ansi, &frame->is_open, flags);
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
  case R_UI_WIDGET_TYPE_BUTTON:
    render_button(this, ui, (r_ui_button_t*)widget->data);
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

  if (ui_api->ui->show_demo) {
    bool open = true;
    igShowDemoWindow(&open);
  }
}

internal void //
r_ui_imgui_end(r_ui_api_t* ui_api) {
  igRender();
  ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
}

void //
r_ui_imgui_init(imgui_t* this, r_api_db_t* api_db) {
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
  this->ui_api->init_theme = &r_ui_imgui_init_theme;
}

void //
r_ui_imgui_destroy(imgui_t* this) {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  igDestroyContext(this->context);
}