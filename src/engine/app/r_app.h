#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_time_t r_time_t;
typedef struct r_memory_t r_memory_t;
typedef struct r_window_t r_window_t;
typedef struct r_plugin_manager_t r_plugin_manager_t;

typedef struct r_app_info_t {
  char title[256];
  i32 width;
  i32 height;
  i32 x;
  i32 y;
  r_color_t back_color;
  f64 desired_fps;
  r_time_t* time;
} r_app_info_t;

typedef struct r_app_t {
  r_memory_t* memory;
  r_window_t* window;
  r_plugin_manager_t* plugin_manager;
  r_time_t* time;
  bool running;
} r_app_t;

dll_export r_app_t* //
r_app_create(r_memory_t* memory, r_app_info_t* app_info);

dll_export void //
r_app_run(r_app_t* state);

dll_export void //
r_app_init(r_app_t* state);

dll_export void //
r_app_load(r_app_t* state);

dll_export void //
r_app_input(r_app_t* state);

dll_export void //
r_app_update(r_app_t* state);

dll_export void //
r_app_render(const r_app_t* state);

dll_export void //
r_app_unload(const r_app_t* state);

dll_export void //
r_app_destroy(const r_app_t* state);

#ifdef __cplusplus
}
#endif