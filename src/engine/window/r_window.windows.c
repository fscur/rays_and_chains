#include "r_window.c"
#include "r_window.windows.h"

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK
WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;

  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

    EndPaint(hwnd, &ps);
  }
    return 0;
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

r_window_t* //
r_window_create() {
  wchar_t* lpWindowName = L"New window";

  WNDCLASS wc = {0};

  wc.lpfnWndProc = WindowProc;
  wc.hInstance = __hInstance;
  wc.lpszClassName = L"R_WINDOW_MAIN_WINDOW";

  RegisterClass(&wc);

  HWND hwnd = CreateWindowEx(0,                   // Optional window styles.
                             wc.lpszClassName,         // Window class
                             lpWindowName,        // Window text
                             WS_OVERLAPPEDWINDOW, // Window style

                             // Size and position
                             CW_USEDEFAULT,
                             CW_USEDEFAULT,
                             CW_USEDEFAULT,
                             CW_USEDEFAULT,

                             NULL,        // Parent window
                             NULL,        // Menu
                             __hInstance, // Instance handle
                             NULL         // Additional application data
  );
  if (hwnd == NULL)
  {
    exit(1);
  }
  
  r_window_t* window = calloc(1, sizeof(r_window_t));
  window->handle = hwnd;
  RECT rect;
  GetWindowRect(hwnd, &rect);

  window->width = rect.right - rect.left;
  window->height = rect.top - rect.bottom;
  window->should_close = false;
  r_string_w_copy((wchar_t*)lpWindowName, window->title);
  return window;
}

void //
r_window_show(r_window_t* window) {
  ShowWindow((HWND)window->handle, __nShowCmd);
}
