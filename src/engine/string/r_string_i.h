#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_STRING_API_ID 3
#define R_STRING_API_NAME "r_string"

typedef void (*R_STRING_TO_ANSI)(const wchar_t* wide_string, char* ansi_string, size_t length);
typedef void (*R_STRING_COPY_WIDE)(wchar_t* destination, const wchar_t* source);
typedef void (*R_STRING_COPY_ANSI)(char* destination, const char* source);

typedef struct r_string_i {
  // converts wide string to ansi
  R_STRING_TO_ANSI to_ansi;
  R_STRING_COPY_WIDE copy_wide;
  R_STRING_COPY_ANSI copy_ansi;
} r_string_i;

#ifdef __cplusplus
}
#endif

char* strcpy(char* dest, const char* src);