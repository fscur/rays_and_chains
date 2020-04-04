#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_lib_load_info_t r_lib_load_info_t;

dll_export size_t //
r_gfx_opengl_get_size(void);

dll_export size_t //
r_gfx_opengl_get_api_size(void);

dll_export void //
r_gfx_opengl_load(r_lib_load_info_t* load_info);

#ifdef __cplusplus
}
#endif