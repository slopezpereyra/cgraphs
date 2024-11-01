/**
 * @file search.c
 * @brief Functions for graph traversal and tree construction in a BFS and DFS context.
 */

#include "search.h"

#include "queue.h"
#include "api.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

/**
 * @brief Constructs a BFS tree from an insertion array. This is a private function.
 *
 * Creates a tree where each vertex `i` is connected as a leaf of vertex `(insertionArray[i] - 1)`.
 * Insertion array values are incremented by one to differentiate included vertices from non-included ones.
 *
 * @param[in] insertionArray Array indicating the parent for each vertex in the tree.
 * @param[in] insertionArrayLength Length of the insertion array.
 * @param[in] n Total number of vertices in the graph.
 * @return A pointer to the constructed Graph structure.
 */
Graph *_constructTreeFromArray(u32* insertionArray, u32 insertionArrayLength, u32 n){
    Graph * B = initGraph(n, n-1, STD_FLAG);
    u32 edgeIndex = 0;

    for (u32 i = 0; i < insertionArrayLength; i++){
        // If insertionArray[i] == 0, the vertex i is not in the BFS tree.
        if (insertionArray[i] == 0){
            continue;
        }
        setEdge(B , edgeIndex, insertionArray[i] - 1, i);
        edgeIndex++;
    }
    formatEdges(B );
    return( B ) ;
}

/**
 * @brief Builds a Breadth-First Search (BFS) tree from a given graph.
 *
 * Performs a BFS traversal on graph `G`, starting from vertex `s`, and constructs a BFS tree.
 *
 * @param[in] G Pointer to the original graph.
 * @param[in] s Starting vertex for the BFS traversal.
 * @return A pointer to the Graph structure representing the BFS tree.
 */
Graph *BFS(Graph *G, u32 s){

    u32 n = numberOfVertices(G);
    // An array s.t. insertionArray[i] = (k+1) iff vertex i was enqueued
    // by vertex k.
    u32* insertionArray = genArray(n);
    u32 treeVertexCount = 1; // root included necessarily

    struct Queue* Q = createQueue();
    enQueue(Q, s);

    while (Q->front != NULL){

        u32 v = pop(Q);
        u32 d = degree(v, G);

        for (u32 i = 0; i < d; i++){
            u32 iNeighbour = neighbour(i, v, G);
            if (insertionArray[iNeighbour] != 0 || iNeighbour == s){
                continue;
            }
            insertionArray[iNeighbour] = v + 1; 
            treeVertexCount++;
            enQueue(Q, iNeighbour);
        }
    }
    dumpQueue(Q);
    Graph *B = _constructTreeFromArray(insertionArray, n, treeVertexCount); 
    free(insertionArray);
    return(B);

}

/**
 * @brief Recursive helper function for Depth-First Search (DFS).
 *
 * Traverses a graph recursively from a starting vertex `v`, updating the `track` array to record
 * parent vertices and counting the number of nodes in the DFS tree. Useful for managing multiple connected components.
 *
 * @param[in] v Current vertex in the traversal.
 * @param[out] track Array tracking the parent of each vertex.
 * @param[in] root Initial root vertex of the DFS traversal.
 * @param[in] G Pointer to the graph being traversed.
 * @return Number of vertices in the DFS tree.
 */
u32 DFSRecursive(u32 v, u32* track, u32 root, Graph *G){
    u32 n = 1;
    for (u32 i = 0; i < degree(v, G); i++){
        u32 iNeighbour = neighbour(i, v, G);
        if (iNeighbour == root || track[iNeighbour] != 0){
            continue;
        }
        track[iNeighbour] = v + 1;
        n += DFSRecursive(iNeighbour, track, root, G);
    }
    return n;
}

/**
 * @brief Builds a Depth-First Search (DFS) tree from a given graph.
 *
 * Uses a recursive DFS approach to traverse graph `G` from vertex `s` and construct a DFS tree.
 *
 * @param[in] G Pointer to the original graph.
 * @param[in] s Starting vertex for the DFS traversal.
 * @return A pointer to the Graph structure representing the DFS tree.
 */
Graph *DFS(Graph *G, u32 s){

    u32 n = numberOfVertices(G);
    u32 *insertionArray = genArray(n);
    u32 treeVertexCount = DFSRecursive(s, insertionArray, s, G);
    Graph *D = _constructTreeFromArray(insertionArray, n, treeVertexCount); 
    free(insertionArray);
    return(D);

}

/**
 * @brief Searches for a target vertex in a graph using Breadth-First Search (BFS).
 *
 * Performs a BFS search on graph `G` starting from vertex `s` to find the `target` vertex.
 *
 * @param[in] G Pointer to the graph.
 * @param[in] s Starting vertex for the search.
 * @param[in] target Vertex being searched for.
 * @return `true` if the target vertex is found, `false` otherwise.
 */
bool BFSSearch(Graph *G, u32 s, u32 target){
    assert(s != target);

    u32 n = numberOfVertices(G);
    u32* visited = genArray(n);

    struct Queue* Q = createQueue();
    enQueue(Q, s);

    while (Q->front != NULL){

        u32 v = pop(Q);
        u32 d = degree(v, G);

        for (u32 i = 0; i < d; i++){
            u32 iNeighbour = neighbour(i, v, G);
            // If this vertex was visited already or is the root, continue
            if (visited[iNeighbour] != 0 || iNeighbour == s){
                continue;
            }
//            // If it is the target we are pivoting on the root
//            if (iNeighbour == target && v == s){
//                continue;
//            }
            if (iNeighbour == target){
                dumpQueue(Q);
                free(visited);
                return true;
            }
            visited[iNeighbour] = 1; 
            enQueue(Q, iNeighbour);
        }
    }
    dumpQueue(Q);
    free(visited);
    return false;

}

/**
 * @brief Checks if a graph is connected.
 *
 * Determines if the graph `G` is fully connected by performing a BFS traversal
 * from vertex 0 and counting reachable nodes.
 *
 * @param[in] G Pointer to the graph.
 * @return `true` if the graph is connected, `false` otherwise.
 */
bool isConnected(Graph *G){

    u32 n = numberOfVertices(G);
    u32* insertionArray = genArray(n);
    u32 treeVertexCount = 1; // root included necessarily

    struct Queue* Q = createQueue();
    enQueue(Q, 0);

    while (Q->front != NULL){

        u32 v = pop(Q);
        u32 d = degree(v, G);

        for (u32 i = 0; i < d; i++){
            u32 iNeighbour = neighbour(i, v, G);
            if (insertionArray[iNeighbour] != 0 || iNeighbour == 0){
                continue;
            }
            insertionArray[iNeighbour] = v + 1; 
            treeVertexCount++;
            enQueue(Q, iNeighbour);
        }
    }
    dumpQueue(Q);

    return (n == treeVertexCount);


}


