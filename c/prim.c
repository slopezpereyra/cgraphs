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
 * @file prim.c
 * @brief An implementation of Prim's algorithm for generating a spanning tree
 * of a weighted graph which minimizes the sum of the weights of the used edges.
 */

#include "api.h"
#include "heap.h"
#include "utils.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// helper function
void addEdgesToHeap(u32 root, Heap *heap, bool *inMST, Graph *G) {

  u32 rootIndex = firstNeighbourIndex(G, root);

  for (u32 i = 0; i < degree(root, G); i++) {
    u32 w = neighbour(i, root, G);
    insert(heap, rootIndex + i, *getEdge(root, w, G).w);
  }
}

Graph *prim(Graph *G, u32 s) {

  bool *inMST = (bool *)calloc(G->n, sizeof(bool));
  u32 n = numberOfVertices(G);
  Graph *MST = initGraph(n, 0, W_FLAG);
  inMST[s] = 1;

  Heap *heap = createHeap(numberOfEdges(G));
  addEdgesToHeap(s, heap, inMST, G);
  inMST[s] = 1;

  while (numberOfEdges(MST) < n - 1) {

    HeapNode node = extractMin(heap);
    Edge edgeToAdd = getIthEdge(node.label, G);

    u32 newVertex = edgeToAdd.y;
    if (inMST[newVertex])
      continue;

    addEdge(MST, edgeToAdd.x, edgeToAdd.y, edgeToAdd.w, NULL);
    inMST[newVertex] = 1;
    addEdgesToHeap(newVertex, heap, inMST, G);
  }

  free(inMST);
  dumpHeap(heap);
  return (MST);
}
