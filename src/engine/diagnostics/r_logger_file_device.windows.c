#include <windows.h>
#include <stdio.h>

#include "r_logger_file_device.h"

void //
r_logger_file_device_print(const char* msg) {  
  assert(R_LOGGER_FILE_DEVICE_FILE_NAME[0] != 0);
  freopen(R_LOGGER_FILE_DEVICE_FILE_NAME, "a+", stdout);
  printf(msg);
  fclose(stdout);
}

void //
r_logger_file_device_set_filename(const char* msg)
{
  sprintf(R_LOGGER_FILE_DEVICE_FILE_NAME, "%s", msg);
}