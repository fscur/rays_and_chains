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
typedef struct r_api_db_i r_api_db_i;

typedef struct r_app_host_t {
  r_memory_t* memory;
  r_window_t* window;
  r_ui_t* ui;
  r_frame_info_t* frame_info;
  r_app_t* app;
  r_api_db_i* api_db_api;
  r_api_db_t* api_db;
  r_gfx_renderer_t* renderer;
  bool running;
  char libs_path[SHORT_STRING_LENGTH];
  r_lib_t libs[MAX_PLUGINS_COUNT];
  i32 lib_count;
  u8 reloaded_libs[MAX_PLUGINS_COUNT];
  u8 reloaded_lib_count;
} r_app_host_t;

dll_export size_t //
r_app_host_get_size();

dll_export r_app_host_t* //
r_app_host_create(r_memory_t* memory, r_frame_info_t* frame_info);

dll_export void //
r_app_host_load_app(r_app_host_t* this, const char* filename);

dll_export void //
r_app_host_run(r_app_host_t* this);

dll_export void //
r_app_host_init(r_app_host_t* this);

dll_export void //
r_app_host_destroy(const r_app_host_t* this);

#ifdef __cplusplus
}
#endif