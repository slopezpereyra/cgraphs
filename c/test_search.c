#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "search.h"
#include "queue.h"
#include "api.h"
#include "utils.h"
#include "search.h"

void testConstructTreeFromInsertionArray() {
    printf("Testing constructTreeFromInsertionArray.\n");
    u32 insertionArray[] = {0, 1, 1, 2, 3}; // Simple parent-child relationship
    u32 n = 5;
    Graph *tree = _TreeFromInsertionArray(insertionArray, 5, n);
    assert(tree != NULL); // Tree should be created
    
    // Verify specific edges
    assert(isNeighbour(0, 1, tree)); // Check root connection
    assert(isNeighbour(0, 2, tree)); // Check middle connection
    assert(isNeighbour(1, 3, tree)); // Check leaf connections
    assert(isNeighbour(2, 4, tree)); // Check leaf connections
    
    dumpGraph(tree);
    printf("test_constructTreeFromInsertionArray passed.\n");
}

// Test BFS traversal to ensure tree structure is correct.
void testBFS() {
    printf("Testing BFS.\n");
    Graph *G = initGraph(5, 4, STD_FLAG); // Create a simple graph with 5 vertices
    setEdge(G, 0, 0, 1, NULL, NULL);
    setEdge(G, 1, 0, 2, NULL, NULL);
    setEdge(G, 2, 1, 3, NULL, NULL);
    setEdge(G, 3, 1, 4, NULL, NULL);
    formatEdges(G);
   
    Graph *BFSResult = BFS(G, 0); // Run BFS from vertex 0
    assert(BFSResult != NULL);

    // Verify BFS tree structure
    assert(isNeighbour(0, 1, BFSResult));
    assert(isNeighbour(0, 2, BFSResult));
    assert(isNeighbour(1, 3, BFSResult));
    assert(isNeighbour(1, 4, BFSResult));

    dumpGraph(G);
    dumpGraph(BFSResult);
    printf("testBFS passed.\n");
}

// Test DFS traversal to ensure tree structure is correct.
void testDFS() {
    printf("Testing DFS.\n");
    Graph *G = initGraph(5, 4, STD_FLAG); // Create a simple graph with 5 vertices
    setEdge(G, 0, 0, 1, NULL, NULL);
    setEdge(G, 1, 0, 2, NULL, NULL);
    setEdge(G, 2, 1, 3, NULL, NULL);
    setEdge(G, 3, 1, 4, NULL, NULL);
    formatEdges(G);
    
    Graph *DFSResult = DFS(G, 0); // Run DFS from vertex 0
    assert(DFSResult != NULL);

    // Verify DFS tree structure
    assert(isNeighbour(0, 1, DFSResult));
    assert(isNeighbour(1, 3, DFSResult) || isNeighbour(1, 4, DFSResult)); // DFS is depth-prioritized
    
    dumpGraph(DFSResult);
    dumpGraph(G);
    printf("testDFS passed.\n");
}

// Test BFSSearch to check if the target vertex can be found in the graph.
void testBFSSearch() {
    Graph *G = initGraph(5, 4, STD_FLAG);
    setEdge(G, 0, 0, 1, NULL, NULL);
    setEdge(G, 1, 1, 2, NULL, NULL);
    setEdge(G, 2, 2, 3, NULL, NULL);
    setEdge(G, 3, 0, 0, NULL, NULL);
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
    Graph *G = initGraph(4, 3, STD_FLAG);
    setEdge(G, 0, 0, 1, NULL, NULL);
    setEdge(G, 1, 1, 2, NULL, NULL);
    setEdge(G, 2, 2, 3, NULL, NULL);
    formatEdges(G);

    assert(isConnected(G) == true); // Graph is connected
    
    Graph *disconnectedG = initGraph(4, 2, STD_FLAG);
    setEdge(disconnectedG, 0, 0, 0, NULL, NULL);
    formatEdges(disconnectedG);

    assert(isConnected(disconnectedG) == false); // Graph is not connected
    
    dumpGraph(G);
    dumpGraph(disconnectedG);
    printf("testIsConnected passed.\n");
}

// Main function to run all test cases
int main() {
    testConstructTreeFromInsertionArray();
    testBFS();
    testDFS();
    testBFSSearch();
    testIsConnected();
    
    printf("All tests passed successfully.\n");
    return 0;
}
