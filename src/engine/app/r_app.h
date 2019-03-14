#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_memory_arena_t r_memory_arena_t;
typedef struct r_window_t r_window_t;
typedef struct r_app_ui_t r_app_ui_t;

typedef struct r_app_info_t {
  char title[256];
  i32 width;
  i32 height;
  r_color_t back_color;

} r_app_info_t;

typedef struct r_app_state_t {
  r_memory_arena_t* memory_arena;
  r_window_t* window;
  r_app_ui_t* ui;
  f32 dt;
  bool running;
} r_app_state_t;

typedef r_app_state_t* (*R_APP_CREATE)(r_memory_arena_t*, r_app_info_t);
typedef void (*R_APP_RUN)(r_app_state_t*);
typedef void (*R_APP_INIT)(r_app_state_t*);
typedef void (*R_APP_LOAD)(r_app_state_t*);
typedef void (*R_APP_INPUT)(r_app_state_t*);
typedef void (*R_APP_UPDATE)(r_app_state_t*);
typedef void (*R_APP_RENDER)(r_app_state_t*);
typedef void (*R_APP_UNLOAD)(r_app_state_t*);
typedef void (*R_APP_DESTROY)(r_app_state_t*);

typedef struct r_app_api {
  void* handle;
  r_app_state_t* (*create)(r_memory_arena_t*, r_app_info_t);
  void (*run)(r_app_state_t*);
  void (*init)(r_app_state_t*);
  void (*load)(r_app_state_t*);
  void (*input)(r_app_state_t*);
  void (*update)(r_app_state_t*);
  void (*render)(r_app_state_t*);
  void (*unload)(r_app_state_t*);
  void (*destroy)(r_app_state_t*);
} r_app_api;

dll_export r_app_state_t* //
r_app_create(r_memory_arena_t* memory_arena, r_app_info_t app_info);

dll_export void //
r_app_run(r_app_state_t* state);

dll_export void //
r_app_init(r_app_state_t* state);

dll_export void //
r_app_load(r_app_state_t* state);

dll_export void //
r_app_input(r_app_state_t* state);

dll_export void //
r_app_update(r_app_state_t* state);

dll_export void //
r_app_render(const r_app_state_t* state);

dll_export void //
r_app_unload(const r_app_state_t* state);

dll_export void //
r_app_destroy(const r_app_state_t* state);

#ifdef __cplusplus
}
#endif