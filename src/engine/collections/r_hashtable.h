#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_HASHTABLE_MAX_ITEMS 1024
#define R_HASHTABLE_MAX_KEY_LENGTH R_KEY_STRING_LENGTH
#define R_HASHTABLE_SEED 42

typedef struct r_hashtable_t r_hashtable_t;

dll_export r_hashtable_t* //
r_hashtable_create();

dll_export void //
r_hashtable_add(r_hashtable_t* hashtable, const char* key, void* data);

dll_export void* //
r_hashtable_find(r_hashtable_t* hashtable, const char* key);

dll_export void //
r_hashtable_remove(r_hashtable_t* hashtable, const char* key);

dll_export void //
r_hashtable_destroy(r_hashtable_t* hashtable);

#ifdef __cplusplus
}
#endif