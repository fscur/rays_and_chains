#include <windows.h>
#include "engine/time/r_datetime.h"
#include "engine/time/r_clock.h"

f64 //
r_datetime_now(void) {
  assert(r_clock_frequency_in_ms > 0);
  LARGE_INTEGER counter;
  QueryPerformanceCounter(&counter);
  return counter.QuadPart * r_clock_frequency_in_ms;
}

inline i32 //
r_datetime_compare(r_datetime_t* a, r_datetime_t* b) {
  FILETIME ft_a;
  FILETIME ft_b;

  SystemTimeToFileTime((SYSTEMTIME*)a, &ft_a);
  SystemTimeToFileTime((SYSTEMTIME*)b, &ft_b);
  long r = (CompareFileTime(&ft_a, &ft_b));
  return (i32)r;
}