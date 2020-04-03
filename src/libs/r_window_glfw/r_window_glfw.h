#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_lib_load_info_t r_lib_load_info_t;
typedef struct r_api_db_i r_api_db_i;
typedef struct r_window_i r_window_i;
typedef struct r_window_t r_window_t;

#define R_WINDOW_GLFW_API_NAME "r_window_glfw"

dll_export void //
r_window_glfw_load(r_lib_load_info_t* load_info);

dll_export size_t //
r_window_glfw_get_size();

dll_export size_t //
r_window_glfw_get_api_size();

dll_export void //
r_window_glfw_init_api(r_window_i* window, r_api_db_i* api_db);

dll_export void //
r_window_glfw_destroy(r_window_t* window);

#ifdef __cplusplus
}
#endif