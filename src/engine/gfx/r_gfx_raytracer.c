#include "engine/core/r_core_math.h"
#include "engine/media/r_media_bitmap.h"
#include "r_gfx_camera.h"
#include "r_gfx_scene.h"
#include "r_gfx_raytracer.h"

r_color_t //
r_gfx_raytracer_li(r_gfx_scene_t* scene, r_ray_t ray) {
  f32 t_min = scene->camera->far_plane;

  if (ray_plane_intersection(ray, scene->floor, &t_min))
    return (r_color_t){1.0f, 0.0f, 0.0f, 1.0f};
  else
    return scene->sky_color;
}

void //
r_gfx_raytracer_start_raytracing(r_media_bitmap_t* image, f32 dt) {

  r_gfx_camera_t camera = {0};
  camera.near_plane = 1.0;
  camera.far_plane = 1001.0;
  camera.fov = 90;
  camera.position = (r_v3_t){0.0, dt, 1.0};
  camera.look_at = (r_v3_t){0.0, 0.0, 0.0};

  camera.up = (r_v3_t){0.0, 1.0, 0.0};
  camera.direction = norm3(sub3(camera.position, camera.look_at));
  camera.right = norm3(cross3(camera.up, camera.direction));
  camera.up = cross3(camera.direction, camera.right);

  r_plane_t plane = {0};
  plane.p = (r_v3_t){0.0f, 0.0f, 0.0f};
  plane.n = (r_v3_t){0.0f, 1.0f, 0.0f};
  r_gfx_scene_t scene = {0};
  scene.sky_color = (r_color_t){0.5f, 0.6f, 0.8f, 1.0f};
  scene.camera = &camera;
  scene.floor = plane;

  f32 x, y, w, h;

  w = (f32)image->width;
  h = (f32)image->height;

  f32 x_factor = 1.0f / w;
  f32 y_factor = 1.0f / h;
  f32 x_aspect = w > h ? w / h : 1.0f;
  f32 y_aspect = h > w ? h / w : 1.0f;

  u32* pixels = (u32*)image->data;

  r_v3_t film_z = add3(camera.position, mul3(camera.direction, -camera.near_plane));

  for (y = 0; y < h; ++y) {
    r_v3_t film_y = mul3(camera.up, (y * y_factor * 2.0f - 1.0f) * y_aspect);

    for (x = 0.0f; x < w; ++x) {
      r_v3_t film_x = mul3(camera.right, (x * x_factor * 2.0f - 1.0f) * x_aspect);
      r_v3_t film_pos = add3(add3(film_x, film_y), film_z);
      r_ray_t ray = {camera.position, norm3(sub3(film_pos, camera.position))};

      r_color_t color = r_gfx_raytracer_li(&scene, ray);

      u8 r = round_f32_to_u8(color.r * 255.0f);
      u8 g = round_f32_to_u8(color.g * 255.0f);
      u8 b = round_f32_to_u8(color.b * 255.0f);
      u8 a = round_f32_to_u8(color.a * 255.0f);

      *pixels++ = from_u8_to_32(a, r, g, b);
    }
  }
}