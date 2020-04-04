#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_UI_RENDERER_IMGUI_API_NAME "r_ui_renderer_imgui"

typedef struct r_ui_renderer_t r_ui_renderer_t;
typedef struct r_ui_renderer_imgui_i r_ui_renderer_imgui_i;

typedef struct r_ui_renderer_imgui_i {
  size_t (*get_size)(void);
  char* (*get_api_name)(void);
  void (*init)(r_ui_renderer_imgui_i* api, r_api_db_i* db);
  void (*destroy)(r_ui_renderer_t* state);
  void (*render)(r_ui_renderer_t* ui_renderer, r_ui_t* ui);
  r_ui_renderer_t* (*create)();
} r_ui_renderer_imgui_i;

#ifdef __cplusplus
}
#endif