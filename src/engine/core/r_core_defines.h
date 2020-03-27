#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#define local static
#define internal static
#define global extern

// keywords
#if defined(WIN32)
#include <windows.h>
#define R_LIBS_DIRECTORY ".\\libs"
#define R_LIBS_EXTENSION ".dll"
#define dll_export __declspec(dllexport)
global HINSTANCE __hInstance = 0;
global int __nShowCmd = 0;
#else
#define R_LIBS_DIRECTORY "./libs"
#define R_LIBS_EXTENSION ".so"
#define dll_export
#endif

// consts
#define R_MAX_LIB_COUNT 256
#define R_KEY_STRING_LENGTH 32
#define R_SHORT_STRING_LENGTH 256
#define R_LONG_STRING_LENGTH 1024
#define R_MAX_FUNCTION_COUNT 64

// functions
#if _DEBUG
#define assert(expression)                                                                                             \
  if (!(expression)) {                                                                                                 \
    *(int*)0 = 0;                                                                                                      \
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