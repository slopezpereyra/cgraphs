#include "prim.h"
#include "wapi.h"
#include "utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


void test_empty_graph() {
    Graph *G = initGraph(0, 0, W_FLAG);
    Graph *T = prim(0, G);
    assert(T == NULL);  // Expect NULL since there's no spanning tree for an empty graph.
    dumpGraph(G);
}

void test_single_node_graph() {
    Graph *G = initGraph(1, 0, W_FLAG);
    Graph *T = prim(0, G);
    assert(T != NULL);
    assert(numberOfVertices(T) == 1);  // Single vertex graph should return itself.
    assert(numberOfEdges(T) == 0);     // No edges in a single-node MST.
    dumpGraph(G);
    dumpGraph(T);
}

void test_two_nodes_one_edge() {
    Graph *G = initGraph(2, 1, W_FLAG);
    setEdge(G, 0, 1, 5);  // Set an edge with weight 5 between nodes 0 and 1.
    Graph *T = prim(0, G);
    assert(T != NULL);
    assert(numberOfVertices(T) == 2);
    assert(numberOfEdges(T) == 1);
    assert(getEdgeWeight(0, 1, T) == 5);  // Verify the edge weight in the MST.
    dumpGraph(G);
    dumpGraph(T);
}

void test_three_nodes_two_edges() {
    Graph *G = initGraph(3, 2, W_FLAG);
    setEdge(G, 0, 0, 1);
    setEdge(G, 1, 1, 2);
    formatEdges(G);
    setEdgeWeight(0, 1, 3, G);
    setEdgeWeight(1, 2, 5, G);
    Graph *T = prim(0, G);
    assert(T != NULL);
    assert(numberOfVertices(T) == 3);
    assert(numberOfEdges(T) == 2);
    dumpGraph(G);
    dumpGraph(T);
}

void test_four_nodes_multiple_edges() {
    Graph *G = initGraph(4, 5, W_FLAG);
    setEdge(G, 0, 1, 1);
    setEdge(G, 0, 2, 3);
    setEdge(G, 0, 3, 4);
    setEdge(G, 1, 2, 2);
    setEdge(G, 2, 3, 5);
    Graph *T = prim(0, G);
    assert(T != NULL);
    assert(numberOfVertices(T) == 4);
    assert(numberOfEdges(T) == 3);
    dumpGraph(G);
    dumpGraph(T);
}

void test_disconnected_graph() {
    Graph *G = initGraph(4, 2, W_FLAG);
    setEdge(G, 0, 1, 1);
    setEdge(G, 2, 3, 2);
    Graph *T = prim(0, G);
    assert(T == NULL);  // Expect NULL since the graph is disconnected.
    dumpGraph(G);
}

void test_large_graph() {
    int n = 1000;
    Graph *G = initGraph(n, n - 1, W_FLAG);
    for (int i = 0; i < n - 1; i++) {
        setEdge(G, i, i + 1, i + 1);
    }
    Graph *T = prim(0, G);
    assert(T != NULL);
    assert(numberOfVertices(T) == n);
    assert(numberOfEdges(T) == n - 1);
    dumpGraph(G);
    dumpGraph(T);
}

void run_all_tests() {
//    test_empty_graph();
//    test_single_node_graph();
//    test_two_nodes_one_edge();
    test_three_nodes_two_edges();
//    test_four_nodes_multiple_edges();
//    test_disconnected_graph();
//    test_large_graph();
    printf("All tests passed!\n");
}

int main() {
    run_all_tests();
    return 0;
}
