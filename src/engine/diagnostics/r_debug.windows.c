#include <windows.h>
#include <stdio.h>
#include "engine/diagnostics/r_debug.h"

void //
r_debug_print(const char* format, ...) {
#if _DEBUG
  local char msg[1024] = {0};
  va_list vl;
  va_start(vl, format);
  vsprintf(msg, format, vl);
  va_end(vl);

  freopen(R_DEBUG_LOG_FILENAME, "a+", stdout);
  printf(msg);
  fclose(stdout);
#endif
}

void //
r_debug_print_test(r_debug_t* this, const char* format)
{
  printf("%d", 0);
}