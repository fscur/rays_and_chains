#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_UI_API_ID 3
#define R_UI_API_NAME "r_ui"

typedef struct r_ui_t r_ui_t;

typedef void (*R_UI_RENDER)(const r_ui_t* ui);
typedef void (*R_UI_UPDATE)(r_ui_t* ui);

typedef struct r_ui_api_t {
  r_ui_t* ui;
  R_UI_RENDER render;
  R_UI_UPDATE update;
} r_ui_api_t;

#ifdef __cplusplus
}
#endif