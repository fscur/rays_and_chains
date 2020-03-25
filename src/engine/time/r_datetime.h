#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_datetime_t {
  i16 year;
  i16 month;
  i16 day_of_week;
  i16 day;
  i16 hour;
  i16 minute;
  i16 second;
  i16 milli_seconds;
} r_datetime_t;

f64 //
r_datetime_now_milliseconds();

i32 //
r_datetime_compare(r_datetime_t* a, r_datetime_t* b);

#ifdef __cplusplus
}
#endif