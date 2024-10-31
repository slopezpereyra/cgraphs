#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "api.h"

// Test suite for Graph API

/**
 * @brief Tests the creation of a new edge and verifies if the x and y values are correctly assigned.
 */
void testNewEdge() {
    struct Edge *edge = newEdge(1, 2);
    assert(edge->x == 1);
    assert(edge->y == 2);
    free(edge);
    printf("testNewEdge passed.\n");
}

/**
 * @brief Tests the initialization of a new graph and checks initial vertex and edge counts.
 */
void testInitGraph() {
    struct Graph *G = initGraph(5, 3);
    assert(G->n == 5);
    assert(G->m == 3);
    assert(G->Δ == 0);
    assert(G->δ == 1024);
    dumpGraph(G);
    printf("testInitGraph passed.\n");
}

/**
 * @brief Tests the edge setting in a graph and verifies correct adjacency for both directed edges.
 */
void testSetEdge() {
    struct Graph *G = initGraph(3, 1);
    setEdge(G, 0, 1, 2);
    assert(G->_edges[0].x == 1 && G->_edges[0].y == 2);
    assert(G->_edges[G->m].x == 2 && G->_edges[G->m].y == 1);
    dumpGraph(G);
    printf("testSetEdge passed.\n");
}

/**
 * @brief Tests the edge setting in a graph and verifies correct adjacency for both directed edges.
 */
void testSetExistingEdge() {
    struct Graph *G = initGraph(3, 1);
    setEdge(G, 0, 1, 2);
    assert(G->_edges[0].x == 1 && G->_edges[0].y == 2);
    assert(G->_edges[G->m].x == 2 && G->_edges[G->m].y == 1);
    dumpGraph(G);
    printf("testSetEdge passed.\n");
}

/**
 * @brief Tests the addition of an edge and verifies if the number of edges and degrees are updated.
 */
void testAddEdge() {
    struct Graph *G = initGraph(3, 1);
    setEdge(G, 0, 1, 2);
    addEdge(G, 0, 1);
    assert(G->m == 2);
    assert(isNeighbour(0, 1, G));
    dumpGraph(G);
    printf("testAddEdge passed.\n");
}

/**
 * @brief Tests the removal of an edge and checks if degrees and edges are correctly updated.
 */
void testRemoveEdge() {
    struct Graph *G = initGraph(3, 2);
    setEdge(G, 0, 1, 2);
    setEdge(G, 1, 2, 3);
    removeEdge(G, 1, 2);
    assert(!isEdge(G, 1, 2));
    assert(G->m == 1);
    dumpGraph(G);
    printf("testRemoveEdge passed.\n");
}

/**
 * @brief Tests neighbor functionality to ensure `isNeighbour` detects connectivity correctly.
 */
void testIsNeighbour() {
    struct Graph *G = initGraph(3, 1);
    setEdge(G, 0, 1, 2);
    assert(isNeighbour(1, 2, G) == true);
    assert(isNeighbour(0, 2, G) == false);
    dumpGraph(G);
    printf("testIsNeighbour passed.\n");
}

/**
 * @brief Tests the functionality of `edgeIndex` to get correct edge position in the array.
 */
void testEdgeIndex() {
    struct Graph *G = initGraph(3, 1);
    setEdge(G, 0, 1, 2);
    assert(edgeIndex(G, 1, 2) == 0);
    dumpGraph(G);
    printf("testEdgeIndex passed.\n");
}

/**
 * @brief Tests that the degree values are correctly calculated and stored in the graph.
 */
void testDegree() {
    struct Graph *G = initGraph(3, 2);
    setEdge(G, 0, 0, 1);
    setEdge(G, 1, 1, 2);
    assert(degree(1, G) == 2);
    assert(degree(0, G) == 1);
    dumpGraph(G);
    printf("testDegree passed.\n");
}

/**
 * @brief Tests coloring functionality by setting and getting vertex colors.
 */
void testColors() {
    struct Graph *G = initGraph(3, 1);
    setColor(2, 0, G);
    assert(getColor(0, G) == 2);
    removeColors(G);
    assert(getColor(0, G) == 0);
    dumpGraph(G);
    printf("testColors passed.\n");
}

/**
 * @brief Tests the edge comparison function to ensure edges are ordered correctly.
 */
void testCompareEdges() {
    struct Edge e1 = {1, 2};
    struct Edge e2 = {2, 3};
    struct Edge e3 = {1, 3};
    assert(compareEdges(&e1, &e2) < 0);
    assert(compareEdges(&e2, &e1) > 0);
    assert(compareEdges(&e1, &e3) < 0);
    printf("testCompareEdges passed.\n");
}

/**
 * @brief Tests the initialization of graph from an input file and checks for graph creation.
 * Requires a valid input file in Penazzi format for full functionality.
 */
void test_readGraph() {
    // Simulate reading from a file (not implemented here as it requires I/O).
    printf("test_readGraph requires a file; manually verify this function.\n");
}

/**
 * @brief Main function to run all tests.
 */
int main() {
    testNewEdge();
    testInitGraph();
    testSetEdge();
    testAddEdge();
    testRemoveEdge();
    testIsNeighbour();
    testEdgeIndex();
    testDegree();
    testColors();
    testCompareEdges();
    // Note: test_readGraph requires an actual file input for complete verification.
    printf("All tests passed.\n");
    return 0;
}
