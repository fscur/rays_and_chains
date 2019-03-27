#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_plugin_load_info_t r_plugin_load_info_t;
typedef struct r_api_db_t r_api_db_t;
typedef struct r_debug_api_t r_debug_api_t;
typedef struct r_plugin_t r_plugin_t;
typedef struct plugin_a_api_t plugin_a_api_t;

typedef struct plugin_b_t {
  plugin_a_api_t* plugin_a_api;
  r_debug_api_t* debug_api;
} plugin_b_t;

dll_export size_t //
get_size_plugin_b();

dll_export u32 //
get_id_plugin_b();

dll_export r_plugin_t* //
load_plugin_b(r_plugin_load_info_t* load_info);

dll_export void //
plugin_b_init(plugin_b_t* this, r_api_db_t* api_db);

dll_export void //
plugin_b_render(plugin_b_t* this);

dll_export void //
plugin_b_print_sum(plugin_b_t* this, i32 a, i32 b);

#ifdef __cplusplus
}
#endif