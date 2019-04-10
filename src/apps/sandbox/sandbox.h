#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_lib_load_info_t r_lib_load_info_t;
typedef struct r_api_db_t r_api_db_t;
typedef struct r_app_api_t r_app_api_t;
typedef struct r_debug_api_t r_debug_api_t;
typedef struct r_window_api_t r_window_api_t;
typedef struct r_ui_api_t r_ui_api_t;
typedef struct r_string_api_t r_string_api_t;
typedef struct r_window_t r_window_t;
typedef struct r_lib_t r_lib_t;

typedef struct sandbox_t {
  r_debug_api_t* debug_api;
  r_window_api_t* window_api;
  r_ui_api_t* ui_api;
  r_string_api_t* string_api;
} sandbox_t;

dll_export void //
load_sandbox(r_lib_load_info_t* load_info);

dll_export size_t //
get_size_sandbox();

dll_export u32 //
get_id_sandbox();

dll_export void //
sandbox_init(sandbox_t* this, r_api_db_t* api_db);

dll_export void //
sandbox_run(sandbox_t* this, r_frame_info_t* frame_info);

dll_export void //
sandbox_destroy(sandbox_t* this);

#ifdef __cplusplus
}
#endif