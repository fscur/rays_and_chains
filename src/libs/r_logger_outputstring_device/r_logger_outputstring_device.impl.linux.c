#include <stdio.h>

#include "r_logger_outputstring_device.impl.h"

void //
r_logger_outputstring_device_print(const char* msg) {
#if _DEBUG
  printf("%s", msg);
#endif
}