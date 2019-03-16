#include <windows.h>
#include "engine/time/r_time.h"

f64 r_time_clock_frequency_in_ms = -1;

void //
r_time_init_clock_frequency() {
  LARGE_INTEGER clock_frequency;
  QueryPerformanceFrequency(&clock_frequency);
  r_time_clock_frequency_in_ms = 1000.0 / clock_frequency.QuadPart;
}

f64 //
r_time_now() {
  assert(r_time_clock_frequency_in_ms > 0);
  LARGE_INTEGER counter;
  QueryPerformanceCounter(&counter);
  return counter.QuadPart * r_time_clock_frequency_in_ms;
}