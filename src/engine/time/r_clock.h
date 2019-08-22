#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

global f64 r_clock_frequency_in_ms;

inline void //
r_clock_init();

#ifdef __cplusplus
}
#endif