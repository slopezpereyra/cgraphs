#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "api.h"
#include "diapi.h"

/**
 * @brief Tests the initialization of a new graph and checks initial vertex and edge counts.
 */
void testInitGraph() {
    Graph *G = initGraph(5, 3, D_FLAG);
    assert(G->n == 5);
    assert(G->m == 3);
    assert(G->_edgeArraySize == G->m);
    assert(G->Δ == 0);
    assert(!( G->_g_flag & W_FLAG ));
    assert(!( G->_g_flag & C_FLAG ));
    assert(( G->_g_flag != F_FLAG ));
    for (u32 i = 0; i < G->_edgeArraySize; i++){
        Edge e = (G -> _edges)[i];
        assert (e.x == 0 && e.y == 0 && e.w == NULL && e.c == NULL);
    }
    for (u32 i = 0; i < numberOfVertices(G); i++){
        assert ((G->_firstneighbour)[i] == 0);
        assert (G->_colors == NULL);
        assert ((G->_outdegrees)[i] == 0);
        assert ((G->_indegrees)[i] == 0);
    }
    dumpGraph(G);
    printf("Test init graph succeded...\n");
}


/**
 * @brief Tests the addition of an edge and verifies if the number of edges and degrees are updated.
 */
void testAddEdge() {
    Graph *G = initGraph(4, 1, D_FLAG);
    assert(!( G->_g_flag & W_FLAG ));
    assert(( G->_g_flag != F_FLAG ));
    assert(!( G->_g_flag & C_FLAG ));
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
    assert (degree(1, G) == 1);
    assert (degree(2, G) == 1);
    assert (degree(3, G) == 0);
    assert (inDegree(3, G) == 1);
    assert (inDegree(2, G) == 2);
    assert (inDegree(1, G) == 1);
    assert (inDegree(0, G) == 0);

    assert (Δ(G) == 2);
    dumpGraph(G);
    printf("testAddEdge passed.\n");
}

void testReadGraph(){

    Graph *G = readGraph("graphs/simpleDigraph.txt");
    assert(G != NULL);
    assert(G->n == 6);
    assert(G->m == 7); 
    assert(G->_edgeArraySize == 7); 
    // Expected Graph
    // 0 ~~> 1  (10)  [30]
    // 0 ~~> 2  (20)  [30]
    // 1 ~~> 4  (30)  [30]
    // 2 ~~> 3  (10)  [30]
    // 2 ~~> 4  (5)  [30]
    // 3 ~~> 5  (20)  [30]
    // 4 ~~> 5  (10)  [30]
    u32 x[7] = {0, 0, 1, 2, 2, 3, 4};
    u32 y[7] = {1, 2, 4, 3, 4, 5, 5};
    for (u32 i = 0; i < G->_edgeArraySize; i++)
    {
        Edge e = getIthEdge(i, G);
        assert(e.x == x[i] && e.y == y[i]);
    }

}


/**
 * @brief Main function to run all tests.
 */
int main() {
    testInitGraph();
    testAddEdge();
    testReadGraph();
    printf("All tests passed.\n");
    return 0;
}
