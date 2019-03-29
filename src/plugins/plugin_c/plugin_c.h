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

typedef struct plugin_c_t {
  r_debug_api_t* debug_api;
  r_window_api_t* window_api;
} plugin_c_t;

dll_export r_plugin_t* //
load_plugin_c(r_plugin_load_info_t* load_info);

dll_export size_t //
get_size_plugin_c();

dll_export u32 //
get_id_plugin_c();

dll_export void //
plugin_c_init(plugin_c_t* this, r_api_db_t* api_db);

dll_export void //
plugin_c_update(plugin_c_t* this, f64 dt);

dll_export i32 plugin_c_add(i32 a, i32 b);
dll_export i32 plugin_c_sub(i32 a, i32 b);

#ifdef __cplusplus
}
#endif