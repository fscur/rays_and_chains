#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int CALLBACK
WinMain(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nShowCmd) {
  MessageBox(0, "ola", "oi", MB_OK | MB_ICONEXCLAMATION);
  return 0;
}