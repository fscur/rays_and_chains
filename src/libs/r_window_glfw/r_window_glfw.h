#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_plugin_load_info_t r_plugin_load_info_t;
typedef struct r_api_db_i r_api_db_i;
typedef struct r_logger_i r_logger_i;
typedef struct r_window_i r_window_i;
typedef struct r_string_i r_string_i;
typedef struct r_window_t r_window_t;
typedef struct r_plugin_t r_plugin_t;

#define GLFW_API_ID 256

typedef struct glfw_t {
  r_logger_i* debug_api;
  r_window_i* window_api;
  r_string_i* string_api;
  r_window_t* window;
} glfw_t;

dll_export void //
r_window_glfw_load(r_lib_load_info_t* load_info);

dll_export size_t //
r_window_glfw_get_size();

dll_export void //
r_window_glfw_init(glfw_t* this, r_api_db_i* api_db);

dll_export void //
r_window_glfw_destroy(glfw_t* this);

#ifdef __cplusplus
}
#endif