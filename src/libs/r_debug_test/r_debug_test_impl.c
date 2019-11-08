#include "engine/core/r_core_types.h"
#include "engine/diagnostics/r_debug.h"

internal void //
r_debug_test_print_test(r_debug_t* this, const char* format){  
  printf(format, this->test++);
}