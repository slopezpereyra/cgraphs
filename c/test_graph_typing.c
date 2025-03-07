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






#include "api.h" // Include the header for the initGraph function
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_initGraph_standard() {
  Graph *G = initGraph(5, 10, STD_FLAG);

  assert(G != NULL);
  assert(G->n == 5);
  assert(G->m == 10);
  assert(G->_edgeArraySize == 20); // STD_FLAG implies undirected graph
  assert(G->_edges != NULL);
  assert(G->_firstneighbour != NULL);
  assert(G->_g_flag == STD_FLAG);
  assert(G->_degrees != NULL);
  assert(G->_indegrees == NULL);
  assert(G->_outdegrees == NULL);
  assert(G->_colors == NULL);

  printf("test_initGraph_standard passed\n");
  dumpGraph(G);
}

void test_initGraph_directed() {
  Graph *G = initGraph(5, 10, D_FLAG);

  assert(G != NULL);
  assert(G->n == 5);
  assert(G->m == 10);
  assert(G->_edgeArraySize == 10); // Directed graph
  assert(G->_edges != NULL);
  assert(G->_firstneighbour != NULL);
  assert(G->_g_flag & D_FLAG);
  assert(G->_degrees == NULL);
  assert(G->_indegrees != NULL);
  assert(G->_outdegrees != NULL);
  assert(G->_colors == NULL);

  printf("test_initGraph_directed passed\n");
  dumpGraph(G);
}

void test_initGraph_colored() {
  Graph *G = initGraph(5, 10, COL_FLAG);

  assert(G != NULL);
  assert(G->n == 5);
  assert(G->m == 10);
  assert(G->_edgeArraySize == 20); // Undirected graph by default
  assert(G->_edges != NULL);
  assert(G->_firstneighbour != NULL);
  assert(G->_g_flag == COL_FLAG);
  assert(G->_degrees != NULL);
  assert(G->_indegrees == NULL);
  assert(G->_outdegrees == NULL);
  assert(G->_colors != NULL); // Colored graph

  printf("test_initGraph_colored passed\n");
  dumpGraph(G);
}

void test_initGraph_weighted() {
  Graph *G = initGraph(5, 10, W_FLAG);

  assert(G != NULL);
  assert(G->n == 5);
  assert(G->m == 10);
  assert(G->_edgeArraySize == 20); // Undirected graph by default
  assert(G->_edges != NULL);
  assert(G->_firstneighbour != NULL);
  assert(G->_g_flag == W_FLAG);
  assert(G->_degrees != NULL);
  assert(G->_indegrees == NULL);
  assert(G->_outdegrees == NULL);
  assert(G->_colors == NULL); // Not colored

  printf("test_initGraph_weighted passed\n");
  dumpGraph(G);
}

void test_initGraph_netflow() {
  Graph *G = initGraph(5, 10, NETFLOW_FLAG);

  assert(G != NULL);
  assert(G->n == 5);
  assert(G->m == 10);
  assert(G->_edgeArraySize == 10); // Directed graph with netflow
  assert(G->_edges != NULL);
  assert(G->_firstneighbour != NULL);
  assert(G->_g_flag == NETFLOW_FLAG);
  assert(G->_degrees == NULL);
  assert(G->_indegrees != NULL);
  assert(G->_outdegrees != NULL);
  assert(G->_colors == NULL); // Not colored

  printf("test_initGraph_netflow passed\n");
  dumpGraph(G);
}


void testDirectedWeightedNotFlow() {
  Graph *G = initGraph(5, 10, W_FLAG | D_FLAG);

  assert(G != NULL);
  assert(G->n == 5);
  assert(G->m == 10);
  assert(G->_edgeArraySize == 10); // Directed graph with netflow
  assert(G->_edges != NULL);
  assert(G->_firstneighbour != NULL);
  assert(G->_g_flag != NETFLOW_FLAG);
  assert(G->_g_flag == ( W_FLAG | D_FLAG ));
  assert(G->_degrees == NULL);
  assert(G->_indegrees != NULL);
  assert(G->_outdegrees != NULL);
  assert(G->_colors == NULL); // Not colored

  printf("test_initGraph_netflow passed\n");
  dumpGraph(G);
}

int main() {
  test_initGraph_standard();
  test_initGraph_directed();
  test_initGraph_colored();
  test_initGraph_weighted();
  test_initGraph_netflow();
  testDirectedWeightedNotFlow();

  printf("All tests passed.\n");
  return 0;
}
