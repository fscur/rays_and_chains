#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_lib_load_info_t r_lib_load_info_t;
typedef struct r_api_db_i r_api_db_i;
typedef struct r_app_t r_app_t;
typedef struct r_debug_i r_debug_i;
typedef struct r_window_i r_window_i;
typedef struct r_string_i r_string_i;
typedef struct r_window_t r_window_t;
typedef struct r_lib_t r_lib_t;

#define SANDBOX_API_ID 256

typedef struct hammer_t {
  r_debug_i* debug_api;
  r_window_i* window_api;
  r_string_i* string_api;
} hammer_t;

dll_export void //
hammer_load(r_lib_load_info_t* load_info);

dll_export size_t //
hammer_get_size();

dll_export u32 //
hammer_get_id();

dll_export r_app_info_t //
hammer_get_app_info();

dll_export void //
hammer_init(r_app_t* app, r_api_db_i* api_db);

dll_export void //
hammer_run(hammer_t* this, r_frame_info_t* frame_info);

dll_export void //
hammer_destroy(hammer_t* this);

#ifdef __cplusplus
}
#endif