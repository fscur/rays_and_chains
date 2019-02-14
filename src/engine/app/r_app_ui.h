#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

struct r_app_window_t;
struct r_media_bitmap_t;

typedef struct r_app_ui_t {
  r_app_window_t* window;
  r_media_bitmap_t* image;
  u32 texture_id;
  r_color_t clear_color;
  f32 dt;
} r_app_ui_t;

void //
r_app_ui_init(r_app_ui_t* ui);

void //
r_app_ui_load(r_app_ui_t* ui);

void //
r_app_ui_render(r_app_ui_t* ui);

void //
r_app_ui_unload(r_app_ui_t* ui);

#ifdef __cplusplus
}
#endif
