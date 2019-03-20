#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

dll_export i32 //
r_string_cmp(const char* str_a, const char* str_b);

dll_export i32 //
r_string_wcmp(const wchar_t* str_a, const wchar_t* str_b);

#ifdef __cplusplus
}
#endif