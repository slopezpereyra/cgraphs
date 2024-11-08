#include "prim.h"
#include "utils.h"
#include <assert.h>
#include <limits.h>
#include <search.h>
#include <stdio.h>
#include <stdlib.h>

void test_prim() {
  Graph *G = readGraph("graphs/primTest.txt");
  Graph *P = prim(G, 0);

  assert(numberOfEdges(P) == 8 && numberOfVertices(P) == 9);
  assert(isConnected(P));

  u32 edges[16][3] = {{0, 1, 4}, {0, 7, 8}, {1, 0, 4}, {2, 3, 7},
                      {2, 5, 4}, {2, 8, 2}, {3, 2, 7}, {3, 4, 9},
                      {4, 3, 9}, {5, 2, 4}, {5, 6, 2}, {6, 5, 2},
                      {6, 7, 1}, {7, 0, 8}, {7, 6, 1}, {8, 2, 2}};

  for (u32 i = 0; i < 2 * numberOfEdges(P); i++) {
    Edge e = getIthEdge(i, P);
    assert(e.x == edges[i][0] && e.y == edges[i][1] && *e.w == edges[i][2]);
  }
  dumpGraph(G);
  dumpGraph(P);
}

void run_all_tests() {
  test_prim();
  printf("All tests passed!\n");
}

int main() {
  run_all_tests();
  return 0;
}
