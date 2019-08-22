#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include <math.h>

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#define PROG_NAME "r_engine"
#if _DEBUG
#define PROG_VERSION "[dev]"
#define PROG_DESCRIPTION "Rays and chains engine. Development version."
#else
#define PROG_VERSION "0.0.0.1"
#define PROG_DESCRIPTION "Rays and chains engine."
#endif

#define SHORT_STRING_LENGTH 256
#define MAX_FUNCTION_COUNT 64

#define local static
#define internal static
#define global extern

#define kilobytes(value) ((value)*1024LL)
#define megabytes(value) (kilobytes(value) * 1024LL)
#define gigabytes(value) (megabytes(value) * 1024LL)
#define terabytes(value) (gigabytes(value) * 1024LL)

#if _DEBUG
#define assert(expression)                                                                         \
  if (!(expression)) {                                                                             \
    *(int*)0 = 0;                                                                                  \
  }
#else
#define assert(expression)
#endif

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
  wchar_t title[SHORT_STRING_LENGTH];
  i32 width;
  i32 height;
  i32 x;
  i32 y;
  f64 desired_fps;
} r_app_info_t;

typedef struct r_success_t {
  void* data;
} r_success_t;

typedef struct r_error_t {
  u8 message[SHORT_STRING_LENGTH];
  u64 code;
  void* data;
} r_error_t;

typedef void (*R_RESULT_ON_SUCCESS)(r_success_t* success);
typedef void (*R_RESULT_ON_ERROR)(r_error_t* error);

typedef struct r_result_t {
  R_RESULT_ON_SUCCESS on_success;
  R_RESULT_ON_ERROR on_error;
} r_result_t;

typedef struct r_memory_block_t r_memory_block_t;
typedef struct r_lib_load_info_t r_lib_load_info_t;
typedef struct r_api_db_t r_api_db_t;

typedef void* (*R_LIB_LOADER_FN)(void*, const char*);

typedef u32 (*R_LIB_GET_ID)();
typedef u32 (*R_LIB_GET_FN_COUNT)();
typedef size_t (*R_LIB_GET_SIZE)();
typedef void* (*R_LIB_LOAD)(r_lib_load_info_t* load_info);
typedef void* (*R_LIB_INIT)(void* lib_state, r_api_db_t* db);
typedef void* (*R_LIB_DESTROY)(void* lib_state);

typedef struct r_lib_load_info_t {
  R_LIB_LOADER_FN fn;
  void* handle;
  void* lib_memory_addr;
  void* state_memory_addr;
} r_lib_load_info_t;

typedef struct r_lib_t {
  void* functions[MAX_FUNCTION_COUNT];     // 512
  char name[SHORT_STRING_LENGTH];          // 256
  char file_name[SHORT_STRING_LENGTH];     // 256
  char tmp_file_name[SHORT_STRING_LENGTH]; // 256
  r_datetime_t last_modification;          // 16
  void* handle;                            // 8
  r_memory_block_t* memory_block;          // 8
  void* state;                             // 8
  i32 version;                             // 4
  u32 id;                                  // 4
  u32 fn_count;                            // 4
} r_lib_t;                                 // 1332

#if defined(WIN32)
#define dll_export __declspec(dllexport)
#endif

#ifdef __cplusplus
}
#endif