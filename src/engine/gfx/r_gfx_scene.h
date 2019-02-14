#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

struct r_gfx_camera_t;

typedef struct r_gfx_scene_t {
  r_color_t sky_color;
  r_gfx_camera_t* camera;
  r_plane_t floor;
} r_gfx_scene_t;

#ifdef __cplusplus
}
#endif