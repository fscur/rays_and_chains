#include "engine/ui/r_ui.h"
#include "engine/string/r_string_api.h"

r_ui_menu_t* //
r_ui_create_menu(r_ui_t* this, r_ui_control_t* parent) {
  if (this->control_count == R_UI_MAX_CONTROL_COUNT)
    return NULL;

  r_ui_control_t* control = &this->controls[this->control_count++];
  control->type = R_UI_CONTROL_TYPE_MENU;

  r_ui_menu_t* menu = (r_ui_menu_t*)malloc(sizeof(r_ui_menu_t));
  memset(menu, 0, sizeof(r_ui_menu_t));
  menu->item_count = 0;
  menu->control = control;
  menu->parent = parent;

  control->data = menu;
  return menu;
}

r_ui_menu_item_t* //
r_ui_create_menu_item(r_ui_t* this, r_ui_menu_t* menu, const wchar_t* text) {
  if (menu->item_count == R_UI_MAX_MENU_ITEMS)
    return NULL;

  // r_ui_control_t* control = &this->controls[this->control_count++];
  // control->type = R_UI_CONTROL_TYPE_MENU_ITEM;

  r_ui_menu_item_t* menu_item = &menu->items[menu->item_count++];
  r_string_w_copy(text, menu_item->text_wide);

  r_string_to_ansi(menu_item->text_wide, menu_item->text_ansi, SHORT_STRING_LENGTH);

  // control->data = menu_item;
  return menu_item;
}

dll_export void //
r_ui_set_theme(r_ui_t* this, u32 theme_id) {
  assert(theme_id < R_UI_MAX_THEME_COUNT);
  this->active_theme = &this->themes[theme_id];
}
