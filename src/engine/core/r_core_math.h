#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "r_core_types.h"

u32
from_u8_to_32(u8 h1, u8 h0, u8 l1, u8 l0) {
  u32 result = (h1 << 24) | (h0 << 16) | (l1 << 8) | (l0 << 0);
  return result;
}

u8
round_f32_to_u8(f32 value) {
  return (u8)roundf(value);
}

i8
round_f32_to_i8(f32 value) {
  return (i8)roundf(value);
}

i32
round_f32_to_i32(f32 value) {
  return (i32)roundf(value);
}

f32
dot2(r_v2_t a, r_v2_t b) {
  return a.x * b.x + a.y * b.y;
}

f32
len2(r_v2_t v) {
  return sqrtf(dot2(v, v));
}

r_v3_t
add3(r_v3_t a, r_v3_t b) {
  return (r_v3_t){a.x + b.x, a.y + b.y, a.z + b.z};
}

r_v3_t
sub3(r_v3_t a, r_v3_t b) {
  return (r_v3_t){a.x - b.x, a.y - b.y, a.z - b.z};
}

r_v3_t
neg3(r_v3_t v) {
  return (r_v3_t){-v.x, -v.y, -v.z};
}

r_v3_t
mul3(r_v3_t v, f32 s) {
  return (r_v3_t){v.x * s, v.y * s, v.z * s};
}

r_v3_t
dir_v3_t(r_v3_t v, f32 s) {
  return (r_v3_t){v.x / s, v.y / s, v.z / s};
}

f32
dot3(r_v3_t a, r_v3_t b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

r_v3_t
cross3(r_v3_t a, r_v3_t b) {
  return (r_v3_t){a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y};
}

f32
len3(r_v3_t v) {
  return sqrtf(dot3(v, v));
}

r_v3_t
norm3(r_v3_t v) {
  return dir_v3_t(v, len3(v));
}

bool
ray_plane_intersection(r_ray_t ray, r_plane_t plane, f32* t_min) {

  f32 denom = dot3(plane.n, ray.d);

  // eps = 1e-6
  // if (denom > eps)
  //   return false;

  r_v3_t v = sub3(plane.p, ray.o);
  *t_min = dot3(v, plane.n) / denom; // +eps?????
  return (*t_min >= 0.0f);
}

#ifdef __cplusplus
}
#endif