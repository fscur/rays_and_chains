#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define MAX(x, y) ((x) >= (y) ? (x) : (y))

void* xrealloc(void* addr, size_t new_size) {
  void* addr = realloc(addr, new_size);
  if (!addr) {
    perror("xrealloc failed");
    exit(1);
  }
  return addr;
}

void* xcalloc(size_t element_count, size_t element_size) {
  void* addr = calloc(element_count, element_size);
  if (!addr) {
    perror("xcalloc failed");
    exit(1);
  }
  return addr;
}

typedef struct r_buffer_header {
  size_t length;
  size_t capacity;
  u8 buffer[0];
} r_buffer_header;

// clang-format off
#define r_buffer__header(b) ((r_buffer_header*)((u8*)b - offsetof(r_buffer_header, buffer)))
#define r_buffer__fits(b, n) (r_buffer_length(b) + (n) <= r_buffer_capacity(b))
#define r_buffer__grow(b, n) ((b) = r_buffer_grow((b), r_buffer_length(b) + (n), sizeof(*(b))))
#define r_buffer__fit(b, n) (r_buffer__fits(b, n) ? 0 : (r_buffer__grow(b, n)))

#define r_stretchy_buffer_length(b) ((b) ? r_buffer__header(b)->length : 0)
#define r_stretchy_buffer_capacity(b) ((b) ? r_buffer__header(b)->capacity : 0)
#define r_stretchy_buffer_push(b, x) (r_buffer__fit(b, 1), (b)[r_buffer_length(b)->length++] = (x))
#define r_stretchy_buffer_free(b) ((b) ? free(r_buffer__header(b)), (b) = NULL : 0)
// clang-format on

internal void*
r_buffer_grow(const void* buffer, size_t new_length, size_t element_count) {
  size_t new_capacity = MAX(1 + 2 * r_stretchy_buffer_capacity(buffer), new_length);
  assert(new_length <= new_capacity);

  size_t new_size = offsetof(r_buffer_header, buffer) + new_capacity * element_count;
  r_buffer_header* new_header = NULL;

  if (buffer) {
    new_header = (r_buffer_header*)xrealloc(r_buffer__header(buffer), new_size);
  } else {
    new_header = (r_buffer_header*)xcalloc(1, new_size);
    new_header->length = 0;
  }

  new_header->capacity = new_capacity;
  return new_header->buffer;
}
#undef MAX
#ifdef __cplusplus
}
#endif
