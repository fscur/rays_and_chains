#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_cmd_line_cmds_t {
  char app_name[SHORT_STRING_LENGTH];
  char log_filename[SHORT_STRING_LENGTH];
} r_cmd_line_cmds_t;

bool //
r_try_get_cmd_line(int* argc, char*** argv);

int r_try_parse_cmd_line(int argc, char** argv, r_cmd_line_cmds_t* cmd_line_cmds);

void r_free_cmd_line(char** argv);

#ifdef __cplusplus
}
#endif