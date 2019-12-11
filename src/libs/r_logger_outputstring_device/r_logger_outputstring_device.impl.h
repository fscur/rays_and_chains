#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

internal void //
r_logger_outputstring_device_debug(const char* msg);

internal void //
r_logger_outputstring_device_warn(const char* msg);

internal void //
r_logger_outputstring_device_error(const char* msg);

#ifdef __cplusplus
}
#endif