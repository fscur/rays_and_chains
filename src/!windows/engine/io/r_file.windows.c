#include <windows.h>
#include "engine/io/r_file.h"

bool //
r_file_a_copy(char* src, char* dst) {
  return CopyFileA(src, dst, false);
}