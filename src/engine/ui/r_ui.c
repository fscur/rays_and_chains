#include "engine/ui/r_ui.h"
#include "engine/string/r_string_api.h"

r_ui_menu_t* //
r_ui_create_main_menu(r_ui_t* this, r_ui_widget_t* parent) {
  if (this->widget_count == R_UI_MAX_WIDGET_COUNT)
    return NULL;

  r_ui_widget_t* widget = &this->widgets[this->widget_count++];
  widget->type = R_UI_WIDGET_TYPE_MAIN_MENU;
  widget->item_count = 0;
  widget->parent = parent;

  r_ui_menu_t* menu = (r_ui_menu_t*)malloc(sizeof(r_ui_menu_t));
  memset(menu, 0, sizeof(r_ui_menu_t));
  menu->widget = widget;
  widget->data = menu;

  if (parent != NULL) {
    parent->items[parent->item_count++] = widget;
  }

  return menu;
}

r_ui_menu_t* //
r_ui_create_menu(r_ui_t* this, r_ui_widget_t* parent, const wchar_t* label) {
  if (this->widget_count == R_UI_MAX_WIDGET_COUNT)
    return NULL;

  r_ui_widget_t* widget = &this->widgets[this->widget_count++];
  widget->type = R_UI_WIDGET_TYPE_MENU;
  widget->item_count = 0;
  widget->parent = parent;

  r_ui_menu_t* menu = (r_ui_menu_t*)malloc(sizeof(r_ui_menu_t));
  memset(menu, 0, sizeof(r_ui_menu_t));
  r_string_w_copy(label, menu->label_wide);
  r_string_to_ansi(menu->label_wide, menu->label_ansi, SHORT_STRING_LENGTH);
  menu->widget = widget;
  widget->data = menu;

  if (parent != NULL) {
    parent->items[parent->item_count++] = widget;
  }

  return menu;
}

r_ui_menu_item_t* //
r_ui_create_menu_item(r_ui_t* this,
                      r_ui_widget_t* parent,
                      const wchar_t* label,
                      const wchar_t* shortcut,
                      bool enabled,
                      R_UI_MENU_ITEM_CLICK_CALLBACK callback,
                      void* context) {
  if (this->widget_count == R_UI_MAX_WIDGET_COUNT)
    return NULL;

  r_ui_widget_t* widget = &this->widgets[this->widget_count++];
  widget->type = R_UI_WIDGET_TYPE_MENU_ITEM;
  widget->item_count = 0;
  widget->parent = parent;

  r_ui_menu_item_t* menu_item = (r_ui_menu_item_t*)malloc(sizeof(r_ui_menu_item_t));
  memset(menu_item, 0, sizeof(r_ui_menu_item_t));
  r_string_w_copy(label, menu_item->label_wide);
  r_string_to_ansi(menu_item->label_wide, menu_item->label_ansi, SHORT_STRING_LENGTH);
  r_string_w_copy(shortcut, menu_item->shortcut_wide);
  r_string_to_ansi(menu_item->shortcut_wide, menu_item->shortcut_ansi, SHORT_STRING_LENGTH);
  menu_item->enabled = enabled;
  menu_item->callback = callback;
  menu_item->context = context;
  menu_item->widget = widget;
  widget->data = menu_item;

  if (parent != NULL) {
    parent->items[parent->item_count++] = widget;
  }

  return menu_item;
}

r_ui_frame_t* //
r_ui_create_frame(r_ui_t* this, r_ui_widget_t* parent, const wchar_t* title) {
  if (this->widget_count == R_UI_MAX_WIDGET_COUNT)
    return NULL;

  r_ui_widget_t* widget = &this->widgets[this->widget_count++];
  widget->type = R_UI_WIDGET_TYPE_FRAME;
  widget->item_count = 0;
  widget->parent = parent;

  r_ui_frame_t* frame = (r_ui_frame_t*)malloc(sizeof(r_ui_frame_t));
  memset(frame, 0, sizeof(r_ui_frame_t));
  r_string_w_copy(title, frame->title_wide);
  r_string_to_ansi(frame->title_wide, frame->title_ansi, SHORT_STRING_LENGTH);
  frame->is_open = false;
  frame->widget = widget;
  widget->data = frame;

  if (parent != NULL) {
    parent->items[parent->item_count++] = widget;
  }

  return frame;
}

dll_export void //
r_ui_set_theme(r_ui_t* this, u32 theme_id) {
  assert(theme_id < R_UI_MAX_THEME_COUNT);
  this->active_theme = &this->themes[theme_id];
}
