#include "engine/core/r_core_types.h"
#include "engine/diagnostics/r_logger.h"
#include <windows.h>

internal void //
r_logger_output_print_test(r_logger_t* this, const char* format) {
  OutputDebugStringA(format);
  // printf(format, this->test++);
}