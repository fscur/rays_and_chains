#include <windows.h>
#include <stdio.h>

#include "engine\core\r_core_types.h"
#include "engine\diagnostics\r_logger_device_i.h"
#include "engine\diagnostics\r_logger_i.h"
#include "engine\diagnostics\r_logger.h"
#include "engine\app\r_api_db_i.h"
#include "engine\app\r_api_db.h"
#include "r_logger_output.c"

internal void //
r_logger_output_debug(const char* msg) {
#if _DEBUG
  OutputDebugStringA(msg);
#endif
}

internal void //
r_logger_output_warn(const char* msg) {
  OutputDebugStringA(msg);
}

internal void //
r_logger_output_error(const char* msg) {
    OutputDebugStringA(msg);
}

void //
r_logger_output_init(r_logger_t* this, r_api_db_i* api_db) {
  local r_logger_device_i api;
  api.debug = &r_logger_output_debug;
  api.warn = &r_logger_output_warn;
  api.error = &r_logger_output_error;
  r_logger_i* logger_api = api_db->find_by_name(api_db->instance, R_LOGGER_API_NAME);
  logger_api->add_device(&api);
}