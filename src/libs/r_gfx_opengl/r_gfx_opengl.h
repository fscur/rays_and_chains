#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_plugin_load_info_t r_plugin_load_info_t;
typedef struct r_api_db_i r_api_db_i;
typedef struct r_logger_i r_logger_i;
typedef struct r_plugin_t r_plugin_t;
typedef struct r_gfx_opengl_i r_gfx_opengl_i;

dll_export void //
r_gfx_opengl_load(r_lib_load_info_t* load_info);

dll_export size_t //
r_gfx_opengl_get_size();

dll_export void //
r_gfx_opengl_init(r_gfx_opengl_i* this, r_api_db_i* api_db);

dll_export void //
r_gfx_opengl_destroy(void* this);

#ifdef __cplusplus
}
#endif