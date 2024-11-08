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
