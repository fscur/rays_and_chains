#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_api_db_i r_api_db_i;
typedef struct r_frame_info_t r_frame_info_t;

typedef struct r_app_i {
  r_app_info_t (*get_app_info)();
  void (*init)(void* state, r_api_db_i* api_db);
  void (*run)(void* state, r_frame_info_t* frame_info);
  void (*destroy)(void* state);
} r_app_i;

#ifdef __cplusplus
}
#endif