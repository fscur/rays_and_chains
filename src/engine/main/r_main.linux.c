#include "engine/string/r_string.linux.c"
#include "engine/main/r_cmd_line.linux.c"
#include "engine/logger/r_logger.linux.c"
#include "engine/time/r_time.linux.c"
#include "engine/thread/r_thread.linux.c"
#include "engine/memory/r_memory.linux.c"
#include "engine/algorithms/r_murmur3.c"
#include "engine/collections/r_hashtable.c"
#include "engine/io/r_io.linux.c"
#include "engine/lib_loader/r_lib_loader.linux.c"
#include "engine/app/r_api_db.c"
#include "engine/app/r_app.linux.c"

#include "engine/window/r_window.linux.c"
// #include "engine/ui/r_ui.windows.c"
// #include "engine/gfx/r_gfx.windows.c"

#include "engine/main/r_main.c"

void
on_success(r_success_t* success) {
  r_logger_debug("All good.");
}

void
on_error(r_error_t* error) {
  r_logger_debug("No good.");
}

// void
// redirect_stdout() {
//   char name[256];
//   int pid = GetCurrentProcessId();
//   sprintf(name, "\\\\.\\pipe\\cout%d", pid);
//   freopen(name, "a", stdout);
// }


int
main(int argc, char** argv) {

    // if (strcmp(argv[argc - 1], "launcher") == 0) {
    //   redirect_stdout();
    //   argc--;
    // }

    r_cmd_line_cmds_t cmd_line_cmds = {0};
    r_string_copy_ansi(cmd_line_cmds.log_filename, R_LOGGER_FILE_DEVICE_FILENAME);

    if (!r_try_parse_cmd_line(argc, argv, &cmd_line_cmds))
      return 1;

  #if _DEBUG
    // if (cmd_line_cmds.show_attach_msg) {
    //   MessageBoxA(NULL, "attach", "attach", MB_OK);
    // }
  #endif

    r_main_info_t main_info = {0};
    r_string_copy_ansi(main_info.app_filename, cmd_line_cmds.app_name);
    r_string_concat_ansi(main_info.app_filename, ".so");
    r_string_copy_ansi(main_info.log_filename, cmd_line_cmds.log_filename);

    r_main(&main_info, &on_success, &on_error);

    return 0;
}

// #include "engine/io/r_io.linux.c"
// #include "engine/time/r_time.linux.c"
// #include "engine/algorithms/r_murmur3.c"
// #include "engine/string/r_string.linux.c"
// #include "engine/collections/r_hashtable.c"
// #include "engine/app/r_api_db.h"
// #include "engine/app/r_api_db.c"
// #include "engine/app/r_app_host.c"

// int
// main(int argc, char** argv) {
//   r_app_host_get_size();
//   r_api_db_t* db = r_api_db_create();
//   r_api_db_add(db, "filipe", NULL);
// }