#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_plugin_load_info_t r_plugin_load_info_t;
typedef struct r_api_db_i r_api_db_i;
typedef struct r_debug_i r_debug_i;
typedef struct r_plugin_t r_plugin_t;
typedef struct r_gfx_renderer_i r_gfx_renderer_i;

#define OPENGL_API_ID 258

typedef struct opengl_t {
  r_debug_i* debug;
  r_gfx_renderer_i* renderer;
} opengl_t;

dll_export void //
r_gfx_opengl_load(r_lib_load_info_t* load_info);

dll_export size_t //
r_gfx_opengl_get_size();

dll_export u32 //
r_gfx_opengl_get_id();

dll_export void //
r_gfx_opengl_init(opengl_t* this, r_api_db_i* api_db);

dll_export void //
r_gfx_opengl_destroy(opengl_t* this);

#ifdef __cplusplus
}
#endif