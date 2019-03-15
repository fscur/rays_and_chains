#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_memory_t r_memory_t;
typedef struct r_window_t r_window_t;
typedef struct r_plugin_manager_t r_plugin_manager_t;

typedef struct r_app_info_t {
  char title[256];
  i32 width;
  i32 height;
  r_color_t back_color;
} r_app_info_t;

typedef struct r_app_t {
  r_memory_t* memory;
  r_window_t* window;
  r_plugin_manager_t* plugin_manager;
  bool running;
  f64 dt;
  f64 time;
} r_app_t;

// #define R_APP_API "r_app.dll"
// #define R_APP_API_CREATE "r_app_create"
// #define R_APP_API_RUN "r_app_run"
// #define R_APP_API_INIT "r_app_init"
// #define R_APP_API_LOAD "r_app_load"
// #define R_APP_API_INPUT "r_app_input"
// #define R_APP_API_UPDATE "r_app_update"
// #define R_APP_API_RENDER "r_app_render"
// #define R_APP_API_UNLOAD "r_app_unload"
// #define R_APP_API_DESTROY "r_app_destroy"

// typedef r_app_state_t* (*R_APP_CREATE)(r_memory_t*, r_app_info_t);
// typedef void (*R_APP_RUN)(r_app_state_t*);
// typedef void (*R_APP_INIT)(r_app_state_t*);
// typedef void (*R_APP_LOAD)(r_app_state_t*);
// typedef void (*R_APP_INPUT)(r_app_state_t*);
// typedef void (*R_APP_UPDATE)(r_app_state_t*);
// typedef void (*R_APP_RENDER)(r_app_state_t*);
// typedef void (*R_APP_UNLOAD)(r_app_state_t*);
// typedef void (*R_APP_DESTROY)(r_app_state_t*);

// typedef struct r_app_api_t {
//   void* handle;
//   r_app_state_t* (*create)(r_memory_t*, r_app_info_t);
//   void (*run)(r_app_state_t*);
//   void (*init)(r_app_state_t*);
//   void (*load)(r_app_state_t*);
//   void (*input)(r_app_state_t*);
//   void (*update)(r_app_state_t*);
//   void (*render)(r_app_state_t*);
//   void (*unload)(r_app_state_t*);
//   void (*destroy)(r_app_state_t*);
// } r_app_api_t;

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