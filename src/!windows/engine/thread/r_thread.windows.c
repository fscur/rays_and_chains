#include "windows.h"
#include "engine/thread/r_thread.h"

#pragma comment(lib, "winmm.lib")

bool r_thread_sleep_is_granular = false;

void //
r_thread_set_sleep_granularity(i32 ms) {
  r_thread_sleep_is_granular = timeBeginPeriod(ms) == TIMERR_NOERROR;
}

void //
r_thread_sleep(i32 ms) {
  Sleep(ms);
}