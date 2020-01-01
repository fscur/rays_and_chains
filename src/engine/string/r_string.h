#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

dll_export size_t //
r_string_length_ansi(const char* string);

dll_export i32 //
r_string_compare_ansi(const char* str_a, const char* str_b);

dll_export i32 //
r_string_compare_wide(const wchar_t* str_a, const wchar_t* str_b);

dll_export void //
r_string_to_ansi(const wchar_t* wide_string, char* ansi_string, const size_t length);

dll_export void //
r_string_to_wide(const char* ansi_string, wchar_t* wide_string, const size_t length);

dll_export void //
r_string_copy_ansi(char* destination, const char* source);

dll_export void //
r_string_copy_wide(wchar_t* destination, const wchar_t* source);

dll_export void //
r_string_concat_ansi(char* destination, const char* source);

#ifdef __cplusplus
}
#endif