#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_gfx_camera_t {
  f32 near_plane;
  f32 far_plane;
  f32 fov;
  r_v3_t position;
  r_v3_t look_at;
  r_v3_t up;
  r_v3_t right;
  r_v3_t direction;
} r_gfx_camera_t;

#ifdef __cplusplus
}
#endif