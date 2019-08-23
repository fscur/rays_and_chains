#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/ui/r_ui_types.h"

#define R_UI_MAX_CONTROL_COUNT 512
#define R_UI_MAX_MENU_ITEMS 16
#define R_UI_MAX_MENU_ITEM_TEXT_LENGTH 32
#define R_UI_MAX_THEME_COUNT 1

typedef enum r_ui_control_type_t {
  R_UI_CONTROL_TYPE_MENU,
  R_UI_CONTROL_TYPE_MENU_ITEM
} r_ui_control_type_t;

typedef struct r_ui_control_t {
  r_ui_control_type_t type;
  r_v3_t position;
  r_v2_t size;
  void* data;
} r_ui_control_t;

typedef struct r_ui_menu_item_t {
  // r_ui_control_t* control;
  // r_ui_control_t* parent;
  wchar_t text_wide[R_UI_MAX_MENU_ITEM_TEXT_LENGTH];
  char text_ansi[R_UI_MAX_MENU_ITEM_TEXT_LENGTH];
} r_ui_menu_item_t;

typedef struct r_ui_menu_t {
  r_ui_control_t* control;
  r_ui_control_t* parent;
  r_ui_menu_item_t items[R_UI_MAX_MENU_ITEMS];
  u32 item_count; 
} r_ui_menu_t;

typedef struct r_ui_t {
  u32 control_count;
  r_ui_control_t controls[R_UI_MAX_CONTROL_COUNT];
  r_ui_theme_t themes[R_UI_MAX_THEME_COUNT];
  r_ui_theme_t* active_theme;
} r_ui_t;

dll_export r_ui_menu_t* //
r_ui_create_menu(r_ui_t* this, r_ui_control_t* parent);

dll_export r_ui_menu_item_t* //
r_ui_create_menu_item(r_ui_t* this, r_ui_menu_t* menu, const wchar_t* text);

dll_export void //
r_ui_set_theme(r_ui_t* this, u32 theme_id);

#ifdef __cplusplus
}
#endif
