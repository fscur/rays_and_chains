#include "sandbox.h"
#include "engine/app/r_app.h"
#include "engine/app/r_api_db.h"
#include "engine/diagnostics/r_debug_api.h"
#include "engine/window/r_window.h"
#include "engine/window/r_window_api.h"
#include "engine/ui/r_ui.h"
#include "engine/ui/r_ui_api.h"
#include "engine/string/r_string_api.h"
#include "engine/gfx/r_gfx_renderer.h"
#include "engine/gfx/r_gfx_renderer_api.h"
#include "engine/memory/r_memory_block.h"

//#include "ui.c"

// #include "cimgui/cimgui.h"
// #pragma comment(lib, "cimgui.lib")

u32 //
get_id_sandbox(void) {
  return 0;
}

size_t //
get_size_sandbox(void) {
  return sizeof(sandbox_t) +         //
         sizeof(r_ui_frame_t) * 2 +  //
         sizeof(r_ui_button_t) * 4 + //
         sizeof(r_ui_menu_t) * 5 +   //
         sizeof(r_ui_menu_item_t) * 9;
}

void //
load_sandbox(r_lib_load_info_t* load_info) {
  r_lib_t* lib = (r_lib_t*)load_info->lib_memory_addr;
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "sandbox_get_app_info");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "sandbox_init");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "sandbox_run");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "sandbox_destroy");
}

r_app_info_t //
sandbox_get_app_info(void) {

  r_app_info_t app_info = {
      .title = L"sandbox app", .width = 1280, .height = 720, .desired_fps = 30.0};

  return app_info;
}

internal void //
open_imgui_demo(r_ui_t* ui) {
  ui->show_demo = !ui->show_demo;
}

internal void
close(r_window_t* window) {
  window->should_close = true;
}

void //
init_ui(sandbox_t* this, r_memory_block_t* memory_block) {

  r_memory_block_t ui_memory_block = {0};
  ui_memory_block.base_addr =
      (u8*)memory_block->base_addr + sizeof(r_memory_block_t) + sizeof(sandbox_t);
  ui_memory_block.current_addr = ui_memory_block.base_addr;
  ui_memory_block.size = 0;
  ui_memory_block.max_size = memory_block->size - (sizeof(r_memory_block_t) + sizeof(sandbox_t));

  r_ui_t* ui = this->ui_api->ui;
  ui->memory_block = &ui_memory_block;
  r_ui_theme_t* theme = ui->active_theme;

  theme->border_color = (r_color_t){0.04f, 0.04f, 0.04f, 0.80f};
  theme->menu_background_color = (r_color_t){0.101f, 0.113f, 0.149f, 1.00f};
  theme->menu_item_background_color = (r_color_t){0.12f, 0.14f, 0.18f, 1.00f};
  theme->border_size = 0.0f;
  theme->frame_rounding = 0.0;

  r_ui_api_t* ui_api = this->ui_api;
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

  r_ui_button_t* button1 =
      ui_api->create_button(ui, side_menu->widget, L"F", true, &open_imgui_demo, ui);
  button1->position = (r_v2_t){5, 5};
  button1->size = (r_v2_t){40, 40};

  r_ui_button_t* button2 =
      ui_api->create_button(ui, side_menu->widget, L"I", true, &open_imgui_demo, ui);
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
      ui, file_menu->widget, L"Close", L"", true, &close, this->window_api->window);

  r_ui_menu_t* edit_menu = ui_api->create_menu(ui, main_menu->widget, L"Edit");
  ui_api->create_menu_item(ui, edit_menu->widget, L"Copy", L"CTRL+C", true, NULL, NULL);
  ui_api->create_menu_item(ui, edit_menu->widget, L"Paste", L"CTRL+V", true, NULL, NULL);

  r_ui_menu_t* tools_menu = ui_api->create_menu(ui, main_menu->widget, L"Tools");
  ui_api->create_menu_item(ui, tools_menu->widget, L"Plugin creator", L"", true, NULL, NULL);
  ui_api->create_menu_item(ui, tools_menu->widget, L"ImGui Demo", L"", true, &open_imgui_demo, ui);

  r_ui_menu_t* help_menu = ui_api->create_menu(ui, main_menu->widget, L"Help");
  ui_api->create_menu_item(ui, help_menu->widget, L"About", L"", true, NULL, NULL);
}

void //
sandbox_init(r_app_t* app, r_api_db_t* api_db) {

  sandbox_t* this = (sandbox_t*)app->state;

  this->debug_api = api_db->apis[R_DEBUG_API_ID];
  this->window_api = api_db->apis[R_WINDOW_API_ID];
  this->ui_api = api_db->apis[R_UI_API_ID];
  this->string_api = api_db->apis[R_STRING_API_ID];
  this->renderer_api = api_db->apis[R_GFX_RENDERER_API_ID];

  init_ui(this, app->memory_block);
}

void //
sandbox_run(sandbox_t* this, r_frame_info_t* frame_info) {
  r_window_t* window = this->window_api->window;

  this->window_api->input(window);
  this->window_api->update(window);

  r_gfx_renderer_t* renderer = this->renderer_api->renderer;
  r_gfx_cmd_t* cmd = this->renderer_api->create_clear_color_cmd(renderer);

  r_gfx_clear_color_cmd_t* clear_color_cmd = (r_gfx_clear_color_cmd_t*)cmd->data;
  clear_color_cmd->color = (r_color_t){0.04f, 0.04f, 0.054f, 1.00f};

  this->renderer_api->clear(renderer);
  this->renderer_api->add_cmd(renderer, cmd);
  this->renderer_api->sort(renderer);
  this->renderer_api->submit(renderer);

  this->ui_api->begin(this->ui_api);
  this->ui_api->render(this->ui_api);
  this->ui_api->end(this->ui_api);

  this->window_api->swap_buffers(window);
}

void //
sandbox_destroy(sandbox_t* this) {}