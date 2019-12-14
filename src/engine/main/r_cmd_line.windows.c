#include <shellapi.h>
#include "engine/argtable/argtable3.c"

#include "r_cmd_line.h"

#pragma comment(lib, "shell32.lib")

/*************************************************************************
 * CommandLineToArgvA            [SHELL32.@]
 *
 * MODIFIED FROM https://www.winehq.org/ project
 * We must interpret the quotes in the command line to rebuild the argv
 * array correctly:
 * - arguments are separated by spaces or tabs
 * - quotes serve as optional argument delimiters
 *   '"a b"'   -> 'a b'
 * - escaped quotes must be converted back to '"'
 *   '\"'      -> '"'
 * - consecutive backslashes preceding a quote see their number halved with
 *   the remainder escaping the quote:
 *   2n   backslashes + quote -> n backslashes + quote as an argument delimiter
 *   2n+1 backslashes + quote -> n backslashes + literal quote
 * - backslashes that are not followed by a quote are copied literally:
 *   'a\b'     -> 'a\b'
 *   'a\\b'    -> 'a\\b'
 * - in quoted strings, consecutive quotes see their number divided by three
 *   with the remainder modulo 3 deciding whether to close the string or not.
 *   Note that the opening quote must be counted in the consecutive quotes,
 *   that's the (1+) below:
 *   (1+) 3n   quotes -> n quotes
 *   (1+) 3n+1 quotes -> n quotes plus closes the quoted string
 *   (1+) 3n+2 quotes -> n+1 quotes plus closes the quoted string
 * - in unquoted strings, the first quote opens the quoted string and the
 *   remaining consecutive quotes follow the above rule.
 */

LPSTR* WINAPI
CommandLineToArgvA(LPSTR lpCmdline, int* numargs) {
  DWORD argc;
  LPSTR* argv;
  LPSTR s;
  LPSTR d;
  LPSTR cmdline;
  int qcount, bcount;

  if (!numargs || *lpCmdline == 0) {
    SetLastError(ERROR_INVALID_PARAMETER);
    return NULL;
  }

  /* --- First count the arguments */
  argc = 1;
  s = lpCmdline;
  /* The first argument, the executable path, follows special rules */
  if (*s == '"') {
    /* The executable path ends at the next quote, no matter what */
    s++;
    while (*s)
      if (*s++ == '"')
        break;
  } else {
    /* The executable path ends at the next space, no matter what */
    while (*s && *s != ' ' && *s != '\t')
      s++;
  }
  /* skip to the first argument, if any */
  while (*s == ' ' || *s == '\t')
    s++;
  if (*s)
    argc++;

  /* Analyze the remaining arguments */
  qcount = bcount = 0;
  while (*s) {
    if ((*s == ' ' || *s == '\t') && qcount == 0) {
      /* skip to the next argument and count it if any */
      while (*s == ' ' || *s == '\t')
        s++;
      if (*s)
        argc++;
      bcount = 0;
    } else if (*s == '\\') {
      /* '\', count them */
      bcount++;
      s++;
    } else if (*s == '"') {
      /* '"' */
      if ((bcount & 1) == 0)
        qcount++; /* unescaped '"' */
      s++;
      bcount = 0;
      /* consecutive quotes, see comment in copying code below */
      while (*s == '"') {
        qcount++;
        s++;
      }
      qcount = qcount % 3;
      if (qcount == 2)
        qcount = 0;
    } else {
      /* a regular character */
      bcount = 0;
      s++;
    }
  }

  /* Allocate in a single lump, the string array, and the strings that go
   * with it. This way the caller can make a single LocalFree() call to free
   * both, as per MSDN.
   */
  argv =
      LocalAlloc(LMEM_FIXED, (argc + 1) * sizeof(LPSTR) + (strlen(lpCmdline) + 1) * sizeof(char));
  if (!argv)
    return NULL;
  cmdline = (LPSTR)(argv + argc + 1);
  strcpy(cmdline, lpCmdline);

  /* --- Then split and copy the arguments */
  argv[0] = d = cmdline;
  argc = 1;
  /* The first argument, the executable path, follows special rules */
  if (*d == '"') {
    /* The executable path ends at the next quote, no matter what */
    s = d + 1;
    while (*s) {
      if (*s == '"') {
        s++;
        break;
      }
      *d++ = *s++;
    }
  } else {
    /* The executable path ends at the next space, no matter what */
    while (*d && *d != ' ' && *d != '\t')
      d++;
    s = d;
    if (*s)
      s++;
  }
  /* close the executable path */
  *d++ = 0;
  /* skip to the first argument and initialize it if any */
  while (*s == ' ' || *s == '\t')
    s++;
  if (!*s) {
    /* There are no parameters so we are all done */
    argv[argc] = NULL;
    *numargs = argc;
    return argv;
  }

  /* Split and copy the remaining arguments */
  argv[argc++] = d;
  qcount = bcount = 0;
  while (*s) {
    if ((*s == ' ' || *s == '\t') && qcount == 0) {
      /* close the argument */
      *d++ = 0;
      bcount = 0;

      /* skip to the next one and initialize it if any */
      do {
        s++;
      } while (*s == ' ' || *s == '\t');
      if (*s)
        argv[argc++] = d;
    } else if (*s == '\\') {
      *d++ = *s++;
      bcount++;
    } else if (*s == '"') {
      if ((bcount & 1) == 0) {
        /* Preceded by an even number of '\', this is half that
         * number of '\', plus a quote which we erase.
         */
        d -= bcount / 2;
        qcount++;
      } else {
        /* Preceded by an odd number of '\', this is half that
         * number of '\' followed by a '"'
         */
        d = d - bcount / 2 - 1;
        *d++ = '"';
      }
      s++;
      bcount = 0;
      /* Now count the number of consecutive quotes. Note that qcount
       * already takes into account the opening quote if any, as well as
       * the quote that lead us here.
       */
      while (*s == '"') {
        if (++qcount == 3) {
          *d++ = '"';
          qcount = 0;
        }
        s++;
      }
      if (qcount == 2)
        qcount = 0;
    } else {
      /* a regular character */
      *d++ = *s++;
      bcount = 0;
    }
  }
  *d = '\0';
  argv[argc] = NULL;
  *numargs = argc;

  return argv;
}

