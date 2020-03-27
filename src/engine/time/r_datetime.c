#include "engine/time/r_datetime.h"

inline i32 //
r_datetime_compare(r_datetime_t* a, r_datetime_t* b) {
  if (a->year > b->year)
    return 1;
  else if (a->year < b->year)
    return -1;
  else if (a->month > b->month)
    return 1;
  else if (a->month < b->month)
    return -1;
  else if (a->day > b->day)
    return 1;
  else if (a->day < b->day)
    return -1;
  else if (a->hour > b->hour)
    return 1;
  else if (a->hour < b->hour)
    return -1;
  else if (a->minute > b->minute)
    return 1;
  else if (a->minute < b->minute)
    return -1;
  else if (a->second > b->second)
    return 1;
  else if (a->second < b->second)
    return -1;
  else if (a->milli_seconds > b->milli_seconds)
    return 1;
  else if (a->milli_seconds < b->milli_seconds)
    return -1;

  return 0;
}