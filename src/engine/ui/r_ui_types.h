#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_ui_theme_t {
  u32 id;
  wchar_t* name;
  f32 border_size;
  r_color_t border_color;
  r_color_t menu_background_color;
  r_color_t menu_item_background_color;
} r_ui_theme_t;

#ifdef __cplusplus
}
#endif