#pragma once
#include "engine/core/r_core_types.h"
#include "engine/window/r_window_i.h"
#include "engine/window/r_window.h"
#include "engine/ui/r_ui_i.h"
#include "engine/ui/r_ui.h"
#include "engine/string/r_string_i.h"
#include "engine/memory/r_memory_block.h"
#include "sandbox.h"

size_t //
sandbox_get_sizeof_ui() {
  return sizeof(r_ui_frame_t) * 2 +  //
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

r_memory_block_t
sandbox_ui_get_ui_memory_block(r_memory_block_t* memory_block) {
  r_memory_block_t ui_memory_block = {0};
  ui_memory_block.base_addr =
      (u8*)memory_block->base_addr + sizeof(r_memory_block_t) + sizeof(sandbox_t);
  ui_memory_block.current_addr = ui_memory_block.base_addr;
  ui_memory_block.size = 0;
  ui_memory_block.max_size = memory_block->size - (sizeof(r_memory_block_t) + sizeof(sandbox_t));
  return ui_memory_block;
}

void //
sandbox_ui_init(sandbox_t* this, r_memory_block_t* memory_block) {

  r_memory_block_t ui_memory_block = sandbox_ui_get_ui_memory_block(memory_block);

  r_ui_t* ui = this->ui_api->instance;
  ui->memory_block = &ui_memory_block;
  r_ui_theme_t* theme = ui->active_theme;

  theme->border_color = (r_color_t){0.04f, 0.04f, 0.04f, 0.80f};
  theme->menu_background_color = (r_color_t){0.101f, 0.113f, 0.149f, 1.00f};
  theme->menu_item_background_color = (r_color_t){0.12f, 0.14f, 0.18f, 1.00f};
  theme->border_size = 0.0f;
  theme->frame_rounding = 0.0;

  r_ui_i* ui_api = this->ui_api;
  ui_api->init_theme(ui);

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
          &open_imgui_demo,
          ui);

  button1->position = (r_v2_t){5, 5};
  button1->size = (r_v2_t){40, 40};

  r_ui_button_t* button2 =   //
      ui_api->create_button( //
          ui,
          side_menu->widget,
          L"I",
          true,
          &open_imgui_demo,
          ui);
          
  button2->position = (r_v2_t){5, 50};
  button2->size = (r_v2_t){40, 40};

  r_ui_button_t* button3 =
      ui_api->create_button(ui, side_menu->widget, L"L", true, &open_imgui_demo, ui);
  button3->position = (r_v2_t){5, 95};
  button3->size = (r_v2_t){40, 40};

  r_ui_button_t* button4 =
      ui_api->create_button(ui, side_menu->widget, L"I", true, &open_imgui_demo, ui);
  button4->position = (r_v2_t){5, 140};
  button4->size = (r_v2_t){40, 40};

  r_ui_menu_t* main_menu = ui_api->create_main_menu(ui, ui->root);

  r_ui_menu_t* file_menu = ui_api->create_menu(ui, main_menu->widget, L"File");
  ui_api->create_menu_item(ui, file_menu->widget, L"New", L"CTRL+N", true, NULL, NULL);
  ui_api->create_menu_item(ui, file_menu->widget, L"Open", L"CTRL+O", true, NULL, NULL);
  ui_api->create_menu_item(ui, file_menu->widget, L"Save", L"CTRL+S", true, NULL, NULL);
  ui_api->create_menu_item(
      ui, file_menu->widget, L"Close", L"", true, &close, this->window_api->instance);

  r_ui_menu_t* edit_menu = ui_api->create_menu(ui, main_menu->widget, L"Edit");
  ui_api->create_menu_item(ui, edit_menu->widget, L"Copy", L"CTRL+C", true, NULL, NULL);
  ui_api->create_menu_item(ui, edit_menu->widget, L"Paste", L"CTRL+V", true, NULL, NULL);

  r_ui_menu_t* tools_menu = ui_api->create_menu(ui, main_menu->widget, L"Tools");
  ui_api->create_menu_item(ui, tools_menu->widget, L"Plugin creator", L"", true, NULL, NULL);
  ui_api->create_menu_item(ui, tools_menu->widget, L"ImGui Demo", L"", true, &open_imgui_demo, ui);

  r_ui_menu_t* help_menu = ui_api->create_menu(ui, main_menu->widget, L"Help");
  ui_api->create_menu_item(ui, help_menu->widget, L"About", L"", true, NULL, NULL);
}