#include "engine/io/r_file.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct r_datetime_t r_datetime_t;

bool //
r_file_a_copy(const char* src_file_name, const char* dst_file_name) {
  // return CopyFileA(src_file_name, dst_file_name, false);
  return true;
}

bool //
r_file_a_get_last_modification(const char* file_name, r_datetime_t* time) {
  // WIN32_FIND_DATAA ffd;
  // HANDLE hFind = INVALID_HANDLE_VALUE;
  // hFind = FindFirstFileA(file_name, &ffd);

  // if (hFind == INVALID_HANDLE_VALUE)
  //   return false;

  // FileTimeToSystemTime(&ffd.ftLastWriteTime, (SYSTEMTIME*)time);
  // FindClose(hFind);
  // return true;
  return true;
}