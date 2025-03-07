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
 * @file Tests for graph generation
 * @brief Test suite for all graph generating functions.
 */

#include "api.h"       // Assuming all dependencies are included in generator.c
#include "generator.h" // Assuming all dependencies are included in generator.c
#include "search.h"    // Assuming all dependencies are included in generator.c
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_genCompleteGraph() {
  printf("Testing genCompleteGraph...\n");

  u32 n = 50;
  Graph *G = genCompleteGraph(n);

  assert(G != NULL);
  assert(numberOfVertices(G) == n);
  assert(numberOfEdges(G) == n * (n - 1) / 2);
  assert(isConnected(G));

  for (u32 i = 0; i < n; i++) {
    assert(degree(i, G) ==
           n - 1); // Complete graph: each vertex should connect to n-1 vertices
    for (u32 j = 0; j < n; j++) {
      if (i != j) {
        assert(isNeighbour(i, j, G)); // Check that all pairs are connected
      }
    }
  }
  printf("genCompleteGraph passed.\n");
  dumpGraph(G);
}

void test_fromPruferSequence() {
  printf("Testing fromPruferSequence...\n");

  u32 prufer[] = {0, 1, 2, 3}; // Prufer sequence for a 6-node tree
  u32 prufer_len = sizeof(prufer) / sizeof(prufer[0]);

  Graph *T = fromPruferSequence(prufer, prufer_len);

  u32 n = prufer_len + 2; // Number of nodes in the tree
  assert(T != NULL);
  assert(numberOfVertices(T) == n);
  assert(numberOfEdges(T) == n - 1); // A tree has n-1 edges
  assert(isConnected(T));

  printf("fromPruferSequence passed.\n");
  dumpGraph(T);
}

void test_genGammas() {
  printf("Testing genGammas...\n");

  Graph *G = genCompleteGraph(4);
  u32 **gammaLists = genGammas(G);

  assert(gammaLists != NULL);
  for (u32 i = 0; i < numberOfVertices(G); i++) {
    u32 d = degree(i, G);
    for (u32 j = 0; j < d; j++) {
      assert(isNeighbour(i, gammaLists[i][j],
                         G)); // Ensure all neighbors in gamma list are valid
    }
    free(gammaLists[i]);
  }
  free(gammaLists);

  dumpGraph(G);
  printf("genGammas passed.\n");
}

void test_genGammaComplements() {
  printf("Testing genGammaComplements...\n");

  Graph *G = genCompleteGraph(4);
  u32 **gammaComplements = genGammaComplements(G);

  assert(gammaComplements != NULL);
  for (u32 i = 0; i < numberOfVertices(G); i++) {
    u32 nonNeighborCount = 0;
    for (u32 j = 0; j < numberOfVertices(G); j++) {
      if (!isNeighbour(i, j, G) && i != j) {
        assert(gammaComplements[i][nonNeighborCount] == j);
        nonNeighborCount++;
      }
    }
    free(gammaComplements[i]);
  }
  free(gammaComplements);

  dumpGraph(G);
  printf("genGammaComplements passed.\n");
}

void test_randomTree() {
  printf("Testing randomTree...\n");

  u32 n = 50;
  Graph *T = randomTree(n);

  assert(T != NULL);
  assert(numberOfVertices(T) == n);
  assert(numberOfEdges(T) == n - 1); // A tree has n-1 edges
  assert(isConnected(T));

  dumpGraph(T);
  printf("randomTree passed.\n");
}

void test_genCGraphUnbound() {
  printf("Testing genCGraphUnbound...\n");

  u32 n = 50;
  Graph *G = genCGraphUnbound(n);

  assert(G != NULL);
  assert(numberOfVertices(G) == n);
  assert(numberOfEdges(G) >=
         n - 1); // Graph should have at least n-1 edges to remain connected
  assert(isConnected(G));

  dumpGraph(G);
  printf("genCGraphUnbound passed.\n");
}

void test_genFromRandomTree() {
  printf("Testing genCGraph...\n");

  u32 n = 50;
  u32 m = 100; // Should be between n-1 and n*(n-1)/2 for connected graphs
  Graph *G = genFromRandomTree(n, m);

  assert(G != NULL);
  assert(numberOfVertices(G) == n);
  assert(numberOfEdges(G) == m);
  assert(isConnected(G));
  dumpGraph(G);

  printf("genCGraph passed.\n");
}

void test_genFromKn() {
  printf("Testing genFromKn...\n");

  u32 n = 50;
  u32 m = 100; // Retain this many edges in the generated graph
  Graph *G = genFromKn(n, m);

  assert(G != NULL);
  assert(numberOfVertices(G) == n);
  assert(numberOfEdges(G) == m);
  assert(isConnected(G));
  dumpGraph(G);

  printf("genFromKn passed.\n");
}

int main() {
  test_genCompleteGraph();
  test_fromPruferSequence();
  test_genGammas();
  test_genGammaComplements();
  test_randomTree();
  test_genCGraphUnbound();
  test_genFromRandomTree();
  test_genFromKn();

  printf("All tests passed!\n");
  return 0;
}
