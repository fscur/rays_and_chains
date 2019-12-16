#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

uint32_t //
r_murmur3_32(const char* key, size_t len, uint32_t seed);

#ifdef __cplusplus
}
#endif