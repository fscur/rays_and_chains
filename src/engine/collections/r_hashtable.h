#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

i32 //
r_hashtable_add(void* data);

void* //
r_hashtable_get(i32 key);

#ifdef __cplusplus
}
#endif