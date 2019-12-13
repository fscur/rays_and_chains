#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_api_db_t r_api_db_t;
typedef struct r_frame_info_t r_frame_info_t;

typedef r_app_info_t (*R_APP_GET_APP_INFO)();
typedef void (*R_APP_INIT)(void* state, r_api_db_i* api_db);
typedef void (*R_APP_RUN)(void* state, r_frame_info_t* frame_info);
typedef void (*R_APP_DESTROY)(void* state);

typedef struct r_app_i {
  R_APP_GET_APP_INFO get_app_info;
  R_APP_INIT init;
  R_APP_RUN run;
  R_APP_DESTROY destroy;
} r_app_i;

#ifdef __cplusplus
}
#endif