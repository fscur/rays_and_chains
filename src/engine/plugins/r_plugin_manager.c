#include "engine/core/r_core_types.h"
#include "engine/memory/r_memory.h"
#include "r_plugin_manager.h"

struct r_memory_arena;

r_plugin_manager_state_t* //
r_plugin_manager_create(r_memory_t* memory) {
  assert(sizeof(r_plugin_manager_state_t) <= memory->permanent_size);

  r_memory_arena_t* arena = (r_memory_arena_t*)memory->permanent_addr;
  r_memory_arena_init(arena, memory->permanent_addr, memory->permanent_size);
  R_MEMORY_ARENA_PUSH_STRUCT(arena, r_memory_arena_t);

  r_plugin_manager_state_t* state = R_MEMORY_ARENA_PUSH_STRUCT(arena, r_plugin_manager_state_t);
  state->memory_arena = arena;
  return state;
}

void //
r_plugin_manager_add(r_plugin_manager_state_t* state,
                     char* file_name,
                     void* plugin_handle,
                     size_t memory_size) {
  u8 index = state->plugin_count++;
  state->plugins[index].file_name = file_name;
  state->plugins[index].handle = plugin_handle;
  state->plugins[index].state_addr = state->memory_arena->current_addr;
  state->plugins[index].memory_size = memory_size;
}

void //
r_plugin_manager_remove(r_plugin_manager_state_t* state, void* api) {}

void* //
r_plugin_manager_find(r_plugin_manager_state_t* state, char* file_name) {
  return NULL;
}