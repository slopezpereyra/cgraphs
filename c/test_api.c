#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "api.h"

// Test suite for Graph API

/**
 * @brief Tests the creation of a new edge and verifies if the x and y values are correctly assigned.
 */
void testNewEdge() {
    Edge *edge = newEdge(1, 2);
    assert(edge->x == 1);
    assert(edge->y == 2);
    free(edge);
    printf("testNewEdge passed.\n");
}

/**
 * @brief Tests the initialization of a new graph and checks initial vertex and edge counts.
 */
void testInitGraph() {
    Graph *G = initGraph(5, 3, STD_FLAG);
    assert(G->n == 5);
    assert(G->m == 3);
    assert(G->Δ == 0);
    for (u32 i = 0; i < 2*numberOfEdges(G); i++){
        Edge e = (G -> _edges)[i];
        assert (e.x == 0 && e.y == 0);
    }
    for (u32 i = 0; i < numberOfVertices(G); i++){
        assert ((G->_firstneighbour)[i] == 0);
        assert (G->_colors == NULL);
        assert (G->_weights == NULL);
        assert ((G->_degrees)[i] == 0);
    }
    dumpGraph(G);
    printf("testInitGraph passed.\n");
}

/**
 * @brief Tests the edge setting in a graph and verifies correct adjacency for both directed edges.
 */
void testSetEdge() {
    Graph *G = initGraph(3, 2, STD_FLAG);
    setEdge(G, 0, 1, 2);
    assert(G->_edges[0].x == 1 && G->_edges[0].y == 2);
    assert(G->_edges[G->m].x == 2 && G->_edges[G->m].y == 1);
    assert(degree(1, G) == 1);
    setEdge(G, 0, 1, 3);
    assert(degree(1, G) == 1);
    setEdge(G, 1, 1, 2);
    assert(degree(1, G) == 2);
    dumpGraph(G);
    printf("testSetEdge passed.\n");
}

/**
 * @brief Tests the addition of an edge and verifies if the number of edges and degrees are updated.
 */
void testAddEdge() {
    Graph *G = initGraph(4, 1, STD_FLAG);
    setEdge(G, 0, 1, 2);
    addEdge(G, 0, 1);
    addEdge(G, 0, 2);
    addEdge(G, 2, 3);
    assert(G->m == 4);
    assert(isNeighbour(0, 1, G));
    assert(isNeighbour(1, 2, G));
    assert(isNeighbour(0, 2, G));
    assert(isNeighbour(2, 3, G));

    // The added edge should now be the first,
    // because (0, 1) < (1, 2).
    Edge e = getIthEdge(0, G);
    assert (e.x == 0 && e.y == 1);
    // Test degrees make sense
    assert (degree(0, G) == 2);
    assert (degree(1, G) == 2);
    assert (degree(2, G) == 3);
    assert (degree(3, G) == 1);
    assert (Δ(G) == 3);
    dumpGraph(G);
    printf("testAddEdge passed.\n");
}


/**
 * @brief Tests the functionality of `edgeIndex` to get correct edge position in the array.
 */
void testEdgeIndex() {
    Graph *G = initGraph(4, 3, STD_FLAG);
    setEdge(G, 0, 1, 2);
    setEdge(G, 1, 0, 2);
    setEdge(G, 2, 2, 3);

    formatEdges(G);

    assert(edgeIndex(G, 0, 2) == 0);
    assert(edgeIndex(G, 1, 2) == 1);
    assert(edgeIndex(G, 2, 3) == 4);

    dumpGraph(G);
    printf("testEdgeIndex passed.\n");
}


/**
 * @brief Test getEdge
 */
void testGetEdge() {
    Graph *G = initGraph(4, 3, STD_FLAG);
    setEdge(G, 0, 1, 2);
    setEdge(G, 1, 0, 2);
    setEdge(G, 2, 2, 3);

    formatEdges(G);

    assert(edgeIndex(G, 0, 2) == 0);
    assert(edgeIndex(G, 1, 2) == 1);
    assert(edgeIndex(G, 2, 3) == 4);

    Edge e = getEdge(0, 2, G);
    assert(e.x == 0);
    assert(e.y == 2);

    dumpGraph(G);
    printf("testEdgeIndex passed.\n");
}

/**
 * @brief Tests the removal of an edge and checks if degrees and edges are correctly updated.
 */
void testRemoveEdge() {
    Graph *G = initGraph(4, 4, STD_FLAG);
    setEdge(G, 0, 1, 2);
    setEdge(G, 1, 0, 1);
    setEdge(G, 2, 0, 2);
    setEdge(G, 3, 2, 3);

    formatEdges(G);

    removeEdge(G, 0, 2);

    assert(!isNeighbour(0, 2, G));
    assert(G->m == 3);

    dumpGraph(G);
    printf("testRemoveEdge passed.\n");
}

/**
 * @brief Tests neighbor functionality to ensure `isNeighbour` detects connectivity correctly.
 */
void testIsNeighbour() {
    Graph *G = initGraph(3, 1, STD_FLAG);
    setEdge(G, 0, 1, 2);
    formatEdges(G);
    assert(isNeighbour(1, 2, G) == true);
    assert(isNeighbour(0, 2, G) == false);
    dumpGraph(G);
    printf("testIsNeighbour passed.\n");
}


/**
 * @brief Tests that the degree values are correctly calculated and stored in the graph.
 */
void testDegree() {
    Graph *G = initGraph(3, 2, STD_FLAG);
    setEdge(G, 0, 0, 1);
    setEdge(G, 1, 1, 2);
    formatEdges(G);
    assert(degree(1, G) == 2);
    assert(degree(0, G) == 1);
    dumpGraph(G);
    printf("testDegree passed.\n");
}

/**
 * @brief Tests coloring functionality by setting and getting vertex colors.
 */
void testColors() {
    Graph *G = initGraph(3, 1, C_FLAG);
    assert(G->_colors != NULL);
    printf("\nHERE\n");
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
    Edge e1 = {1, 2};
    Edge e2 = {2, 3};
    Edge e3 = {1, 3};
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
    Graph *G = readGraph("../testGraph.txt");
    assert(G != NULL);
    assert(numberOfVertices(G) == 4);
    assert(numberOfEdges(G) == 3);
    assert(Δ(G) == 1);
    bool t = isNeighbour(0, 1, G) && isNeighbour(1, 2, G) && isNeighbour(2, 3, G);
    assert(t);
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
