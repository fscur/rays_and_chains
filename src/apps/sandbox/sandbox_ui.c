#pragma once
#include "engine/core/r_core_types.h"
#include "engine/window/r_window_i.h"
#include "engine/window/r_window.h"
#include "engine/ui/r_ui_i.h"
#include "engine/ui/r_ui.h"
#include "engine/string/r_string_i.h"
#include "engine/memory/r_memory_arena.c"
#include "engine/memory/r_memory_arena.h"
#include "sandbox.h"

size_t //
sandbox_get_sizeof_ui() {
  return sizeof(r_ui_theme_t) +      //
         sizeof(r_ui_frame_t) * 2 +  //
         sizeof(r_ui_button_t) * 4 + //
         sizeof(r_ui_menu_t) * 5 +   //
         sizeof(r_ui_menu_item_t) * 9;
}

internal void //
open_imgui_demo(r_ui_t* ui) {
  ui->show_demo = !ui->show_demo;
}

internal void
close(r_window_t* window) {
  window->should_close = true;
}

R_UI_MENU_ITEM_CLICK_CALLBACK test2 = (R_UI_MENU_ITEM_CLICK_CALLBACK)open_imgui_demo;
R_UI_MENU_ITEM_CLICK_CALLBACK test1 = (R_UI_MENU_ITEM_CLICK_CALLBACK)close;

r_memory_arena_t
sandbox_ui_get_ui_memory_arena(r_memory_arena_t* memory_arena) {
  r_memory_arena_t ui_memory_arena = {0};
  ui_memory_arena.base_addr = (u8*)memory_arena->base_addr + sizeof(r_memory_arena_t) + sizeof(sandbox_t);
  ui_memory_arena.current_addr = ui_memory_arena.base_addr;
  ui_memory_arena.size = 0;
  ui_memory_arena.max_size = memory_arena->size - (sizeof(r_memory_arena_t) + sizeof(sandbox_t));
  return ui_memory_arena;
}

void //
sandbox_ui_init(sandbox_t* this, r_ui_i* ui_api) {
  r_memory_arena_t* memory_arena = this->memory_arena;
  r_memory_arena_t ui_memory_arena = sandbox_ui_get_ui_memory_arena(memory_arena);
  r_ui_t* ui = this->ui;
  ui->memory_arena = &ui_memory_arena;
  
  ui->active_theme = r_memory_arena_push_struct(ui->memory_arena, r_ui_theme_t);
  ui->active_theme->border_color = (r_color_t){0.04f, 0.04f, 0.04f, 0.80f};
  ui->active_theme->menu_background_color = (r_color_t){0.101f, 0.113f, 0.149f, 1.00f};
  ui->active_theme->menu_item_background_color = (r_color_t){0.12f, 0.14f, 0.18f, 1.00f};
  ui->active_theme->border_size = 0.0f;
  ui->active_theme->frame_rounding = 0.0;

  ui->root = &ui->widgets[ui->widget_count++];

  r_ui_frame_t* side_menu = ui_api->create_frame(ui, ui->root, L"SideBar");
  side_menu->is_open = false;
  side_menu->position = (r_v2_t){0.0, 29.0};
  side_menu->size = (r_v2_t){50, 700.0};
  side_menu->frame_style = R_UI_FRAME_STYLE_NO_BORDER;
  side_menu->is_open = true;

  r_ui_frame_t* side_bar = ui_api->create_frame(ui, ui->root, L"ExtensionBar");
  side_bar->is_open = false;
  side_bar->position = (r_v2_t){51.0, 29.0};
  side_bar->size = (r_v2_t){250, 700.0};
  side_bar->frame_style = R_UI_FRAME_STYLE_NO_BORDER;
  side_bar->is_open = true;

  r_ui_button_t* button1 =   //
      ui_api->create_button( //
          ui,
          side_menu->widget,
          L"F",
          true,
          test2,
          ui);

  button1->position = (r_v2_t){5, 5};
  button1->size = (r_v2_t){40, 40};

  r_ui_button_t* button2 =   //
      ui_api->create_button( //
          ui,
          side_menu->widget,
          L"I",
          true,
          test2,
          ui);

  button2->position = (r_v2_t){5, 50};
  button2->size = (r_v2_t){40, 40};

  r_ui_button_t* button3 = ui_api->create_button(ui, side_menu->widget, L"L", true, test2, ui);
  button3->position = (r_v2_t){5, 95};
  button3->size = (r_v2_t){40, 40};

  r_ui_button_t* button4 = ui_api->create_button(ui, side_menu->widget, L"I", true, test2, ui);
  button4->position = (r_v2_t){5, 140};
  button4->size = (r_v2_t){40, 40};

  r_ui_menu_t* main_menu = ui_api->create_main_menu(ui, ui->root);

  r_ui_menu_t* file_menu = ui_api->create_menu(ui, main_menu->widget, L"File");
  ui_api->create_menu_item(ui, file_menu->widget, L"New", L"CTRL+N", true, NULL, NULL);
  ui_api->create_menu_item(ui, file_menu->widget, L"Open", L"CTRL+O", true, NULL, NULL);
  ui_api->create_menu_item(ui, file_menu->widget, L"Save", L"CTRL+S", true, NULL, NULL);
  ui_api->create_menu_item(ui, file_menu->widget, L"Close", L"", true, test1, this->main_window);

  r_ui_menu_t* edit_menu = ui_api->create_menu(ui, main_menu->widget, L"Edit");
  ui_api->create_menu_item(ui, edit_menu->widget, L"Copy", L"CTRL+C", true, NULL, NULL);
  ui_api->create_menu_item(ui, edit_menu->widget, L"Paste", L"CTRL+V", true, NULL, NULL);

  r_ui_menu_t* tools_menu = ui_api->create_menu(ui, main_menu->widget, L"Tools");
  ui_api->create_menu_item(ui, tools_menu->widget, L"Plugin creator", L"", true, NULL, NULL);
  ui_api->create_menu_item(ui, tools_menu->widget, L"ImGui Demo", L"", true, test2, ui);

  r_ui_menu_t* help_menu = ui_api->create_menu(ui, main_menu->widget, L"Help");
  ui_api->create_menu_item(ui, help_menu->widget, L"About", L"", true, NULL, NULL);
}