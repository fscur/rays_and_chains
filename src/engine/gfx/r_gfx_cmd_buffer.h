#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_gfx_cmd_buffer_t {
  u64 cmds[kilobytes(64)];
  size_t cmd_count;
} r_gfx_cmd_buffer_t;

#ifdef __cplusplus
}
#endif