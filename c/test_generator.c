/**
 * @file Tests for graph generation
 * @brief Test suite for all graph generating functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "generator.h" // Assuming all dependencies are included in generator.c
#include "api.h" // Assuming all dependencies are included in generator.c
#include "search.h" // Assuming all dependencies are included in generator.c

void test_genCompleteGraph() {
    printf("Testing genCompleteGraph...\n");

    u32 n = 50;
    struct Graph *G = genCompleteGraph(n);

    assert(G != NULL);
    assert(numberOfVertices(G) == n);
    assert(numberOfEdges(G) == n * (n - 1) / 2);
    assert(isConnected(G));

    for (u32 i = 0; i < n; i++) {
        assert(degree(i, G) == n - 1); // Complete graph: each vertex should connect to n-1 vertices
        for (u32 j = 0; j < n; j++) {
            if (i != j) {
                assert(isNeighbour(i, j, G)); // Check that all pairs are connected
            }
        }
    }
    printf("genCompleteGraph passed.\n");
}

void test_fromPruferSequence() {
    printf("Testing fromPruferSequence...\n");

    u32 prufer[] = {0, 1, 2, 3}; // Prufer sequence for a 6-node tree
    u32 prufer_len = sizeof(prufer) / sizeof(prufer[0]);

    struct Graph *T = fromPruferSequence(prufer, prufer_len);

    u32 n = prufer_len + 2; // Number of nodes in the tree
    assert(T != NULL);
    assert(numberOfVertices(T) == n);
    assert(numberOfEdges(T) == n - 1); // A tree has n-1 edges
    assert(isConnected(T));

    printf("fromPruferSequence passed.\n");
}

void test_genGammas() {
    printf("Testing genGammas...\n");

    struct Graph *G = genCompleteGraph(4);
    u32 **gammaLists = genGammas(G);

    assert(gammaLists != NULL);
    for (u32 i = 0; i < numberOfVertices(G); i++) {
        u32 d = degree(i, G);
        for (u32 j = 0; j < d; j++) {
            assert(isNeighbour(i, gammaLists[i][j], G)); // Ensure all neighbors in gamma list are valid
        }
        free(gammaLists[i]);
    }
    free(gammaLists);

    printf("genGammas passed.\n");
}

void test_genGammaComplements() {
    printf("Testing genGammaComplements...\n");

    struct Graph *G = genCompleteGraph(4);
    u32 **gammaComplements = genGammaComplements(G);

    assert(gammaComplements != NULL);
    for (u32 i = 0; i < numberOfVertices(G); i++) {
        u32 nonNeighborCount = 0;
        for (u32 j = 0; j < numberOfVertices(G); j++) {
            if (!isNeighbour(i, j, G) && i != j) {
                assert(gammaComplements[i][nonNeighborCount] == j);
                nonNeighborCount++;
            }
        }
        free(gammaComplements[i]);
    }
    free(gammaComplements);

    printf("genGammaComplements passed.\n");
}

void test_randomTree() {
    printf("Testing randomTree...\n");

    u32 n = 50;
    struct Graph *T = randomTree(n);

    assert(T != NULL);
    assert(numberOfVertices(T) == n);
    assert(numberOfEdges(T) == n - 1); // A tree has n-1 edges
    assert(isConnected(T));

    printf("randomTree passed.\n");
}

void test_genCGraphUnbound() {
    printf("Testing genCGraphUnbound...\n");

    u32 n = 50;
    struct Graph *G = genCGraphUnbound(n);

    assert(G != NULL);
    assert(numberOfVertices(G) == n);
    assert(numberOfEdges(G) >= n - 1); // Graph should have at least n-1 edges to remain connected
    assert(isConnected(G));

    printf("genCGraphUnbound passed.\n");
}

void test_genCGraph() {
    printf("Testing genCGraph...\n");

    u32 n = 50;
    u32 m = 100; // Should be between n-1 and n*(n-1)/2 for connected graphs
    struct Graph *G = genCGraph(n, m);

    assert(G != NULL);
    assert(numberOfVertices(G) == n);
    assert(numberOfEdges(G) == m);
    assert(isConnected(G));

    printf("genCGraph passed.\n");
}

void test_genConnectedGraphFromKn() {
    printf("Testing genConnectedGraphFromKn...\n");

    u32 n = 50;
    u32 m = 100; // Retain this many edges in the generated graph
    struct Graph *G = genConnectedGraphFromKn(n, m);

    assert(G != NULL);
    assert(numberOfVertices(G) == n);
    assert(numberOfEdges(G) == m);
    assert(isConnected(G));

    printf("genConnectedGraphFromKn passed.\n");
}

int main() {
    test_genCompleteGraph();
    test_fromPruferSequence();
    test_genGammas();
    test_genGammaComplements();
    test_randomTree();
    test_genCGraphUnbound();
    test_genCGraph();
    test_genConnectedGraphFromKn();

    printf("All tests passed!\n");
    return 0;
}
