#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "engine/string/r_string.h"

i32
r_string_cmp(const char* str_a, const char* str_b) {
  return strcmp(str_a, str_b);
}

i32
r_string_wcmp(const wchar_t* str_a, const wchar_t* str_b) {
  return wcscmp(str_a, str_b);
}

void //
r_string_to_ansi(wchar_t* wide_string, char* ansi_string, size_t length) {
  wcstombs(ansi_string, wide_string, length);
}

void //
r_string_to_wide(char* ansi_string, wchar_t* wide_string, size_t length) {
  mbstowcs(wide_string, ansi_string, length);
}