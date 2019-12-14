#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "engine/string/r_string.h"

#pragma comment(lib, "user32.lib")

size_t //
r_string_length_ansi(const char* string) {
  return strlen(string);
}

i32 //
r_string_compare_ansi(const char* string_a, const char* string_b) {
  return strcmp(string_a, string_b);
}

i32 //
r_string_compare_wide(const wchar_t* string_a, const wchar_t* string_b) {
  return wcscmp(string_a, string_b);
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
r_string_copy_ansi(char* destination, const char* source) {
  sprintf(destination, source);
}

void //
r_string_copy_wide(wchar_t* destination, const wchar_t* source) {
  wsprintf(destination, source);
}

void //
r_string_concat_ansi(char* destination, const char* source) {
  strcat(destination, source);
}