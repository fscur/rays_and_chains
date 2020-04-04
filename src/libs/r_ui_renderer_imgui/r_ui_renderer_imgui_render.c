#include <cimgui/cimgui.h>

#include "engine/ui/r_ui.h"
#include "engine/ui/r_ui_i.h"
#include "r_ui_renderer_imgui.h"

#define MAIN_BG_COLOR                                                                                                  \
  (ImVec4) { 0.12f, 0.14f, 0.18f, 1.00f }

#define MAIN_MENU_BG_COLOR                                                                                             \
  (ImVec4) { 0.101f, 0.113f, 0.149f, 1.00f }

#define BORDER_COLOR                                                                                                   \
  (ImVec4) { 0.04f, 0.04f, 0.04f, 0.80f }

internal void //
r_ui_renderer_imgui_init_theme(r_ui_t* ui) {
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

internal ImVec4
from_color(r_color_t color) {
  return (ImVec4){color.r, color.g, color.b, color.a};
}

internal ImVec2
from_v2(r_v2_t v2) {
  return (ImVec2){v2.x, v2.y};
}

internal void //
render_widget(r_ui_renderer_t* this, r_ui_t* ui, r_ui_widget_t* widget);

internal void //
render_menu_item(r_ui_renderer_t* this, r_ui_t* ui, r_ui_menu_item_t* menu_item) {
  if (igMenuItemBool(menu_item->label_ansi, menu_item->shortcut_ansi, false, menu_item->enabled)) {
    if (menu_item->callback)
      menu_item->callback(menu_item->context);
  }
}

internal void //
render_button(r_ui_renderer_t* this, r_ui_t* ui, r_ui_button_t* button) {
  igSetCursorPos(from_v2(button->position));
  if (igButton(button->label_ansi, from_v2(button->size))) {
    if (button->callback)
      button->callback(button->context);
  }
}

internal void //
render_menu(r_ui_renderer_t* this, r_ui_t* ui, r_ui_menu_t* menu) {

  r_ui_theme_t* theme = ui->active_theme;

  igPushStyleVarFloat(ImGuiStyleVar_PopupBorderSize, theme->border_size);
  igPushStyleVarFloat(ImGuiStyleVar_WindowRounding, 0.0f);
  igPushStyleColorVec4(ImGuiCol_Border, from_color(theme->border_color));
  igPushStyleColorVec4(ImGuiCol_WindowBg, from_color(theme->menu_background_color));
  igPushStyleColorVec4(ImGuiCol_PopupBg, from_color(theme->menu_background_color));

  local bool is_open = true;
  if (igBeginMenu(menu->label_ansi, is_open)) {
    for (size_t i = 0; i < menu->widget->item_count; i++) {
      render_widget(this, ui, menu->widget->items[i]);
    }
    igEndMenu();
  }

  igPopStyleColor(3);
  igPopStyleVar(2);
}

internal void //
render_main_menu(r_ui_renderer_t* this, r_ui_t* ui, r_ui_menu_t* menu) {

  r_ui_theme_t* theme = ui->active_theme;

  igPushStyleVarFloat(ImGuiStyleVar_PopupBorderSize, theme->border_size);
  igPushStyleVarFloat(ImGuiStyleVar_WindowRounding, 0.0f);
  igPushStyleColorVec4(ImGuiCol_Border, from_color(theme->border_color));
  igPushStyleColorVec4(ImGuiCol_WindowBg, from_color(theme->menu_background_color));
  igPushStyleColorVec4(ImGuiCol_PopupBg, from_color(theme->menu_background_color));

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
render_frame(r_ui_renderer_t* this, r_ui_t* ui, r_ui_frame_t* frame) {
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
render_demo_window(r_ui_renderer_t* this, r_ui_t* ui, r_ui_frame_t* frame) {
  if (!frame->is_open)
    return;

  local bool is_open;
  igShowDemoWindow(&is_open);
}

internal void //
render_widget(r_ui_renderer_t* this, r_ui_t* ui, r_ui_widget_t* widget) {
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
  default:
    break;
  }
}

internal void //
render_widgets(r_ui_renderer_t* this, r_ui_t* ui) {
  r_ui_widget_t* root = ui->root;
  for (size_t i = 0; i < root->item_count; i++) {
    r_ui_widget_t* child = root->items[i];
    render_widget(this, ui, child);
  }
}