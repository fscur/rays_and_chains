#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "engine/string/r_string.h"

#pragma comment(lib, "user32.lib")

i32
r_string_cmp(const char* str_a, const char* str_b) {
  return strcmp(str_a, str_b);
}

i32
r_string_wcmp(const wchar_t* str_a, const wchar_t* str_b) {
  return wcscmp(str_a, str_b);
}

void //
r_string_to_ansi(const wchar_t* wide_string, char* ansi_string, const size_t length) {
  wcstombs(ansi_string, wide_string, length);
}

void //
r_string_to_wide(const char* ansi_string, wchar_t* wide_string, const size_t length) {
  mbstowcs(wide_string, ansi_string, length);
}

void //
r_string_a_copy(const char* src, char* dst) {
  sprintf(dst, src);
}

void //
r_string_w_copy(const wchar_t* src, wchar_t* dst) {
  wsprintf(dst, src);
}

void //
r_string_a_cat(char* dst, const char* src) {
  strcat(dst, src);
}