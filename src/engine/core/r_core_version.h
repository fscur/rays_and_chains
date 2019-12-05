#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#define PROG_NAME "r_engine"
#if _DEBUG
#define PROG_VERSION "[dev]"
#define PROG_DESCRIPTION "Rays and chains engine. Development version."
#else
#define PROG_VERSION "0.0.0.1"
#define PROG_DESCRIPTION "Rays and chains engine."
#endif

#ifdef __cplusplus
}
#endif