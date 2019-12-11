#include <windows.h>
#include <stdio.h>

#include "r_logger_outputstring_device.impl.h"

void //
r_logger_outputstring_device_debug(const char* msg) {
#if _DEBUG
  OutputDebugStringA(msg);
#endif
}

void //
r_logger_outputstring_device_warn(const char* msg) {
#if _DEBUG
  OutputDebugStringA(msg);
#endif _DEBUG
}

void //
r_logger_outputstring_device_error(const char* msg) {
#if _DEBUG
  OutputDebugStringA(msg);
#endif _DEBUG
}