bool //
r_try_get_cmd_line(int* argc, char*** argv) {

  *argv = CommandLineToArgvA(GetCommandLineA(), argc);

  if (*argv == NULL) {
    LocalFree(*argv);
    return false;
  }

  return true;
}

void
r_free_cmd_line(char** argv) {
  LocalFree(argv);
}

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

  struct arg_str* app_name =
      arg_strn(NULL, NULL, "<app_name>", 1, 1, "name of the application to run");

  struct arg_file* log_filename = arg_file0(NULL, "log", "<log_filename>", "log file path");

  struct arg_lit* help = arg_lit0("h", "help", "print this help and exit");
  struct arg_lit* version = arg_lit0("v", "version", "print version information and exit");

  struct arg_end* end = arg_end(2);
  void* argtable[] = {help, version, app_name, log_filename, end};
  int nerrors;
  int exitcode = 1;

  /* verify the argtable[] entries were allocated sucessfully */
  if (arg_nullcheck(argtable) != 0) {
    // important: maybe the cmd should use r_logger_log to log the errors?
    freopen(cmd_line_cmds->log_filename, "w", stdout);
    /* NULL entries were detected, some allocations must have failed */
    printf("%s: insufficient memory\n", prog_name);
    fclose(stdout);
    exitcode = 0;
    goto exit;
  }

  /* Parse the command line as defined by argtable[] */
  nerrors = arg_parse(argc, argv, argtable);

  /* special case: '--help' takes precedence over error reporting */
  if (help->count > 0) {
    freopen(cmd_line_cmds->log_filename, "w", stdout);
    print_help(prog_name, argtable);
    fclose(stdout);
    exitcode = 0;
    goto exit;
  }

  /* special case: '--version' takes precedence error reporting */
  if (version->count > 0) {
    freopen(cmd_line_cmds->log_filename, "w", stdout);
    printf("%s version %s", prog_name, prog_version);
    fclose(stdout);
    exitcode = 0;
    goto exit;
  }

  /* If the parser returned any errors then display them and exit */
  if (nerrors > 0) {
    freopen(cmd_line_cmds->log_filename, "w", stdout);
    /* Display the error details contained in the arg_end struct.*/
    arg_print_errors(stdout, end, prog_name);
    printf("Try '%s --help' for more information.\n", prog_name);
    fclose(stdout);
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