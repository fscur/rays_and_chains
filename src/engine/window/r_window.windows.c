#include "r_window.c"

#ifndef UNICODE
#define UNICODE
#endif

#pragma comment(lib, "user32.lib")

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

    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));

    EndPaint(hwnd, &ps);
  }
    return 0;
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

wchar_t* //
r_window_get_class_name(r_window_type_e window_type) {
  switch (window_type) {
  case R_WINDOW_TYPE_TOOL:
    return L"R_WINDOW_TOOL";
  case R_WINDOW_TYPE_MODAL:
    return L"R_WINDOW_MODAL";
  default:
    return L"R_WINDOW_DEFAULT";
  }
}

r_window_t* //
r_window_create(r_window_desc_t* window_descriptor) {

  WNDCLASS wc = {0};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = __hInstance;
  wc.lpszClassName = r_window_get_class_name(window_descriptor->type);

  RegisterClass(&wc);

  HWND hwnd = CreateWindowEx(0,                        // Optional window styles.
                             wc.lpszClassName,         // Window class
                             window_descriptor->title, // Window text
                             WS_OVERLAPPEDWINDOW,      // Window style
                             // Size and position
                             CW_USEDEFAULT,
                             CW_USEDEFAULT,
                             window_descriptor->width,
                             window_descriptor->height,
                             NULL,        // Parent window
                             NULL,        // Menu
                             __hInstance, // Instance handle
                             NULL         // Additional application data
  );
  if (hwnd == NULL) {
    exit(1);
  }

  r_window_t* window = calloc(1, sizeof(r_window_t));
  window->handle = hwnd;
  RECT rect;
  GetWindowRect(hwnd, &rect);

  window->width = rect.right - rect.left;
  window->height = rect.top - rect.bottom;
  window->should_close = false;
  r_string_copy_wide(window_descriptor->title, window->title);
  return window;
}

void //
r_window_show(r_window_t* window) {
  ShowWindow((HWND)window->handle, __nShowCmd);
}

void //
r_window_process_input(r_window_t* window) {
  MSG msg;

  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
    if (msg.message == WM_QUIT) {
      window->should_close = true;
      return;
    }

    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}