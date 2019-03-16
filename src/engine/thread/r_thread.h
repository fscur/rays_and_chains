#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

global bool r_thread_sleep_is_granular; 

void //
r_thread_set_sleep_granularity(i32 ms);

inline void //
r_thread_sleep(i32 ms);

#ifdef __cplusplus
}
#endif