#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define MAX_CMD_COUNT 512

typedef u64 r_gfx_cmd_key_t;
typedef void* r_gfx_cmd_data_t;
typedef void (*R_GFX_CMD_DISPATCHER)(const void* data);

typedef struct r_gfx_cmd_buffer_t {
  r_gfx_cmd_key_t keys[MAX_CMD_COUNT];
  r_gfx_cmd_data_t data[MAX_CMD_COUNT];
  R_GFX_CMD_DISPATCHER fn[MAX_CMD_COUNT];
  size_t cmd_count;
} r_gfx_cmd_buffer_t;

typedef struct r_gfx_cmd_t {
  r_gfx_cmd_key_t key;
  r_gfx_cmd_data_t data;
  R_GFX_CMD_DISPATCHER fn;
} r_gfx_cmd_t;

typedef struct r_gfx_renderer_t {
  r_gfx_cmd_buffer_t cmd_buffer;
  R_GFX_CMD_DISPATCHER clear_color_dispatcher; //set by backend implementation
} r_gfx_renderer_t;

typedef struct r_gfx_clear_color_cmd_t {
  r_color_t color;
} r_gfx_clear_color_cmd_t;

dll_export void //
r_gfx_renderer_add_cmd(r_gfx_renderer_t* this, r_gfx_cmd_t cmd);

dll_export r_gfx_cmd_t* //
r_gfx_renderer_create_clear_color_buffer_cmd(r_gfx_renderer_t* this);

dll_export void //
r_gfx_renderer_clear(r_gfx_renderer_t* this);

dll_export void //
r_gfx_renderer_sort(r_gfx_renderer_t* this);

dll_export void //
r_gfx_renderer_submit(r_gfx_renderer_t* this);

#ifdef __cplusplus
}
#endif