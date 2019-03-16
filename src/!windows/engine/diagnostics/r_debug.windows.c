#include "engine/diagnostics/r_debug.h"

void //
r_debug_print(const char* format, ...) {
#if _DEBUG
  local char msg[1024] = {0};
  va_list vl;
  va_start(vl, format);
  vsprintf(msg, format, vl);
  va_end(vl);
  OutputDebugStringA(msg);
#endif
}
