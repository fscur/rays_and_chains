#include "engine/time/r_datetime.h"
#include "engine/time/r_clock.h"

f64 //
r_datetime_now_milliseconds(void) {
  assert(r_clock_frequency_in_ms > 0);
  LARGE_INTEGER counter;
  QueryPerformanceCounter(&counter);
  return counter.QuadPart * r_clock_frequency_in_ms;
}
