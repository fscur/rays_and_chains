#include "r_api_db.h"

internal void
dfs(u32 start_index,
    u32 G[MAX_PLUGIN_APIS][MAX_PLUGIN_APIS],
    u32 ordered_indices[MAX_PLUGIN_APIS],
    u32* current_index,
    u32 visited[MAX_PLUGIN_APIS]) {
  visited[start_index] = 1;

  for (u32 i = 0; i < MAX_PLUGIN_APIS; ++i) {
    if (i == start_index)
      continue;
    if (!visited[i] && G[start_index][i])
      dfs(i, G, ordered_indices, current_index, visited);
  }
  u32 index = MAX_PLUGIN_APIS - 1 - (*current_index)++;
  ordered_indices[index] = start_index;
}

internal void //
get_dependency_order(u32 start_index,
                     u32 G[MAX_PLUGIN_APIS][MAX_PLUGIN_APIS],
                     u32* ordered_indices,
                     u32* count) {
  u32 current_index = start_index;
  u32 visited[MAX_PLUGIN_APIS] = {0};

  for (u32 i = start_index; i < MAX_PLUGIN_APIS; ++i) {
    if (!visited[i])
      dfs(start_index, G, ordered_indices, &current_index, visited);
  }
  // todo: we have to set the max = count of plugins added????
  *count = MAX_PLUGIN_APIS - 1 - current_index;
}

void //
r_api_db_get_dependency_reload_order(r_api_db_t* this,
                                     const u32 api_id,
                                     u32* ordered_api_ids,
                                     u32* count) {
  get_dependency_order(api_id - MAX_PLUGIN_APIS, this->dependency_graph, ordered_api_ids, count);
}

void* //
r_api_db_find_api(r_api_db_t* this, const u32 api_id, const u32 dependent_id) {
  assert(api_id != dependent_id);
  // todo: (filipe.scur) prevent cycle
  if (api_id >= MAX_PLUGIN_APIS)
    this->dependency_graph[api_id - MAX_PLUGIN_APIS][dependent_id - MAX_PLUGIN_APIS] = 1;

  return this->apis[api_id];
}