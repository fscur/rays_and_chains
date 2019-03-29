#include <windows.h>
#include <stdio.h>

typedef unsigned char u8;
#define MAX_PLUGIN_APIS 5

// int
// dfs(int s, int t, int min) {
//   visit[s] = 1;
//   if (s == t) {
//     printf("valor da menor aresta � %d\n %d ", min, s);
//     return min;
//   }
//   for (int i = 0; i < N; i++) {
//     if (visit[i])
//       continue;
//     int contrario = cont(s, i);
//     int direto = dir(s, i);
//     if (contrario || direto) {
//       int maior = contrario < direto ? direto : contrario;
//       int minaresta;
//       if (minaresta = dfs(i, t, maior < min ? maior : min)) {
//         if (direto >= minaresta)
//           F[s][i] += minaresta;
//         else
//           F[i][s] -= minaresta;
//         printf("%d ", s);
//         visit[s] = 0; // aqui ele para na metade, � uma tristeza
//         return minaresta;
//       }
//     }
//   }
//   visit[s] = 0;
//   return 0;
// }

void
dfs(int start_index,
    int G[MAX_PLUGIN_APIS][MAX_PLUGIN_APIS],
    int ordered_indices[MAX_PLUGIN_APIS],
    int* current_index,
    int visited[MAX_PLUGIN_APIS]) {
  visited[start_index] = 1;

  for (int i = 0; i < MAX_PLUGIN_APIS; ++i) {
    if (i == start_index)
      continue;
    if (!visited[i] && G[start_index][i])
      dfs(i, G, ordered_indices, current_index, visited);
  }
  int index = MAX_PLUGIN_APIS-1-(*current_index)++;
  ordered_indices[index]=start_index;
}

void //
get_dependency_order(int start_index, int G[MAX_PLUGIN_APIS][MAX_PLUGIN_APIS], int* ordered_indices) {
  int current_index = start_index;
  int visited[MAX_PLUGIN_APIS] = {0};

  for (int i = 0; i < MAX_PLUGIN_APIS; ++i) {
    if (!visited[i])
      dfs(start_index, G, ordered_indices, &current_index, visited);
  }
}

int
main() {
  int G[MAX_PLUGIN_APIS][MAX_PLUGIN_APIS] = {0};
  G[0][1] = 1;
  G[1][2] = 1;
  G[0][3] = 1;
  G[1][3] = 1;
  G[2][4] = 1;
  G[3][4] = 1;

  int ordered[MAX_PLUGIN_APIS] = {0};
  for (int i = 0; i < MAX_PLUGIN_APIS; ++i) {
    for (int j = 0; j < MAX_PLUGIN_APIS; ++j) {
      printf("%d ", G[i][j]);
    }
    printf("\n");
  }

  get_dependency_order(0, G, ordered);
  for (int i = 0; i < MAX_PLUGIN_APIS; ++i)
    printf("[f] %d\n", ordered[i]);
  system("pause");
}