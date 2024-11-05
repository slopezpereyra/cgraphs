#include "dijkstra.h"
#include "utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


void test_denseGraph() {
    Graph *G = readGraph("graphs/dijkstraTest.txt");

    // Run Dijkstra starting from vertex 0
    u32 *distances = dijkstra(0, G);

    // Expected shortest distances from vertex 0 to others
    u32 expected_distances[10] = {0, 2, 5, 1, 4, 5, 6, 6, 5, 8};

    // Validate the distances
    for (u32 i = 0; i < numberOfVertices(G); i++) {
        printf("At %d : %d ~~~ %d\n", i, distances[i], expected_distances[i]);
        assert(distances[i] == expected_distances[i]);
    }

    free(distances);
    dumpGraph(G);
    printf("Dense graph test passed.\n");
}

int main(){
    test_denseGraph();
}
