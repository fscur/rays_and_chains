#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct sandbox_t {
  r_lib_t* lib;
  r_memory_arena_t* memory_arena;
  bool running;
  r_window_t* main_window;
  r_ui_t* ui;
  r_ui_renderer_t* ui_renderer;
} sandbox_t;

dll_export void //
sandbox_load(r_lib_load_info_t* load_info);

dll_export size_t //
sandbox_get_api_size();

dll_export size_t //
sandbox_get_size();

dll_export u32 //
sandbox_get_id();

#ifdef __cplusplus
}
#endif