#pragma once
#include "cimgui/cimgui.h"
#include "engine/core/r_core_types.h"

static bool show_demo_window = false;

void //
init_imgui_style() {
  struct ImGuiStyle* style = igGetStyle();

  style->WindowPadding = (ImVec2){7, 7};
  style->FramePadding = (ImVec2){5, 5};
  style->ItemSpacing = (ImVec2){7, 7};
  style->ItemInnerSpacing = (ImVec2){7, 6};
  style->IndentSpacing = 25.0f;
  style->GrabMinSize = 7.0f;
  style->ScrollbarSize = 12.0f;
  style->TabRounding = 2.0f;
  style->ScrollbarRounding = 2.0f;
  style->WindowRounding = 2.0f;
  style->FrameRounding = 2.0f;
  style->GrabRounding = 2.0f;
  style->FrameBorderSize = 0.0f;
  style->ChildBorderSize = 0.0f;
  style->PopupBorderSize = 0.0f;
  style->TabBorderSize = 0.0f;
  style->WindowBorderSize = 0.0f;

  ImVec4 color01 = (ImVec4){0.04f, 0.04f, 0.057f, 1.00f};
  ImVec4 color02 = (ImVec4){0.05f, 0.05f, 0.062f, 1.00f};
  ImVec4 color04 = (ImVec4){0.56f, 0.56f, 0.58f, 1.00f};
  ImVec4 color05 = (ImVec4){0.56f, 0.56f, 0.58f, 0.80f};
  ImVec4 color06 = (ImVec4){1.00f, 0.71f, 0.00f, 1.00f};
  ImVec4 color07 = (ImVec4){1.00f, 0.71f, 0.00f, 0.60f};
  ImVec4 color08 = (ImVec4){0.10f, 0.09f, 0.12f, 1.00f};
  ImVec4 color09 = (ImVec4){0.56f, 0.56f, 0.58f, 0.60f};
  ImVec4 color10 = (ImVec4){0.50f, 0.50f, 0.50f, 0.90f};
  ImVec4 color11 = (ImVec4){0.062f, 0.062f, 0.082f, 1.0f};
  ImVec4 color12 = (ImVec4){0.106f, 0.106f, 0.141f, 1.0f};

  style->Colors[ImGuiCol_Text] = (ImVec4){0.90f, 0.90f, 0.9f, 1.00f};
  style->Colors[ImGuiCol_TextDisabled] = (ImVec4){0.24f, 0.23f, 0.29f, 1.00f};
  //style->Colors[ImGuiCol_WindowBg] = (ImVec4){0.0f, 0.188f, 1.0f, 1.0f};
  style->Colors[ImGuiCol_WindowBg] = (ImVec4){0.197f, 0.188f, 0.224f, 1.0f};
  style->Colors[ImGuiCol_ChildBg] = color11;
  style->Colors[ImGuiCol_PopupBg] = color11;
  style->Colors[ImGuiCol_Border] = (ImVec4){0.80f, 0.80f, 0.83f, 0.88f};
  style->Colors[ImGuiCol_BorderShadow] = (ImVec4){0.92f, 0.91f, 0.88f, 0.30f};
  style->Colors[ImGuiCol_FrameBg] = color08;
  style->Colors[ImGuiCol_FrameBgHovered] = color08;
  style->Colors[ImGuiCol_FrameBgActive] = color08;
  style->Colors[ImGuiCol_TitleBg] = color11;
  style->Colors[ImGuiCol_TitleBgCollapsed] = color12;
  style->Colors[ImGuiCol_TitleBgActive] = color12;
  style->Colors[ImGuiCol_MenuBarBg] = color12;
  style->Colors[ImGuiCol_ScrollbarBg] = color02;
  style->Colors[ImGuiCol_ScrollbarGrab] = color09;
  style->Colors[ImGuiCol_ScrollbarGrabHovered] = color05;
  style->Colors[ImGuiCol_ScrollbarGrabActive] = color04;
  style->Colors[ImGuiCol_CheckMark] = color04;
  style->Colors[ImGuiCol_SliderGrab] = color04;
  style->Colors[ImGuiCol_SliderGrabActive] = color05;
  style->Colors[ImGuiCol_Button] = color06;
  style->Colors[ImGuiCol_ButtonHovered] = color01;
  style->Colors[ImGuiCol_ButtonActive] = color04;
  style->Colors[ImGuiCol_Header] = color11;
  style->Colors[ImGuiCol_HeaderHovered] = color11;
  style->Colors[ImGuiCol_HeaderActive] = color11;
  style->Colors[ImGuiCol_ResizeGrip] = (ImVec4){0.00f, 0.00f, 0.00f, 0.00f};
  style->Colors[ImGuiCol_ResizeGripHovered] = color04;
  style->Colors[ImGuiCol_ResizeGripActive] = color01;
  style->Colors[ImGuiCol_PlotLines] = (ImVec4){0.40f, 0.39f, 0.38f, 0.63f};
  style->Colors[ImGuiCol_PlotLinesHovered] = (ImVec4){0.25f, 1.00f, 0.00f, 1.00f};
  style->Colors[ImGuiCol_PlotHistogram] = (ImVec4){0.40f, 0.39f, 0.38f, 0.63f};
  style->Colors[ImGuiCol_PlotHistogramHovered] = (ImVec4){0.25f, 1.00f, 0.00f, 1.00f};
  style->Colors[ImGuiCol_TextSelectedBg] = (ImVec4){0.25f, 1.00f, 0.00f, 0.43f};
  style->Colors[ImGuiCol_ModalWindowDimBg] = color10;
  style->Colors[ImGuiCol_Separator] = color06;
  style->Colors[ImGuiCol_SeparatorActive] = color06;
  style->Colors[ImGuiCol_SeparatorHovered] = color06;
  style->Colors[ImGuiCol_Tab] = color07;
  style->Colors[ImGuiCol_TabActive] = color06;
  style->Colors[ImGuiCol_TabHovered] = color06;
}

