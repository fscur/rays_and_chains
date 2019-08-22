#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

inline f64 //
r_datetime_now();

dll_export inline i32 //
r_datetime_compare(r_datetime_t* a, r_datetime_t* b);

#ifdef __cplusplus
}
#endif