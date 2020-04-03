#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_ui_renderer_t r_ui_renderer_t;
typedef struct r_ui_renderer_i r_ui_renderer_i;
typedef struct r_plugin_load_info_t r_plugin_load_info_t;
typedef struct r_api_db_i r_api_db_i;

#define R_UI_RENDERER_IMGUI_API_NAME "r_ui_renderer_imgui"

dll_export void //
r_ui_renderer_imgui_load(r_lib_load_info_t* load_info);

dll_export size_t //
r_ui_renderer_imgui_get_size(void);

dll_export size_t //
r_ui_renderer_imgui_get_api_size(void);

dll_export void //
r_ui_renderer_imgui_init(r_ui_renderer_i* api, r_api_db_i* api_db);

dll_export void //
r_ui_renderer_imgui_destroy(r_ui_renderer_t* this);


#ifdef __cplusplus
}
#endif