#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "search.h"
#include "queue.h"
#include "api.h"
#include "utils.h"

// Test if constructTreeFromArray builds the correct tree structure from a given insertion array.
void testConstructTreeFromArray() {
    printf("Testing constructTreeFromArray.\n");
    u32 insertionArray[] = {0, 1, 1, 2, 3}; // Simple parent-child relationship
    u32 n = 5;
    struct Graph *tree = _constructTreeFromArray(insertionArray, 5, n);
    assert(tree != NULL); // Tree should be created
    
    // Verify specific edges
    assert(isEdge(tree, 0, 1)); // Check root connection
    assert(isEdge(tree, 0, 2)); // Check middle connection
    assert(isEdge(tree, 1, 3)); // Check leaf connections
    assert(isEdge(tree, 2, 4)); // Check leaf connections
    
    dumpGraph(tree);
    printf("test_constructTreeFromArray passed.\n");
}

// Test BFS traversal to ensure tree structure is correct.
void testBFS() {
    printf("Testing BFS.\n");
    struct Graph *G = initGraph(5, 4); // Create a simple graph with 5 vertices
    setEdge(G, 0, 0, 1);
    setEdge(G, 1, 0, 2);
    setEdge(G, 2, 1, 3);
    setEdge(G, 3, 1, 4);
    formatEdges(G);
    
    struct Graph *BFSResult = BFS(G, 0); // Run BFS from vertex 0
    assert(BFSResult != NULL);

    // Verify BFS tree structure
    assert(isEdge(BFSResult, 0, 1));
    assert(isEdge(BFSResult, 0, 2));
    assert(isEdge(BFSResult, 1, 3));
    assert(isEdge(BFSResult, 1, 4));
    
    dumpGraph(BFSResult);
    dumpGraph(G);
    printf("testBFS passed.\n");
}

// Test DFS traversal to ensure tree structure is correct.
void testDFS() {
    printf("Testing DFS.\n");
    struct Graph *G = initGraph(5, 4); // Create a simple graph with 5 vertices
    setEdge(G, 0, 0, 1);
    setEdge(G, 1, 0, 2);
    setEdge(G, 2, 1, 3);
    setEdge(G, 3, 1, 4);
    
    struct Graph *DFSResult = DFS(G, 0); // Run DFS from vertex 0
    assert(DFSResult != NULL);

    // Verify DFS tree structure
    assert(isEdge(DFSResult, 0, 1));
    assert(isEdge(DFSResult, 1, 3) || isEdge(DFSResult, 1, 4)); // DFS is depth-prioritized
    
    dumpGraph(DFSResult);
    dumpGraph(G);
    printf("testDFS passed.\n");
}

// Test BFSSearch to check if the target vertex can be found in the graph.
void testBFSSearch() {
    printf("Testing BFS search.\n");
    struct Graph *G = initGraph(5, 4);
    setEdge(G, 0, 0, 1);
    setEdge(G, 1, 1, 2);
    setEdge(G, 2, 2, 3);
    setEdge(G, 3, 0, 0);
    formatEdges(G);

    assert(BFSSearch(G, 0, 3) == true);  // Target 3 should be reachable from 0
    assert(BFSSearch(G, 2, 3) == true); // Target 4 is not reachable from 2
    assert(BFSSearch(G, 0, 4) == false); // Target 4 is not reachable from 2
    
    dumpGraph(G);
    printf("testBFSSearch passed.\n");
}

// Test if the isConnected function correctly detects a connected graph.
void testIsConnected() {
    printf("Testing isConnected function.\n");
    struct Graph *G = initGraph(4, 3);
    setEdge(G, 0, 0, 1);
    setEdge(G, 1, 1, 2);
    setEdge(G, 2, 2, 3);
    formatEdges(G);

    assert(isConnected(G) == true); // Graph is connected
    
    struct Graph *disconnectedG = initGraph(4, 2);
    setEdge(disconnectedG, 0, 0, 0);

    assert(isConnected(disconnectedG) == false); // Graph is not connected
    
    dumpGraph(G);
    dumpGraph(disconnectedG);
    printf("testIsConnected passed.\n");
}

// Main function to run all test cases
int main() {
    testConstructTreeFromArray();
    testBFS();
    testDFS();
    testBFSSearch();
    testIsConnected();
    
    printf("All tests passed successfully.\n");
    return 0;
}
