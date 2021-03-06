#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

#include "engine/io/r_directory.h"

#pragma comment(lib, "user32.lib")

void //
r_directory_w_foreach_file(wchar_t* path, wchar_t* filter, void* callback, void* data) {

  WIN32_FIND_DATA ffd;
  HANDLE hFind = INVALID_HANDLE_VALUE;
  DWORD dwError = 0;
  LARGE_INTEGER filesize;
  wchar_t query[SHORT_STRING_LENGTH] = {0};
  wsprintf(query, L"%ls\\%ls", path, filter);

  hFind = FindFirstFile(query, &ffd);

  if (hFind == INVALID_HANDLE_VALUE) {
    // important: error
    return;
  }

  do {
    if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {

    } else {

      r_file_info_w_t file_info = {0};
      wsprintf(file_info.name, L"%ls", ffd.cFileName);
      wsprintf(file_info.full_name, L"%ls\\%ls", path, ffd.cFileName);
      filesize.HighPart = ffd.nFileSizeHigh;
      file_info.size = filesize.QuadPart;

      ((R_DIRECTORY_W_FOREACH_FILE_CALLBACK)callback)(file_info, (void*)data);
    }
  } while (FindNextFile(hFind, &ffd) != 0);

  dwError = GetLastError();
  if (dwError != ERROR_NO_MORE_FILES) {
    // important: error
  }

  FindClose(hFind);
}

void //
r_directory_a_foreach_file(char* path, char* filter, void* callback, void* data) {

  WIN32_FIND_DATAA ffd;
  HANDLE hFind = INVALID_HANDLE_VALUE;
  DWORD dwError = 0;
  LARGE_INTEGER filesize;
  char query[SHORT_STRING_LENGTH] = {0};
  sprintf(query, "%s\\%s", path, filter);

  hFind = FindFirstFileA(query, &ffd);

  if (hFind == INVALID_HANDLE_VALUE) {
    // important: error
    return;
  }

  do {
    if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {

    } else {

      r_file_info_a_t file_info = {0};
      sprintf(file_info.name, "%s", ffd.cFileName);
      sprintf(file_info.full_name, "%s\\%s", path, ffd.cFileName);
      filesize.HighPart = ffd.nFileSizeHigh;
      file_info.size = filesize.QuadPart;

      ((R_DIRECTORY_A_FOREACH_FILE_CALLBACK)callback)(file_info, (void*)data);
    }
  } while (FindNextFileA(hFind, &ffd) != 0);

  dwError = GetLastError();
  if (dwError != ERROR_NO_MORE_FILES) {
    // important: error
  }

  FindClose(hFind);
}