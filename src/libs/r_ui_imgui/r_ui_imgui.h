#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_plugin_load_info_t r_plugin_load_info_t;
typedef struct r_api_db_i r_api_db_i;
typedef struct r_debug_i r_debug_i;
typedef struct r_window_i r_window_i;
typedef struct r_ui_i r_ui_i;
typedef struct r_string_i r_string_i;
typedef struct r_window_t r_window_t;
typedef struct r_plugin_t r_plugin_t;

typedef struct ImGuiContext ImGuiContext;
typedef struct ImGuiIO ImGuiIO;

#define IMGUI_API_ID 257

typedef struct imgui_t {
  r_debug_i* debug_api;
  r_window_i* window_api;
  r_ui_i* ui_api;
  r_string_i* string_api;
  r_window_t* window;
  ImGuiContext* context;
  ImGuiIO* io;
} imgui_t;

dll_export void //
r_ui_imgui_load(r_lib_load_info_t* load_info);

dll_export size_t //
r_ui_imgui_get_size();

dll_export u32 //
r_ui_imgui_get_id();

dll_export void //
r_ui_imgui_init(imgui_t* this, r_api_db_i* api_db);

dll_export void //
r_ui_imgui_destroy(imgui_t* this);

#ifdef __cplusplus
}
#endif