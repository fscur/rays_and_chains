#include "engine/app/r_api_db.h"
#include "engine/memory/r_memory_arena.h"
#include "r_ui_i.h"
#include "r_ui.h"

void //
r_ui_register_api(r_api_db_t* api_db, r_memory_arena_t* apis_arena) {
  r_ui_i* ui_api = r_memory_arena_push_struct(apis_arena, r_ui_i);

  ui_api->create = &r_ui_create;
  ui_api->create_main_menu = &r_ui_create_main_menu;
  ui_api->create_menu = &r_ui_create_menu;
  ui_api->create_menu_item = &r_ui_create_menu_item;
  ui_api->create_button = &r_ui_create_button;
  ui_api->create_frame = &r_ui_create_frame;

  r_api_db_add(api_db, R_UI_API_NAME, ui_api);
}