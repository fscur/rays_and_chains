#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#include <math.h>

#define local static
#define internal static
#define kilobytes(Value) ((Value)*1024LL)
#define megabytes(Value) (kilobytes(Value) * 1024LL)
#define gigabytes(Value) (megabytes(Value) * 1024LL)
#define terabytes(Value) (gigabytes(Value) * 1024LL)

#if _DEBUG
#define assert(expression)                                                                         \
  if (!(expression)) {                                                                             \
    *(int*)0 = 0;                                                                                  \
  }
#else
#define assert(expression)
#endif

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;
typedef double f64;

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

typedef struct r_ray_t {
  r_v3_t o, d;
} r_ray_t;

typedef struct r_plane_t {
  r_v3_t p, n;
} r_plane_t;

// typedef struct r_linked_list_node {
//   struct r_linked_list_node* next;
//   struct r_linked_list_node* prev;
//   void* data;
// } r_linked_list_node;

// typedef struct r_linked_list {
//   r_linked_list_node* first;
// } r_linked_list;

#if defined(WIN32)
#define dll_export __declspec(dllexport)
#endif

#ifdef __cplusplus
}
#endif