#include "dijkstra.h"
#include "wapi.h"
#include "utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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


void stressTest() {
    u32 vertices = 1000;
    u32 edges = 2000;
    Graph *G = initGraph(vertices, edges, W_FLAG);
    
    for (u32 i = 0; i < edges; i++) {
        setEdge(G, i, i % vertices, (i + 1) % vertices);
    }
    formatEdges(G);
    for (u32 i = 0; i < edges; i++) {
        setEdgeWeight(i, i % vertices, i, G);
    }
    
    u32 *distances = dijkstra(0, G);
    
    for (u32 i = 0; i < vertices; i++) {
        assert(distances[i] >= 0); // Check that no distance is negative
    }
    
    free(distances);
    dumpGraph(G);
    printf("Stress test passed.\n");
}


void test_disconnectedGraph() {
    Graph *G = initGraph(4, 2, W_FLAG);
    setEdge(G, 0, 0, 1); // Edge 0-1
    setEdge(G, 1, 1, 2); // Edge 1-2
    formatEdges(G);

    setEdgeWeight(0, 1, 4, G);
    setEdgeWeight(1, 1, 2, G);
    
    u32 *distances = dijkstra(0, G);
    
    assert(distances[0] == 0);
    assert(distances[1] == 4);
    assert(distances[2] == 6);
    assert(distances[3] == INT_MAX); // Vertex 3 is disconnected
    
    free(distances);
    dumpGraph(G);
    printf("Disconnected graph test passed.\n");
}

void test_denseGraph() {
    u32 vertices = 10;
    u32 edges = 15; 
    Graph *G = initGraph(vertices, edges, W_FLAG);

    // Manually define a set of edges and weights for a dense configuration
    u32 edges_data[15][3] = {
        {0, 1, 2}, {0, 2, 5}, {0, 3, 1},
        {1, 4, 2}, {1, 5, 3}, {1, 6, 4},
        {2, 7, 6}, {2, 8, 2}, {3, 9, 7},
        {3, 4, 3}, {4, 8, 1}, {5, 9, 9},
        {6, 7, 2}, {7, 8, 1}, {8, 9, 4}
    };

    // Add edges to the graph and set weights
    for (u32 i = 0; i < 15; i++) {
        u32 x = edges_data[i][0];
        u32 y = edges_data[i][1];
        
        setEdge(G, i, x, y);
    }
    formatEdges(G);
    for (u32 i = 0; i < 15; i++){
        setEdgeWeight(edges_data[i][0], edges_data[i][1], edges_data[i][2], G);
    }

    // Run Dijkstra starting from vertex 0
    u32 *distances = dijkstra(0, G);

    // Expected shortest distances from vertex 0 to others
    u32 expected_distances[10] = {0, 2, 5, 1, 4, 5, 6, 6, 5, 8};

    // Validate the distances
    for (u32 i = 0; i < vertices; i++) {
        printf("\n%d : %d ~~~ %d\n", i, distances[i], expected_distances[i]);
        assert(distances[i] == expected_distances[i]);
    }

    free(distances);
    dumpGraph(G);
    printf("Dense graph test passed.\n");
}

int main(){
    test_simplePath();
    test_cycleGraph();
    stressTest();
    test_disconnectedGraph();
    test_denseGraph();
}
