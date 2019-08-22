#include <windows.h>
#include "engine/time/r_clock.h"

f64 r_clock_frequency_in_ms = -1;

void //
r_clock_init() {
  LARGE_INTEGER clock_frequency;
  QueryPerformanceFrequency(&clock_frequency);
  r_clock_frequency_in_ms = 1000.0 / clock_frequency.QuadPart;
}