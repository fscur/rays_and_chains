#include <time.h>
#include "r_datetime.h"
#include "r_clock.h"
#include "r_datetime.c"

typedef struct timeb Timespan;
typedef struct timespec Time_Spec;

f64 //
r_datetime_now_milliseconds(void) {
  struct timespec now;
  clock_gettime(CLOCK_MONOTONIC, &now);
  return now.tv_sec * 1000 + now.tv_nsec / 1000000.0;
}
