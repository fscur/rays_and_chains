#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_plugin_load_info_t r_plugin_load_info_t;
typedef struct r_api_db_t r_api_db_t;
typedef struct r_debug_api_t r_debug_api_t;
typedef struct r_window_api_t r_window_api_t;
typedef struct r_plugin_t r_plugin_t;

typedef struct plugin_a_t {
  r_debug_api_t* debug_api;
  r_window_api_t* window_api;
} plugin_a_t;

dll_export r_plugin_t* //
load_plugin_a(r_plugin_load_info_t* load_info);

dll_export size_t //
get_size_plugin_a();

dll_export u32 //
get_id_plugin_a();

dll_export void //
plugin_a_init(plugin_a_t* this, r_api_db_t* api_db);

dll_export void //
plugin_a_update(plugin_a_t* this, f64 dt);

dll_export i32 plugin_a_add(i32 a, i32 b);
dll_export i32 plugin_a_sub(i32 a, i32 b);
dll_export i32 plugin_a_mul(i32 a, i32 b);
dll_export i32 plugin_a_div(i32 a, i32 b);

#ifdef __cplusplus
}
#endif