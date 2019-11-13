#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_lib_load_info_t r_lib_load_info_t;
typedef struct r_api_db_t r_api_db_t;
typedef struct r_app_api_t r_app_api_t;
typedef struct r_app_t r_app_t;
typedef struct r_window_t r_window_t;
typedef struct r_lib_t r_lib_t;
typedef struct r_gfx_renderer_t r_gfx_renderer_t;
typedef struct r_api_db_i r_api_db_i;
typedef struct r_debug_i r_debug_i;
typedef struct r_window_i r_window_i;
typedef struct r_ui_i r_ui_i;
typedef struct r_string_i r_string_i;
typedef struct r_gfx_renderer_i r_gfx_renderer_i;
typedef struct r_ui_renderer_i r_ui_renderer_i;

typedef struct sandbox_t {
  r_api_db_i* api_db;
  r_debug_i* debug;
  r_window_i* window;
  r_ui_i* ui;
  r_string_i* string;
  r_gfx_renderer_i* renderer;
  r_ui_renderer_i* ui_renderer;
} sandbox_t;

dll_export void //
sandbox_load(r_lib_load_info_t* load_info);

dll_export size_t //
sandbox_get_size();

dll_export u32 //
sandbox_get_id();

dll_export r_app_info_t //
sandbox_get_app_info();

dll_export void //
sandbox_init(r_app_t* app, r_api_db_i* api_db);

dll_export void //
sandbox_run(sandbox_t* this, r_frame_info_t* frame_info);

dll_export void //
sandbox_destroy(sandbox_t* this);

#ifdef __cplusplus
}
#endif