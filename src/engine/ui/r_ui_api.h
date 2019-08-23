#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_UI_API_ID 3
#define R_UI_API_NAME "r_ui"

typedef struct r_ui_t r_ui_t;
typedef struct r_ui_control_t r_ui_control_t;
typedef struct r_ui_menu_t r_ui_menu_t;
typedef struct r_ui_menu_item_t r_ui_menu_item_t;
typedef struct r_ui_api_t r_ui_api_t;

typedef void (*R_UI_API_BEGIN)(r_ui_api_t* this);
typedef void (*R_UI_API_RENDER)(r_ui_api_t* this);
typedef void (*R_UI_API_END)(r_ui_api_t* this);
typedef void (*R_UI_API_UPDATE)(r_ui_api_t* this);

typedef r_ui_menu_t* (*R_UI_CREATE_MENU)(r_ui_t* this, r_ui_control_t* parent);
typedef r_ui_menu_item_t* (*R_UI_CREATE_MENU_ITEM)(r_ui_t* this,
                                                   r_ui_menu_t* menu,
                                                   const wchar_t* text);

typedef struct r_ui_api_t {
  r_ui_t* ui;
  void* impl_state;
  R_UI_API_BEGIN begin;
  R_UI_API_RENDER render;
  R_UI_API_END end;
  R_UI_API_UPDATE update;
  R_UI_CREATE_MENU create_menu;
  R_UI_CREATE_MENU_ITEM create_menu_item;
} r_ui_api_t;

#ifdef __cplusplus
}
#endif