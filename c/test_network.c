#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "api.h"

/**
 * @brief Tests the initialization of a new graph and checks initial vertex and edge counts.
 */
void testInitGraph() {
    Graph *G = initGraph(5, 3, F_FLAG);
    assert(G->n == 5);
    assert(G->m == 3);
    assert(G->Δ == 0);
    assert(G->_g_flag & W_FLAG);
    assert(G->_g_flag & F_FLAG);
    assert(!( G->_g_flag & C_FLAG ));
    for (u32 i = 0; i < 2*numberOfEdges(G); i++){
        Edge e = (G -> _edges)[i];
        assert (e.x == 0 && e.y == 0 && e.w != NULL && e.c != NULL);
    }
    for (u32 i = 0; i < numberOfVertices(G); i++){
        assert ((G->_firstneighbour)[i] == 0);
        assert (G->_colors == NULL);
        assert ((G->_degrees)[i] == 0);
    }
    dumpGraph(G);
}


/**
 * @brief Tests the addition of an edge and verifies if the number of edges and degrees are updated.
 */
void testAddEdge() {
    Graph *G = initGraph(4, 1, W_FLAG);
    setEdge(G, 0, 1, 2, NULL, NULL);
    addEdge(G, 0, 1, NULL, NULL);
    addEdge(G, 0, 2, NULL, NULL);
    addEdge(G, 2, 3, NULL, NULL);
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
    setEdge(G, 0, 1, 2, NULL, NULL);
    setEdge(G, 1, 0, 2, NULL, NULL);
    setEdge(G, 2, 2, 3, NULL, NULL);

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
    setEdge(G, 0, 1, 2, NULL, NULL);
    setEdge(G, 1, 0, 2, NULL, NULL);
    setEdge(G, 2, 2, 3, NULL, NULL);

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
    setEdge(G, 0, 1, 2, NULL, NULL);
    setEdge(G, 1, 0, 1, NULL, NULL);
    setEdge(G, 2, 0, 2, NULL, NULL);
    setEdge(G, 3, 2, 3, NULL, NULL);

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
    setEdge(G, 0, 1, 2, NULL, NULL);
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
    setEdge(G, 0, 0, 1, NULL, NULL);
    setEdge(G, 1, 1, 2, NULL, NULL);
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
    Edge e1 = {1, 2, NULL, NULL};
    Edge e2 = {2, 3, NULL, NULL};
    Edge e3 = {1, 3, NULL, NULL};
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
    Graph *G = readGraph("testGraph.txt");
    assert(G != NULL);
    assert(numberOfVertices(G) == 4);
    assert(numberOfEdges(G) == 3);
    assert(Δ(G) == 2);
    assert(G->_g_flag == STD_FLAG);
    bool t = isNeighbour(0, 1, G) && isNeighbour(1, 2, G) && isNeighbour(2, 3, G);
    assert(t);

    Graph *W = readGraph("testGraphW.txt");
    assert(W != NULL);
    assert(W->_g_flag == W_FLAG);
    assert(numberOfVertices(W) == 4);
    assert(numberOfEdges(W) == 3);
    assert(Δ(W) == 2);
    bool tw = isNeighbour(0, 1, W) && isNeighbour(1, 2, W) && isNeighbour(2, 3, W);
    bool tw2 = *(getEdge(0, 1, W).w) == 1 && *(getEdge(1, 2, W).w) == 10 && *(getEdge(2, 3, W).w) == 20;
    assert(tw);
    assert(tw2);
    dumpGraph(W);
    dumpGraph(G);
}


/**
 * @brief Main function to run all tests.
 */
int main() {
    testInitGraph();
    test_readGraph();
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
