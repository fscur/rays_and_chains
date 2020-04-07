#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_STRING_API_NAME "r_string"

typedef struct r_string_i {
  // Converts wide string to ansi.
  void (*to_ansi)(const wchar_t* wide_string, char* ansi_string, size_t length);
  // Copy wide strings.
  void (*copy_wide)(wchar_t* destination, const wchar_t* source);
  // Copy ansi strings.
  void (*copy_ansi)(char* destination, const char* source);
} r_string_i;

void //
r_string_register_api(r_api_db_t* api_db, r_memory_arena_t* apis_arena);

#ifdef __cplusplus
}
#endif

char* strcpy(char* dest, const char* src);