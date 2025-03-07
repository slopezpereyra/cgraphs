/** MIT License
 *
 * Copyright (c) 2024 Santiago López Pereyra
 *
 * santiagolopezpereyra@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * The software is provided "as is", without warranty of any kind, express or
 * implied, including but not limited to the warranties of merchantability,
 * fitness for a particular purpose, and noninfringement. In no event shall the
 * authors or copyright holders be liable for any claim, damages, or other
 * liability, whether in an action of contract, tort, or otherwise, arising from,
 * out of or in connection with the software or the use or other dealings in the
 * software.
 */






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
