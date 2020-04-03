#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"
#include "engine/ui/r_ui_types.h"

#define R_UI_API_NAME "r_ui"

typedef struct r_ui_t r_ui_t;
typedef struct r_ui_widget_t r_ui_widget_t;
typedef struct r_ui_menu_t r_ui_menu_t;
typedef struct r_ui_menu_item_t r_ui_menu_item_t;
typedef struct r_ui_button_t r_ui_button_t;
typedef struct r_ui_i r_ui_i;

typedef struct r_ui_i {
  r_ui_t* (*create)();
  void (*init_theme)(r_ui_t* this);
  r_ui_menu_t* (*create_main_menu)(r_ui_t* this, r_ui_widget_t* parent);
  r_ui_menu_t* (*create_menu)(r_ui_t* this, r_ui_widget_t* parent, const wchar_t* label);

  r_ui_menu_item_t* (*create_menu_item)(r_ui_t* this,
                                        r_ui_widget_t* parent,
                                        const wchar_t* label,
                                        const wchar_t* shortcut,
                                        bool enabled,
                                        R_UI_MENU_ITEM_CLICK_CALLBACK callback,
                                        void* context);

  r_ui_button_t* (*create_button)(r_ui_t* this,
                                  r_ui_widget_t* parent,
                                  const wchar_t* label,
                                  bool enabled,
                                  R_UI_MENU_ITEM_CLICK_CALLBACK callback,
                                  void* context);

  r_ui_frame_t* (*create_frame)(r_ui_t* this, r_ui_widget_t* parent, const wchar_t* title);
} r_ui_i;

#ifdef __cplusplus
}
#endif