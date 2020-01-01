#pragma once
#ifdef __cplusplus
extern "C" {
#endif

// keywords
#if defined(WIN32)
#define dll_export __declspec(dllexport)
#endif

#define local static
#define internal static
#define global extern

// consts
#define R_MAX_LIB_COUNT 256
#define R_KEY_STRING_LENGTH 32
#define R_SHORT_STRING_LENGTH 256
#define R_LONG_STRING_LENGTH 1024
#define R_MAX_FUNCTION_COUNT 64

// functions
#if _DEBUG
#define assert(expression)                                                                         \
  if (!(expression)) {                                                                             \
    *(int*)0 = 0;                                                                                  \
  }
#else
#define assert(expression)
#endif

#define kilobytes(value) ((value)*1024LL)
#define megabytes(value) (kilobytes(value) * 1024LL)
#define gigabytes(value) (megabytes(value) * 1024LL)
#define terabytes(value) (gigabytes(value) * 1024LL)

#ifdef __cplusplus
}
#endif