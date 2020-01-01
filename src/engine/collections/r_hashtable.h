#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_HASHTABLE_MAX_ITEMS 1024
#define R_HASHTABLE_MAX_KEY_LENGTH 32
#define R_HASHTABLE_SEED 42

typedef struct r_hashtable_t r_hashtable_t;

dll_export void //
r_hashtable_add(r_hashtable_t* hashtable, char* key, void* data);

dll_export void* //
r_hashtable_find(r_hashtable_t* hashtable, char* key);

dll_export void //
r_hashtable_remove(r_hashtable_t* hashtable, char* key);

#ifdef __cplusplus
}
#endif