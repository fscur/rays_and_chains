#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

dll_export i32 //
r_string_cmp(const char* str_a, const char* str_b);

dll_export i32 //
r_string_wcmp(const wchar_t* str_a, const wchar_t* str_b);

dll_export void //
r_string_to_ansi(wchar_t* wide_string, char* ansi_string, size_t length);

dll_export void //
r_string_to_wide(char* ansi_string, wchar_t* wide_string, size_t length);

#ifdef __cplusplus
}
#endif