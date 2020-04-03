#include "r_hashtable.h"
#include "engine/algorithms/r_murmur3.h"
#include "engine/string/r_string.h"

typedef struct r_hashtable_item_t {
  char key[R_HASHTABLE_MAX_KEY_LENGTH];
  void* data;
  struct r_hashtable_item_t* next;
} r_hashtable_item_t;

typedef struct r_hashtable_t {
  r_hashtable_item_t* items[R_HASHTABLE_MAX_ITEMS];
} r_hashtable_t;

r_hashtable_t* //
r_hashtable_create() {
  return calloc(1, sizeof(r_hashtable_t));
}

void //
r_hashtable_add(r_hashtable_t* hashtable, const char* key, void* data) {
  assert(r_string_length_ansi(key) < R_HASHTABLE_MAX_KEY_LENGTH);

  u32 index =
      r_murmur3_32(key, r_string_length_ansi(key), R_HASHTABLE_SEED) % R_HASHTABLE_MAX_ITEMS;

  r_hashtable_item_t* item = calloc(1, sizeof(r_hashtable_item_t));
  item->data = data;
  r_string_copy_ansi(item->key, key);

  r_hashtable_item_t* current = hashtable->items[index];

  if (current == NULL) {
    hashtable->items[index] = item;
  } else {
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = item;
  }
}

void* //
r_hashtable_find(r_hashtable_t* hashtable, const char* key) {
  u32 index =
      r_murmur3_32(key, r_string_length_ansi(key), R_HASHTABLE_SEED) % R_HASHTABLE_MAX_ITEMS;

  if (hashtable->items[index]->next == NULL) {
    return hashtable->items[index]->data;
  }

  r_hashtable_item_t* current = hashtable->items[index];

  // todo: filipe.scur@gmail.com | 1/1/2020
  //implement string interning to perform fast string comparisons

  while (r_string_compare_ansi(key, current->key) != 0) {
    current = current->next;

    if (current == NULL)
      return NULL;
  }

  return current->data;
}

void //
r_hashtable_remove(r_hashtable_t* hashtable, const char* key) {
  u32 index =
      r_murmur3_32(key, r_string_length_ansi(key), R_HASHTABLE_SEED) % R_HASHTABLE_MAX_ITEMS;

  if (hashtable->items[index] == NULL) {
    return;
  }

  r_hashtable_item_t* previous = NULL;
  r_hashtable_item_t* current = hashtable->items[index];
  r_hashtable_item_t* next = current->next;

  while (r_string_compare_ansi(key, current->key) != 0) {
    previous = current;
    current = current->next;
    next = current->next;

    if (current == NULL)
      return;
  }

  if (previous == NULL) { // first element
    hashtable->items[index] = next;
  } else if (next == NULL) { // last element
    previous->next = NULL;
  } else { // all others in between
    previous->next = next;
  }

  free(current);
}

void //
r_hashtable_destroy(r_hashtable_t* hashtable) {
  for (size_t i = 0; i < R_HASHTABLE_MAX_ITEMS; i++) {
    r_hashtable_item_t* current = hashtable->items[i];

    if (current == NULL)
      continue;

    r_hashtable_item_t* next = current->next;

    while (next != NULL) {
      free(current);
      current = next;
      next = current->next;
    }
    free(current);
  }
  free(hashtable);
}