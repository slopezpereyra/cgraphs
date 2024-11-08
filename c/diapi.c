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
