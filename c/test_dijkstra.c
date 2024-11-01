#include "dijkstra.h"
#include "wapi.h"
#include "utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_simplePath() {
    Graph *G = initGraph(3, 2, W_FLAG);
    setEdge(G, 0, 0, 1); // Edge 0-1
    setEdge(G, 1, 1, 2); // Edge 1-2
    formatEdges(G);
    setEdgeWeight(0, 1, 1, G);
    setEdgeWeight(1, 2, 2, G);
    
    u32 *distances = dijkstra(0, G); // Starting from vertex 0
    
    assert(distances[0] == 0);      // Distance to itself
    assert(distances[1] == 1);      // Distance 0 -> 1
    assert(distances[2] == 3);      // Distance 0 -> 1 -> 2
    
    free(distances);
    dumpGraph(G);
    printf("Simple path test passed.\n");
}


void test_cycleGraph() {
    Graph *G = initGraph(4, 4, W_FLAG);
    setEdge(G, 0, 0, 1); // Edge 0-1
    setEdge(G, 1, 1, 2); // Edge 1-2
    setEdge(G, 2, 2, 3); // Edge 2-3
    setEdge(G, 3, 3, 0); // Edge 3-0
    formatEdges(G);
    setEdgeWeight(0, 1, 1, G);
    setEdgeWeight(1, 2, 2, G);
    setEdgeWeight(2, 3, 3, G);
    setEdgeWeight(3, 0, 4, G);
    
    u32 *distances = dijkstra(0, G);
    
    assert(distances[0] == 0);
    assert(distances[1] == 1);
    assert(distances[2] == 3);
    assert(distances[3] == 4);
    
    free(distances);
    dumpGraph(G);
    printf("Cycle graph test passed.\n");
}

int main(){
    test_simplePath();
    test_cycleGraph();
}
