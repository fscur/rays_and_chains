#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_memory_t r_memory_t;
typedef struct r_window_t r_window_t;
typedef struct r_ui_t r_ui_t;
typedef struct r_plugin_manager_t r_plugin_manager_t;
typedef struct r_api_db_t r_api_db_t;

typedef struct r_app_info_t {
  char filename[SHORT_STRING_LENGTH];
  wchar_t title[SHORT_STRING_LENGTH];
  i32 width;
  i32 height;
  i32 x;
  i32 y;
  r_color_t back_color;
  f64 desired_fps;
  r_frame_info_t* frame_info;
} r_app_info_t;

typedef struct r_app_context_t {
  r_memory_t* memory;
  r_window_t* window;
  r_ui_t* ui;
  r_frame_info_t* frame_info;
  r_app_t* app;
  r_api_db_t* api_db;
  r_plugin_manager_t* plugin_manager;
  bool running;
} r_app_context_t;

dll_export inline size_t //
r_app_context_get_size();

dll_export r_app_context_t* //
r_app_context_create(r_memory_t* memory, r_app_info_t* app_info);

dll_export void //
r_app_context_run(r_app_context_t* this);

dll_export void //
r_app_context_init(r_app_context_t* this);

dll_export void //
r_app_context_destroy(const r_app_context_t* this);

#ifdef __cplusplus
}
#endif