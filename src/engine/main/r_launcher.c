#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <stdbool.h>

HANDLE coutPipe, cinPipe, cerrPipe;
#define CONNECTIMEOUT 1000

BOOL
CreateNamedPipes(DWORD pid) {
  char name[256];
  sprintf(name, "\\\\.\\pipe\\cout%d", pid);
  // swprintf(name, 256, L"\\\\.\\pipe\\%dcout", pid);

  coutPipe = CreateNamedPipeA(name,
                              PIPE_ACCESS_INBOUND,
                              PIPE_TYPE_BYTE | PIPE_READMODE_BYTE,
                              1,
                              1024,
                              1024,
                              CONNECTIMEOUT,
                              NULL);

  if (coutPipe == INVALID_HANDLE_VALUE) {
    return 0;
  }

  return 1;
}

// Close all named pipes
void
CloseNamedPipes() {
  Sleep(100);
  CloseHandle(coutPipe);
}

void
OutPipeTh(void* test) {
  char buffer[1024] = {0};
  DWORD count = 0;

  ConnectNamedPipe(coutPipe, NULL);

  while (ReadFile(coutPipe, // pipe handle
                  buffer,   // buffer to receive reply
                  1024,     // size of buffer
                  &count,   // number of bytes read
                  NULL)) {
    buffer[count] = 0;
    printf(buffer);
    fflush(stdout);
  }
}

void
RunPipeThreads() {
  _beginthread(OutPipeTh, 0, NULL);
}

int
main(int argc, char argv[]) {

  wchar_t cLine[2048] = {0};
  wchar_t module_name[MAX_PATH + 1] = {0};
  GetModuleFileName(0, module_name, MAX_PATH);
  module_name[MAX_PATH] = 0;
  module_name[wcslen(module_name) - 4] = 0;

  wchar_t cArgs[2048] = {0};
  wchar_t cArgsClean[2048] = L"";
  wcsncpy_s(cArgs, 2048, GetCommandLine(), 2047);

  // Find where to cut out the program name (which may be quoted)
  int offset = 0;
  wchar_t* ptr = cArgs;

  bool inQuote = false;

  if (cArgs[0] == '\"') {
    inQuote = true;
    offset++;
    ptr++;
  }
  while (*ptr) {
    offset++;
    if (inQuote && *ptr == '\"') {
      offset++;
      break;
    }
    if (!inQuote && *ptr == ' ')
      break;

    ptr++;
  }

  wcsncpy_s(cArgsClean, 2048, cArgs + offset, 2047);
  swprintf(cLine, 2048, L"r_engine.exe %s launcher", cArgsClean);

  PROCESS_INFORMATION pInfo = {0};
  STARTUPINFO sInfo = {0};
  sInfo.cb = sizeof(STARTUPINFO);

  if (!CreateProcess(
          NULL, cLine, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &sInfo, &pInfo)) {
    fprintf(stderr, "ERROR: Could not create process.");
    return 1;
  }

  if (!CreateNamedPipes(pInfo.dwProcessId)) {
    fprintf(stderr, "ERROR: Could not create named pipes.");
    return 1;
  }

  RunPipeThreads();

  // resume process
  ResumeThread(pInfo.hThread);

  WaitForSingleObject(pInfo.hProcess, INFINITE);

  CloseNamedPipes();

  ULONG exitCode;

  GetExitCodeProcess(pInfo.hProcess, (ULONG*)&exitCode);

  return exitCode;
}
