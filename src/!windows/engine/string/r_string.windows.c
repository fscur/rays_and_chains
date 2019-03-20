#include <stdio.h>
#include <string.h>

#include "engine/string/r_string.h"

i32 r_string_cmp(const char* str_a, const char* str_b) {
  return strcmp(str_a, str_b);
}

i32 r_string_wcmp(const wchar_t* str_a, const wchar_t* str_b) {
  return wcscmp(str_a, str_b);
}