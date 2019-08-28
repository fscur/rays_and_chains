#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/ui/r_ui_types.h"

#define R_UI_MAX_WIDGET_COUNT 1024
#define R_UI_MAX_CHILD_ITEMS 256
#define R_UI_MAX_MENU_TEXT_LENGTH 32
#define R_UI_MAX_FRAME_TEXT_LENGTH 32
#define R_UI_MAX_THEME_COUNT 1

typedef enum r_ui_widget_type_t {
  R_UI_WIDGET_TYPE_ROOT,
  R_UI_WIDGET_TYPE_FRAME,
  R_UI_WIDGET_TYPE_MAIN_MENU,
  R_UI_WIDGET_TYPE_MENU,
  R_UI_WIDGET_TYPE_MENU_ITEM
} r_ui_widget_type_t;

typedef struct r_ui_widget_t {
  r_ui_widget_type_t type;
  struct r_ui_widget_t* parent;
  struct r_ui_widget_t* items[R_UI_MAX_CHILD_ITEMS];
  u32 item_count;
  void* data;
} r_ui_widget_t;

typedef void (*R_UI_MENU_ITEM_CLICK_CALLBACK)(void* context);

typedef struct r_ui_menu_item_t {
  r_ui_widget_t* widget;
  wchar_t label_wide[R_UI_MAX_MENU_TEXT_LENGTH];
  char label_ansi[R_UI_MAX_MENU_TEXT_LENGTH];
  wchar_t shortcut_wide[R_UI_MAX_MENU_TEXT_LENGTH];
  char shortcut_ansi[R_UI_MAX_MENU_TEXT_LENGTH];
  bool enabled;
  R_UI_MENU_ITEM_CLICK_CALLBACK callback;
  void* context;
} r_ui_menu_item_t;

typedef struct r_ui_menu_t {
  r_ui_widget_t* widget;
  wchar_t label_wide[R_UI_MAX_MENU_TEXT_LENGTH];
  char label_ansi[R_UI_MAX_MENU_TEXT_LENGTH];
} r_ui_menu_t;

typedef struct r_ui_frame_t {
  r_ui_widget_t* widget;
  wchar_t title_wide[R_UI_MAX_FRAME_TEXT_LENGTH];
  char title_ansi[R_UI_MAX_FRAME_TEXT_LENGTH];
  bool is_open;
} r_ui_frame_t;

typedef struct r_ui_t {
  u32 widget_count;
  r_ui_widget_t widgets[R_UI_MAX_WIDGET_COUNT];
  r_ui_widget_t* root;
  r_ui_theme_t themes[R_UI_MAX_THEME_COUNT];
  r_ui_theme_t* active_theme;
} r_ui_t;

dll_export r_ui_menu_t* //
r_ui_create_main_menu(r_ui_t* this, r_ui_widget_t* parent);

dll_export r_ui_menu_t* //
r_ui_create_menu(r_ui_t* this, r_ui_widget_t* parent, const wchar_t* label);

r_ui_menu_item_t* //
r_ui_create_menu_item(r_ui_t* this,
                      r_ui_widget_t* parent,
                      const wchar_t* label,
                      const wchar_t* shortcut,
                      bool enabled,
                      R_UI_MENU_ITEM_CLICK_CALLBACK callback,
                      void* context);

dll_export r_ui_frame_t* //
r_ui_create_frame(r_ui_t* this, r_ui_widget_t* parent, const wchar_t* title);

dll_export void //
r_ui_set_theme(r_ui_t* this, u32 theme_id);

#ifdef __cplusplus
}
#endif
