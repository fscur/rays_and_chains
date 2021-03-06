#include "engine/ui/r_ui.h"
#include "engine/string/r_string_i.h"
#include "engine/memory/r_memory_block.h"

r_ui_menu_t* //
r_ui_create_main_menu(r_ui_t* this, r_ui_widget_t* parent) {
  if (this->widget_count == R_UI_MAX_WIDGET_COUNT)
    return NULL;

  r_ui_widget_t* widget = &this->widgets[this->widget_count++];
  widget->type = R_UI_WIDGET_TYPE_MAIN_MENU;
  widget->item_count = 0;
  widget->parent = parent;

  r_memory_block_t* memory_block = this->memory_block;
  r_ui_menu_t* menu = r_memory_block_push_struct(memory_block, r_ui_menu_t);
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

  r_memory_block_t* memory_block = this->memory_block;
  r_ui_menu_t* menu = r_memory_block_push_struct(memory_block, r_ui_menu_t);
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

  r_memory_block_t* memory_block = this->memory_block;
  r_ui_menu_item_t* menu_item = r_memory_block_push_struct(memory_block, r_ui_menu_item_t);
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

  r_memory_block_t* memory_block = this->memory_block;
  r_ui_frame_t* frame = r_memory_block_push_struct(memory_block, r_ui_frame_t);

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

r_ui_button_t* //
r_ui_create_button(r_ui_t* this,
                   r_ui_widget_t* parent,
                   const wchar_t* label,
                   bool enabled,
                   R_UI_BUTTON_CLICK_CALLBACK callback,
                   void* context) {
  if (this->widget_count == R_UI_MAX_WIDGET_COUNT)
    return NULL;

  r_ui_widget_t* widget = &this->widgets[this->widget_count++];
  widget->type = R_UI_WIDGET_TYPE_BUTTON;
  widget->item_count = 0;
  widget->parent = parent;

  r_memory_block_t* memory_block = this->memory_block;
  r_ui_button_t* button = r_memory_block_push_struct(memory_block, r_ui_button_t);
  r_string_w_copy(label, button->label_wide);
  r_string_to_ansi(button->label_wide, button->label_ansi, SHORT_STRING_LENGTH);
  button->enabled = enabled;
  button->callback = callback;
  button->context = context;
  button->widget = widget;
  widget->data = button;

  if (parent != NULL) {
    parent->items[parent->item_count++] = widget;
  }

  return button;
}

void //
r_ui_set_theme(r_ui_t* this, u32 theme_id) {
  assert(theme_id < R_UI_MAX_THEME_COUNT);
  this->active_theme = &this->themes[theme_id];
}
