#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

struct r_gfx_scene_t;
struct r_media_bitmap_t;

r_color_t //
r_graphics_raytracer_li(r_gfx_scene_t* scene, r_ray_t ray);

void //
r_graphics_raytracer_start_raytracing(r_media_bitmap_t* image, f32 dt);

#ifdef __cplusplus
}
#endif