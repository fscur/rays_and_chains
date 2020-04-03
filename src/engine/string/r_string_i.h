#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_STRING_API_ID 3
#define R_STRING_API_NAME "r_string"

// note: filipe.scur@gmail.com | 3/31/2020
// not really sure about this typedef style pointer to functions in structs
// the thing is that its a bit too verbose and encapsulates too much the params of the functions
// ie. when you use the intelisense, it does not show you the parameters only its type
// that we just defined.. well lets see how it goes..

typedef void (*R_STRING_TO_ANSI)(const wchar_t* wide_string, char* ansi_string, size_t length);
typedef void (*R_STRING_COPY_WIDE)(wchar_t* destination, const wchar_t* source);
typedef void (*R_STRING_COPY_ANSI)(char* destination, const char* source);

typedef struct r_string_i {
  // void r_string::to_ansi(const wchar_t* wide_string, char* ansi_string, size_t length);
  // Converts wide string to ansi.
  R_STRING_TO_ANSI to_ansi;
  // void r_string::copy_wide(wchar_t* destination, const wchar_t* source);
  // Copy wide strings.
  R_STRING_COPY_WIDE copy_wide;
  // void r_string::copy_ansi(char* destination, const char* source);
  // Copy ansi strings.
  R_STRING_COPY_ANSI copy_ansi;
} r_string_i;

#ifdef __cplusplus
}
#endif

char* strcpy(char* dest, const char* src);