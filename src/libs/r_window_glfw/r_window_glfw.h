#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_plugin_load_info_t r_plugin_load_info_t;
typedef struct r_api_db_t r_api_db_t;
typedef struct r_debug_api_t r_debug_api_t;
typedef struct r_window_api_t r_window_api_t;
typedef struct r_string_api_t r_string_api_t;
typedef struct r_window_t r_window_t;
typedef struct r_plugin_t r_plugin_t;

#define GLFW_API_ID 256

typedef struct glfw_t {
  r_debug_api_t* debug_api;
  r_window_api_t* window_api;
  r_string_api_t* string_api;
  r_window_t* window;
} glfw_t;

dll_export void //
r_window_glfw_load(r_lib_load_info_t* load_info);

dll_export size_t //
r_window_glfw_get_size();

dll_export u32 //
r_window_glfw_get_id();

dll_export void //
r_window_glfw_init(glfw_t* this, r_api_db_t* api_db);

dll_export void //
r_window_glfw_destroy(glfw_t* this);

#ifdef __cplusplus
}
#endif