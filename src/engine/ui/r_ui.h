#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/ui/r_ui_types.h"

dll_export r_ui_frame_t* //
r_ui_create_frame(r_ui_t* this, r_ui_widget_t* parent, const wchar_t* title);

dll_export r_ui_menu_t* //
r_ui_create_main_menu(r_ui_t* this, r_ui_widget_t* parent);

dll_export r_ui_menu_t* //
r_ui_create_menu(r_ui_t* this, r_ui_widget_t* parent, const wchar_t* label);

dll_export r_ui_button_t* //
r_ui_create_button(r_ui_t* this,
                   r_ui_widget_t* parent,
                   const wchar_t* label,
                   bool enabled,
                   R_UI_BUTTON_CLICK_CALLBACK callback,
                   void* context);

dll_export r_ui_menu_item_t* //
r_ui_create_menu_item(r_ui_t* this,
                      r_ui_widget_t* parent,
                      const wchar_t* label,
                      const wchar_t* shortcut,
                      bool enabled,
                      R_UI_MENU_ITEM_CLICK_CALLBACK callback,
                      void* context);

dll_export void //
r_ui_set_theme(r_ui_t* this, u32 theme_id);

#ifdef __cplusplus
}
#endif
