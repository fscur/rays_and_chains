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

inline i32 //
r_time_compare(r_time_t* a, r_time_t* b) {
  FILETIME ft_a;
  FILETIME ft_b;

  SystemTimeToFileTime((SYSTEMTIME*)a, &ft_a);
  SystemTimeToFileTime((SYSTEMTIME*)b, &ft_b);
  long r = (CompareFileTime(&ft_a, &ft_b));
  return (i32)r;
}