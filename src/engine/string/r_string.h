#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

dll_export size_t //
r_string_len(const char* str);

dll_export i32 //
r_string_cmp(const char* str_a, const char* str_b);

dll_export i32 //
r_string_wcmp(const wchar_t* str_a, const wchar_t* str_b);

dll_export void //
r_string_to_ansi(const wchar_t* wide_string, char* ansi_string, const size_t length);

dll_export void //
r_string_to_wide(const char* ansi_string, wchar_t* wide_string, const size_t length);

// todo: refactor all these functions to have the dst as the first parameter

dll_export void //
r_string_a_copy(const char* src, char* dst);

dll_export void //
r_string_w_copy(const wchar_t* src, wchar_t* dst);

dll_export void //
r_string_a_cat(char* dst, const char* src);

#ifdef __cplusplus
}
#endif