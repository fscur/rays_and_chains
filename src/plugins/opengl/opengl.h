#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_plugin_load_info_t r_plugin_load_info_t;
typedef struct r_api_db_t r_api_db_t;
typedef struct r_debug_api_t r_debug_api_t;
typedef struct r_plugin_t r_plugin_t;
typedef struct r_gfx_renderer_api_t r_gfx_renderer_api_t;

#define OPENGL_API_ID 258

typedef struct opengl_t {
  r_debug_api_t* debug_api;
  r_gfx_renderer_api_t* renderer_api;
} opengl_t;

dll_export r_plugin_t* //
load_opengl(r_plugin_load_info_t* load_info);

dll_export size_t //
get_size_opengl();

dll_export u32 //
get_id_opengl();

dll_export void //
opengl_init(opengl_t* this, r_api_db_t* api_db);

dll_export void //
opengl_destroy(opengl_t* this);

#ifdef __cplusplus
}
#endif