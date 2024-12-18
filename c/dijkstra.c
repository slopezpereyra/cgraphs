/**
 * @file dijkstra.c
 * @brief An implementation of Dijkstra's algorithm for finding the minimum
 * distance from a root vertex `s` to all other vertices in a weighted graph.
 */

#include "api.h"
#include "utils.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

u32 *dijkstra(u32 s, Graph *G) {
  assert(G != NULL);
  assert(G->_g_flag & W_FLAG);

  u32 n = numberOfVertices(G);
  u32 *distances = genArray(n);
  u32 *visited = genArray(n);

  // Initial distances
  for (u32 i = 0; i < n; i++) {
    distances[i] = INT_MAX;
  }
  distances[s] = 0;

  while (true) {

    u32 v;
    u32 vDistance = INT_MAX;
    for (u32 w = 0; w < n; w++) {
      if (visited[w] != 0 || distances[w] == INT_MAX)
        continue;
      if (distances[w] < vDistance) {
        vDistance = distances[w];
        v = w;
      }
    }
    visited[v] = 1;

    // This only happens if all vertices were visited
    if (vDistance == INT_MAX) {
      free(visited);
      return distances;
    }

    // Traverse neighbours of v and update its distances
    for (u32 i = 0; i < degree(v, G); i++) {
      u32 iNeighbour = neighbour(i, v, G);
      if (visited[iNeighbour])
        continue;
      Edge e = getEdge(v, iNeighbour, G);
      u32 weight = *(e.w);
      distances[iNeighbour] = min(distances[iNeighbour], vDistance + weight);
    }
  }
}
