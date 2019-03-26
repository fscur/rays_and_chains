#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

// important: (filipe.scur@gmail.com)
// this should be unique! we have to find a way to have it be unique!
#define PLUGIN_A_ID 256
#define PLUGIN_A_NAME "plugin_a"

typedef struct r_plugin_load_info_t r_plugin_load_info_t;
typedef struct r_app_api_register_t r_app_api_register_t;
typedef struct r_debug_api_t r_debug_api_t;
typedef struct r_plugin_t r_plugin_t;

typedef struct plugin_a_t {
  r_debug_api_t* debug;
} plugin_a_t;

dll_export r_plugin_t* load_plugin_a(r_plugin_load_info_t* load_info);
dll_export size_t get_size_plugin_a();
dll_export u32 get_id_plugin_a();

dll_export void //
plugin_a_init(plugin_a_t* plugin_a,
              r_app_api_register_t* api_register);

dll_export void //
plugin_a_update(plugin_a_t* plugin_a, f64 dt);

#ifdef __cplusplus
}
#endif