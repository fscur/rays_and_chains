#include <windows.h>
#include <stdio.h>

#include "engine\core\r_core_types.h"
#include "engine\diagnostics\r_logger_device_i.h"
#include "engine\diagnostics\r_logger_i.h"
#include "engine\diagnostics\r_logger.h"
#include "engine\app\r_api_db_i.h"
#include "engine\app\r_api_db.h"
#include "r_logger_outputstring_device.c"

internal void //
r_logger_outputstring_device_debug(const char* msg) {
#if _DEBUG
  OutputDebugStringA(msg);
#endif
}

internal void //
r_logger_outputstring_device_warn(const char* msg) {
  OutputDebugStringA(msg);
}

internal void //
r_logger_outputstring_device_error(const char* msg) {
  OutputDebugStringA(msg);
}

void //
r_logger_outputstring_device_init(r_logger_t* this, r_api_db_i* api_db) {
  local r_logger_device_i api;
  api.debug = &r_logger_outputstring_device_debug;
  api.warn = &r_logger_outputstring_device_warn;
  api.error = &r_logger_outputstring_device_error;
  api_db->add(
      api_db->instance, 
      R_LOGGER_OUTPUTSTRING_DEVICE_API_ID, 
      R_LOGGER_OUTPUTSTRING_DEVICE_API_NAME,
      &api);
}