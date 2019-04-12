#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef u64 r_gfx_cmd_t;

typedef struct r_gfx_cmd_buffer_t {
  r_gfx_cmd_t cmds[kilobytes(64)];
  size_t cmd_count;
} r_gfx_cmd_buffer_t;

typedef struct r_gfx_renderer_t {
  r_gfx_cmd_buffer_t cmd_buffer;
} r_gfx_renderer_t;

dll_export void //
r_gfx_renderer_add_cmd(r_gfx_renderer_t* this, r_gfx_cmd_t cmd);

#ifdef __cplusplus
}
#endif