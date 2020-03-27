#include <windows.h>
#include <stdio.h>

#include "r_logger_file_device.h"

char R_LOGGER_FILE_DEVICE_FILENAME[R_LONG_STRING_LENGTH] = "./log.log";
FILE* log_file = NULL;

void //
r_logger_file_open() {
  log_file = fopen(R_LOGGER_FILE_DEVICE_FILENAME, "a+");
}

void //
r_logger_file_close() {
  fclose(log_file);
}

void //
r_logger_file_device_print(const char* msg) {
  assert(R_LOGGER_FILE_DEVICE_FILENAME[0] != 0 && log_file);
  fprintf(log_file, msg);
}

void //
r_logger_file_device_set_filename(const char* msg) {
  sprintf(R_LOGGER_FILE_DEVICE_FILENAME, "%s", msg);
}