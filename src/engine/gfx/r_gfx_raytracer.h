#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

struct r_gfx_scene_t;
struct r_media_bitmap_t;

dll_export r_color_t //
r_gfx_raytracer_li(struct r_gfx_scene_t* scene, r_ray_t ray);

dll_export void //
r_gfx_raytracer_start_raytracing(struct r_media_bitmap_t* image, f32 dt);

#ifdef __cplusplus
}
#endif