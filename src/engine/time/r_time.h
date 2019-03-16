#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

global f64 r_time_clock_frequency_in_ms;

typedef struct r_time_t {
  f64 desired_fps;
  f64 desired_ms_per_frame;
  f64 dt;
  f64 now;
  i64 frames;
} r_time_t;

inline void //
r_time_init_clock_frequency();

inline f64 //
r_time_now();

#ifdef __cplusplus
}
#endif