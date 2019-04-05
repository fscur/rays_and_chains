#include <windows.h>
#include <stdio.h>

#include "!windows/engine/diagnostics/r_debug.windows.c"
#include "!windows/engine/window/r_window.windows.c"
#include "!windows/engine/memory/r_memory.windows.c"
#include "!windows/engine/thread/r_thread.windows.c"
#include "!windows/engine/time/r_time.windows.c"
#include "!windows/engine/app/r_app.windows.c"
#include "!windows/engine/plugins/r_plugins.windows.c"
#include "!windows/engine/lib_loader/r_lib_loader.windows.c"
#include "engine/main/r_main.c"

void
on_success(r_success_t* success) {
  r_debug_print("All good.");
}

void
on_error(r_error_t* error) {
  r_debug_print("No good.");
}

int CALLBACK
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

  //todo: parse cmd line and fill main_info
  r_main_info_t main_info = {
    .app_filename = "sandbox.dll" 
  };
  
  r_main(&main_info, &on_success, &on_error);

  return 0;
}