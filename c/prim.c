/**
 * @file prim.c
 * @brief An implementation of Prim's algorithm for generating a spanning tree 
 * of a weighted graph which minimizes the sum of the weights of the used edges.
 */

#include "api.h"
#include "utils.h"
#include "heap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

Graph *prim(Graph *G, u32 startVertex) {

  bool *inMST = (bool *)calloc(G->n, sizeof(bool));
  u32 n = numberOfVertices(G);
  Graph *MST = initGraph(n, 0, W_FLAG);
  inMST[startVertex] = 1;

  while (numberOfEdges(MST) < n - 1) {

    u32 edgeToAdd[3] = {0, 0, INT_MAX};

    for (u32 v = 0; v < n; v++) {
      if (!inMST[v] || degree(v, MST) == degree(v, G))
        continue;

      for (u32 j = 0; j < degree(v, G); j++) {
        u32 iNeighbour = neighbour(j, v, G);
        if (inMST[iNeighbour])
          continue;
        Edge e = getEdge(v, iNeighbour, G);
        if (*(e.w) < edgeToAdd[2]) {
          edgeToAdd[0] = v;
          edgeToAdd[1] = iNeighbour;
          edgeToAdd[2] = *e.w;
        }
      }
    }
    addEdge(MST, edgeToAdd[0], edgeToAdd[1], &edgeToAdd[2]);
    inMST[edgeToAdd[1]] = 1;
  }

  free(inMST);
  return (MST);
}
