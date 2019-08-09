#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_plugin_load_info_t r_plugin_load_info_t;
typedef struct r_api_db_t r_api_db_t;
typedef struct r_debug_api_t r_debug_api_t;
typedef struct r_window_api_t r_window_api_t;
typedef struct r_ui_api_t r_ui_api_t;
typedef struct r_string_api_t r_string_api_t;
typedef struct r_window_t r_window_t;
typedef struct r_plugin_t r_plugin_t;

typedef struct ImGuiContext ImGuiContext;
typedef struct ImGuiIO ImGuiIO;

#define IMGUI_API_ID 257

typedef struct imgui_t {
  r_debug_api_t* debug_api;
  r_window_api_t* window_api;
  r_ui_api_t* ui_api;
  r_string_api_t* string_api;
  r_window_t* window;
  ImGuiContext* context;
  ImGuiIO* io;
} imgui_t;

dll_export r_plugin_t* //
load_r_ui_imgui(r_plugin_load_info_t* load_info);

dll_export size_t //
get_size_r_ui_imgui();

dll_export u32 //
get_id_r_ui_imgui();

dll_export void //
imgui_init(imgui_t* this, r_api_db_t* api_db);

dll_export void //
imgui_destroy(imgui_t* this);

#ifdef __cplusplus
}
#endif