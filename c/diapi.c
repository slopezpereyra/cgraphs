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
 * @file diapi.c
 * @brief API for the Graph struct, including creating, formatting, printing,
 * and writing graphs.
 */

#include "api.h"
#include "graphStruct.h"
#include "utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Return the number of edges entering into vertex `i`.
 *
 */
u32 inDegree(u32 i, Graph *G) {
  assert(G != NULL);
  assert(G->_g_flag & D_FLAG);
  if (i < G->n) {
    return (G->_indegrees)[i];
  }
  return 0;
}

/**
 * @brief Set the `x` and `y` fields of the ith Edge structure of `G` to the
 * parameters `x` and `y`.
 *
 * If `m` is the number of edges in the graph, this function also sets
 * the (i + m)th edge structure to represent {y, x}.
 *
 * Upon setting an edge, the degree of the involved vertices and Δ
 * are updated.
 *
 * @note formatEdges(G) should be called after setting edges. It is not
 *       included in the function because setEdges is typically called
 *       several times repeatedly, and formatEdges(G) should be called
 *       once after all these calls for efficiency.
 *
 */
void setEdgeDigraph(Graph *G, u32 i, u32 x, u32 y, u32 *w, u32 *c) {

  (G->_edges)[i].x = x;
  (G->_edges)[i].y = y;
  if (w != NULL) {
    (G->_edges)[i].w = (u32 *)malloc(sizeof(u32));
    *(G->_edges)[i].w = *w;
  }
  if (c != NULL) {
    (G->_edges)[i].c = (u32 *)malloc(sizeof(u32));
    *(G->_edges)[i].c = *c;
  }
  (G->_outdegrees)[x]++;
  (G->_indegrees)[y]++;
  (G->Δ) = max(G->_outdegrees[x], G->Δ);
  G->_formatted = false;
}
