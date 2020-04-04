#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <wchar.h>
#include <stdio.h>

#include "r_core_version.h"
#include "r_core_defines.h"

// cache line = 64 bytes = 64 * 8 bits = 512 bits = 16 i32 = 8 i64;

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

#include "r_core_math_types.h"

typedef struct r_datetime_t {
  i16 year;
  i16 month;
  i16 day_of_week;
  i16 day;
  i16 hour;
  i16 minute;
  i16 second;
  i16 milli_seconds;
} r_datetime_t;

typedef struct r_frame_info_t {
  f64 desired_fps;
  f64 desired_ms_per_frame;
  f64 dt;
  f64 now;
  i64 frame_count;
} r_frame_info_t;

typedef struct r_app_info_t {
  wchar_t title[R_SHORT_STRING_LENGTH];
  char log_filename[R_LONG_STRING_LENGTH];
  i32 width;
  i32 height;
  i32 x;
  i32 y;
  f64 desired_fps;
  bool disable_log_to_file;
} r_app_info_t;

typedef struct r_success_t {
  void* data;
} r_success_t;

typedef struct r_error_t {
  u8 message[R_SHORT_STRING_LENGTH];
  u64 code;
  void* data;
} r_error_t;

typedef void (*R_RESULT_ON_SUCCESS)(r_success_t* success);
typedef void (*R_RESULT_ON_ERROR)(r_error_t* error);

typedef struct r_result_t {
  R_RESULT_ON_SUCCESS on_success;
  R_RESULT_ON_ERROR on_error;
} r_result_t;

typedef struct r_lib_load_info_t r_lib_load_info_t;
typedef struct r_api_db_i r_api_db_i;
typedef struct r_api_db_t r_api_db_t;
typedef struct r_app_api_t r_app_api_t;
typedef struct r_app_t r_app_t;
typedef struct r_window_t r_window_t;
typedef struct r_lib_t r_lib_t;
typedef struct r_gfx_renderer_t r_gfx_renderer_t;
typedef struct r_ui_t r_ui_t;
typedef struct r_ui_renderer_t r_ui_renderer_t;
typedef struct r_memory_arena_t r_memory_arena_t;

#ifdef __cplusplus
}
#endif