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






#include "dijkstra.h"
#include "utils.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void test_denseGraph() {
  Graph *G = readGraph("graphs/dijkstraTest.txt");

  // Run Dijkstra starting from vertex 0
  u32 *distances = dijkstra(0, G);

  // Expected shortest distances from vertex 0 to others
  u32 expected_distances[10] = {0, 2, 5, 1, 4, 5, 6, 6, 5, 8};

  // Validate the distances
  for (u32 i = 0; i < numberOfVertices(G); i++) {
    assert(distances[i] == expected_distances[i]);
  }

  free(distances);
  dumpGraph(G);
  printf("Dense graph test passed.\n");
}

int main() { test_denseGraph(); }
