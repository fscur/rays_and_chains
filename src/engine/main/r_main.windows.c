#include <windows.h>
#include <stdio.h>

#include "engine/diagnostics/r_debug.windows.c"
#include "engine/window/r_window.windows.c"
#include "engine/ui/r_ui.windows.c"
#include "engine/memory/r_memory.windows.c"
#include "engine/thread/r_thread.windows.c"
#include "engine/time/r_time.windows.c"
#include "engine/app/r_app.windows.c"
#include "engine/string/r_string.windows.c"
#include "engine/io/r_io.windows.c"
#include "engine/gfx/r_gfx.windows.c"
#include "engine/plugins/r_plugins.windows.c"
#include "engine/lib_loader/r_lib_loader.windows.c"
#include "engine/main/r_cmd_line.c"
#include "engine/main/r_main.c"
#include "engine/main/r_console.c"

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
  int argc = 0;
  char** argv = NULL;

  if (!r_try_get_cmd_line(&argc, &argv))
    return 1;

  r_cmd_line_cmds_t cmd_line_cmds = {0};
  r_string_a_copy(R_DEBUG_LOG_FILENAME, cmd_line_cmds.log_filename);

  if (!r_try_parse_cmd_line(argc, argv, &cmd_line_cmds))
    return 1;

  r_free_cmd_line(argv);

  r_main_info_t main_info = {0};
  r_string_a_copy(cmd_line_cmds.app_name, main_info.app_filename);
  r_string_a_cat(main_info.app_filename, ".dll");
  r_string_a_copy(cmd_line_cmds.log_filename, main_info.log_filename);

  // todo: if file does not exists then we must not change default filename
  r_string_a_copy(cmd_line_cmds.log_filename, R_DEBUG_LOG_FILENAME);

  r_main(&main_info, &on_success, &on_error);

  return 0;
}