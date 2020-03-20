#include "engine/argtable/argtable3.c"
#include "r_cmd_line.h"

void
print_help(const char* prog_name, void** argtable) {
  printf("Usage: %s", prog_name);
  arg_print_syntaxv(stdout, argtable, "\n");
  printf("\n%s\n\n", PROG_DESCRIPTION);
  arg_print_glossary(stdout, argtable, "  %-10s %s\n");
  printf("\nPlease, report bugs to <filipe.scur@gmail.com>.\n");
}

int
r_try_parse_cmd_line(int argc, char** argv, r_cmd_line_cmds_t* cmd_line_cmds) {

  const char* prog_name = PROG_NAME;
  const char* prog_version = PROG_VERSION;

  struct arg_lit* attach = arg_lit0("a", "attach", "\t\tdisplay a message box at the start");

  struct arg_str* app_name =
      arg_strn(NULL, NULL, "<app_name>", 1, 1, "\t\tname of the application to run");

  struct arg_file* log_filename = arg_file0(NULL, "log", "<filename>", "\tlog file path");

  struct arg_lit* help = arg_lit0("h", "help", "\t\tprint this help and exit");
  struct arg_lit* version = arg_lit0("v", "version", "\tprint version information and exit");

  struct arg_end* end = arg_end(2);

  void* argtable[] = {help, //
                      version,
                      attach,
                      app_name,
                      log_filename,
                      end};
  int nerrors;
  int exitcode = 1;

  /* verify the argtable[] entries were allocated sucessfully */
  if (arg_nullcheck(argtable) != 0) {
    // important: maybe the cmd should use r_logger_log to log the errors?
    /* NULL entries were detected, some allocations must have failed */
    printf("%s: insufficient memory\n", prog_name);
    fflush(stdout);
    exitcode = 0;
    goto exit;
  }

  /* Parse the command line as defined by argtable[] */
  nerrors = arg_parse(argc, argv, argtable);

  cmd_line_cmds->show_attach_msg = attach->count > 0;

  /* special case: '--help' takes precedence over error reporting */
  if (help->count > 0) {
    print_help(prog_name, argtable);
    fflush(stdout);
    exitcode = 0;
    goto exit;
  }

  /* special case: '--version' takes precedence error reporting */
  if (version->count > 0) {
    printf("%s version %s", prog_name, prog_version);
    fflush(stdout);
    exitcode = 0;
    goto exit;
  }

  /* If the parser returned any errors then display them and exit */
  if (nerrors > 0) {

    /* Display the error details contained in the arg_end struct.*/
    arg_print_errors(stdout, end, prog_name);
    printf("Try '%s --help' for more information.\n", prog_name);
    fflush(stdout);
    exitcode = 0;
    goto exit;
  }

  r_string_copy_ansi(cmd_line_cmds->app_name, app_name->sval[0]);

  if (log_filename->count > 0) {
    r_string_copy_ansi(cmd_line_cmds->log_filename, log_filename->filename[0]);
  }

exit:
  arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));

  return exitcode;
}