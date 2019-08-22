#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include <math.h>

typedef struct r_v2_t {
  f32 x, y;
} r_v2_t;

typedef struct r_v3_t {
  f32 x, y, z;
} r_v3_t;

typedef struct r_v4_t {
  f32 x, y, z, w;
} r_v4_t;

typedef struct r_m33_t {
  f32 xx, xy, xz;
  f32 yx, yy, yz;
  f32 zx, zy, zz;
} r_m33_t;

typedef struct r_m44_t {
  f32 xx, xy, xz, xw;
  f32 yx, yy, yz, yw;
  f32 zx, zy, zz, zw;
  f32 wx, wy, wz, ww;
} r_m44_t;

typedef struct r_color_t {
  f32 r, g, b, a;
} r_color_t;

#define R_COLOR_BLACK                                                                              \
  (r_color_t) { 0.0f, 0.0f, 0.0f, 1.0f }

typedef struct r_ray_t {
  r_v3_t o, d;
} r_ray_t;

typedef struct r_plane_t {
  r_v3_t p, n;
} r_plane_t;

#ifdef __cplusplus
}
#endif