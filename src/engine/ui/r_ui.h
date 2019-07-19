#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef enum r_ui_control_type_t {
  R_UI_MENU, R_UI_MENU_ITEM 
} r_ui_control_type_t;

typedef struct r_ui_control_t {
  r_ui_control_type_t type;
  r_v2_t position;
  r_v2_t size;
} r_ui_control_t;

typedef struct r_ui_canvas_t {
  r_ui_control_t controls[256];
} r_ui_canvas_t;

typedef struct r_window_t r_window_t;
typedef struct r_media_bitmap_t r_media_bitmap_t;

typedef struct r_ui_t {
  r_window_t* window;
  
  r_media_bitmap_t* image;
  u32 texture_id;
  r_color_t clear_color;
  f32 dt;
} r_ui_t;

dll_export void //
r_ui_init(r_ui_t* ui);

dll_export void //
r_ui_unload(r_ui_t* ui);

#ifdef __cplusplus
}
#endif
