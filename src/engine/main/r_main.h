#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_app_info_t r_app_info_t;

typedef struct r_main_info_t {
  char app_filename[R_SHORT_STRING_LENGTH];
  char log_filename[R_SHORT_STRING_LENGTH];
} r_main_info_t;

void                                   //
r_main(r_main_info_t* main_info,       //
       R_RESULT_ON_SUCCESS on_success, //
       R_RESULT_ON_ERROR on_error);

#ifdef __cplusplus
}
#endif