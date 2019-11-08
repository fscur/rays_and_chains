#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_UI_MAX_WIDGET_COUNT 1024
#define R_UI_MAX_CHILD_ITEMS 256
#define R_UI_MAX_BUTTON_TEXT_LENGTH 32
#define R_UI_MAX_MENU_TEXT_LENGTH 32
#define R_UI_MAX_FRAME_TEXT_LENGTH 32
#define R_UI_MAX_THEME_COUNT 1

typedef struct r_ui_theme_t {
  u32 id;
  wchar_t* name;
  f32 border_size;
  r_color_t border_color;
  r_color_t menu_background_color;
  r_color_t menu_item_background_color;
  f32 frame_rounding;
} r_ui_theme_t;

typedef enum r_ui_widget_type_t {
  R_UI_WIDGET_TYPE_ROOT,
  R_UI_WIDGET_TYPE_FRAME,
  R_UI_WIDGET_TYPE_MAIN_MENU,
  R_UI_WIDGET_TYPE_MENU,
  R_UI_WIDGET_TYPE_MENU_ITEM,
  R_UI_WIDGET_TYPE_BUTTON
} r_ui_widget_type_t;

typedef struct r_ui_widget_t {
  r_ui_widget_type_t type;
  struct r_ui_widget_t* parent;
  struct r_ui_widget_t* items[R_UI_MAX_CHILD_ITEMS];
  u32 item_count;
  void* data;
} r_ui_widget_t;

typedef void (*R_UI_BUTTON_CLICK_CALLBACK)(void* context);

typedef struct r_ui_button_t {
  r_ui_widget_t* widget;
  wchar_t label_wide[R_UI_MAX_BUTTON_TEXT_LENGTH];
  char label_ansi[R_UI_MAX_BUTTON_TEXT_LENGTH];
  r_v2_t position;
  r_v2_t size;
  bool enabled;
  R_UI_BUTTON_CLICK_CALLBACK callback;
  void* context;
} r_ui_button_t;

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

typedef enum r_ui_frame_style_e { R_UI_FRAME_STYLE_NO_BORDER } r_ui_frame_style_t;

typedef struct r_ui_frame_t {
  r_ui_widget_t* widget;
  wchar_t title_wide[R_UI_MAX_FRAME_TEXT_LENGTH];
  char title_ansi[R_UI_MAX_FRAME_TEXT_LENGTH];
  bool is_open;
  r_v2_t position;
  r_v2_t size;
  r_ui_frame_style_t frame_style;
} r_ui_frame_t;

typedef struct r_ui_t {
  r_memory_block_t* memory_block;
  u32 widget_count;
  r_ui_widget_t widgets[R_UI_MAX_WIDGET_COUNT];
  r_ui_widget_t* root;
  r_ui_theme_t themes[R_UI_MAX_THEME_COUNT];
  r_ui_theme_t* active_theme;
  bool show_demo;
} r_ui_t;

#ifdef __cplusplus
}
#endif