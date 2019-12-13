#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_lib_load_info_t r_lib_load_info_t;
typedef struct r_api_db_i r_api_db_i;
typedef struct r_logger_i r_logger_i;
typedef struct r_window_i r_window_i;
typedef struct r_string_i r_string_i;
typedef struct r_window_t r_window_t;
typedef struct r_window_t r_window_t;
typedef struct r_lib_t r_lib_t;

typedef struct hammer_t {
  r_lib_t lib;
  r_memory_arena_t* memory_arena;
  bool running;
  r_window_t* main_window;
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
hammer_init(hammer_t* this, r_api_db_i* api_db);

dll_export void //
hammer_run(hammer_t* this, r_frame_info_t* frame_info);

dll_export void //
hammer_destroy(hammer_t* this);

#ifdef __cplusplus
}
#endif