#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define PLUGIN_A_NAME "plugin_a"

typedef struct r_app_api_register_t r_app_api_register_t;
typedef struct r_debug_api_t r_debug_api_t;
typedef struct r_plugin_t r_plugin_t;

typedef void* (*R_PLUGIN_LOADER_FN)(void*, const char*);
typedef void* (*R_APP_FIND_API)(r_app_api_register_t*, const u32);

typedef i32 (*ADDFN)(i32, i32);
typedef i32 (*SUBFN)(i32, i32);
typedef i32 (*MULFN)(i32, i32);
typedef i32 (*DIVFN)(i32, i32);

typedef struct plugin_a_t {
  r_debug_api_t* debug;
} plugin_a_t;

typedef struct plugin_a_api_t {
  void* handle;
  void (*init)(void*, R_APP_FIND_API, r_app_api_register_t*);
  void (*update)(void*, f64);
  i32 (*add)(i32, i32);
  i32 (*sub)(i32, i32);
  i32 (*mul)(i32, i32);
  i32 (*div)(i32, i32);
} plugin_a_api_t;

dll_export r_plugin_t* load_plugin_a(R_PLUGIN_LOADER_FN fn, void* memory_addr, void* handle);
dll_export size_t get_size_plugin_a();
dll_export u32 get_id_plugin_a();

dll_export void //
plugin_a_init(plugin_a_t* plugin_a,
              R_APP_FIND_API find_api_function,
              r_app_api_register_t* api_register);

dll_export void //
plugin_a_update(plugin_a_t* plugin_a, f64 dt);

dll_export i32 plugin_a_add(i32 a, i32 b);
dll_export i32 plugin_a_sub(i32 a, i32 b);
dll_export i32 plugin_a_mul(i32 a, i32 b);
dll_export i32 plugin_a_div(i32 a, i32 b);

#ifdef __cplusplus
}
#endif