void //
init_ui() {
  init_imgui_style();
}

void //
render_menu_help() {
  local bool editMenuEnabled = true;
  if (igBeginMenu("Edit", &editMenuEnabled)) {
    if (igMenuItemBool("About", "", false, true)) {
    }
    igEndMenu();
  }
}

void //
render_menu_edit_items() {
  if (igMenuItemBool("Undo", "CTRL+Z", false, true)) {
  }
  if (igMenuItemBool("Redo", "CTRL+Y", false, false)) {
  } // Disabled item

  igSeparator();

  if (igMenuItemBool("Cut", "CTRL+X", false, true)) {
  }
  if (igMenuItemBool("Copy", "CTRL+C", false, true)) {
  }
  if (igMenuItemBool("Paste", "CTRL+V", false, true)) {
  }
}

void //
render_menu_edit() {
  local bool editMenuEnabled = true;
  if (igBeginMenu("Edit", &editMenuEnabled)) {
    render_menu_edit_items();
    igEndMenu();
  }
}

void //
render_menu_file_items() {
  if (igMenuItemBool("New", "CTRL+N", false, true)) {
    show_demo_window = true;
  }
  if (igMenuItemBool("Open...", "CTRL+O", false, false)) {
    show_demo_window = false;
  } // Disabled item

  if (igMenuItemBool("Save", "CTRL+S", false, true)) {
  }
  if (igMenuItemBool("Save as...", "", false, true)) {
  }

  igSeparator();

  if (igMenuItemBool("Quit", "", false, true)) {
  }
}

void //
render_menu_file() {
  local bool isFileMenuEnabled = true;
  if (igBeginMenu("File", &isFileMenuEnabled)) {
    render_menu_file_items();
    igEndMenu();
  }
}

void //
render_main_menu() {
  if (igBeginMainMenuBar()) {
    render_menu_file();
    render_menu_edit();
    igEndMainMenuBar();
  }
}

void //
render_side_menu() {
  ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
                           ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar |
                           ImGuiWindowFlags_NoBringToFrontOnFocus;

  bool open = true;
  igPushStyleVarFloat(ImGuiStyleVar_WindowBorderSize, 1.0f);
  igPushStyleVarFloat(ImGuiStyleVar_WindowRounding, 0.0f);
  igPushStyleColor(ImGuiCol_Border, (ImVec4){0.04f, 0.04f, 0.04f, 0.80f});
  igPushStyleColor(ImGuiCol_WindowBg, (ImVec4){0.045f, 0.045f, 0.065f, 1.00f});

  igBegin("side_menu", &open, flags);
  igSetWindowPosVec2((ImVec2){-1, -1}, ImGuiCond_Always);
  igSetWindowSizeVec2((ImVec2){51, 1081}, ImGuiCond_Always);

  // todo: add extension code

  igEnd();
  igPopStyleColor(2);
  igPopStyleVar(2);
}

void //
render_extension_place_holder() {
  ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
                           ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar |
                           ImGuiWindowFlags_NoBringToFrontOnFocus;

  bool open = true;
  igPushStyleVarFloat(ImGuiStyleVar_WindowBorderSize, 1.0f);
  igPushStyleVarFloat(ImGuiStyleVar_WindowRounding, 0.0f);
  igPushStyleColor(ImGuiCol_Border, (ImVec4){0.04f, 0.04f, 0.04f, 0.80f});
  igPushStyleColor(ImGuiCol_WindowBg, (ImVec4){0.05f, 0.05f, 0.072f, 1.0f});

  igBegin("extension_place_holder", &open, flags);
  igSetWindowPosVec2((ImVec2){49, -1}, ImGuiCond_Always);
  igSetWindowSizeVec2((ImVec2){252, 1081}, ImGuiCond_Always);

  // todo: add extension code

  igEnd();
  igPopStyleColor(2);
  igPopStyleVar(2);
}

void //
render_viewport() {
  ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
                           ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar |
                           ImGuiWindowFlags_NoBringToFrontOnFocus;

  bool open = true;
  igPushStyleVarFloat(ImGuiStyleVar_WindowBorderSize, 1.0f);
  igPushStyleVarFloat(ImGuiStyleVar_WindowRounding, 0.0f);
  igPushStyleColor(ImGuiCol_Border, (ImVec4){0.04f, 0.04f, 0.04f, 0.80f});
  igPushStyleColor(ImGuiCol_WindowBg, (ImVec4){0.05f, 0.05f, 0.072f, 1.0f});

  igBegin("viewport", &open, flags);
  igSetWindowPosVec2((ImVec2){300, 27}, ImGuiCond_Always);
  igSetWindowSizeVec2((ImVec2){2000, 1081}, ImGuiCond_Always);

  // igImage((void*)ui->texture_id,
  //         (ImVec2){(f32)ui->image->width, (f32)ui->image->height},
  //         (ImVec2){uv_start, uv_start},
  //         (ImVec2){uv_end, uv_end},
  //         (ImColor){255, 255, 255, 255},
  //         (ImColor){255, 255, 255, 128});

  // todo: add extension code

  igEnd();
  igPopStyleColor(2);
  igPopStyleVar(2);
}

void //
render_ui() {
  render_main_menu();
  render_side_menu();
  render_extension_place_holder();
  render_viewport();

  if (show_demo_window) {
    bool open = true;
    igShowDemoWindow(&open);
  }
}