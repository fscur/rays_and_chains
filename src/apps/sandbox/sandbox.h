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
typedef struct r_ui_t r_ui_t;
typedef struct r_ui_renderer_t r_ui_renderer_t;

typedef struct sandbox_t {
  r_lib_t* lib;
  r_memory_arena_t* memory_arena;
  bool running;
  r_window_t* main_window;
  r_ui_t* ui;
  r_ui_renderer_t* ui_renderer;
} sandbox_t;

dll_export void //
sandbox_load(r_lib_load_info_t* load_info);

dll_export size_t //
sandbox_get_api_size();

dll_export size_t //
sandbox_get_size();

dll_export u32 //
sandbox_get_id();

dll_export r_app_info_t //
sandbox_get_app_info();

dll_export void //
sandbox_init(sandbox_t* this, r_api_db_i* api_db);

dll_export void //
sandbox_run(sandbox_t* this, r_frame_info_t* frame_info);

dll_export void //
sandbox_destroy(sandbox_t* this);

#ifdef __cplusplus
}
#endif