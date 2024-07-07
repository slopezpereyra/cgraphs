#include "search.h"

#include "queue.h"
#include "APIG24.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// An insertion array A = [v₁, …, vₙ] is s.t. A[i] = vₖ, then vertex (vₖ - 1)
// added vertex i to the tree; i.e. i is a leaf of (vₖ - 1). The values of A are
// increased by one unit to ensure that zero signals non-inclusion in the tree.
Graph constructTreeFromArray(u32* insertionArray, u32 insertionArrayLength, u32 n){
    Graph B = InitGraph(n, n-1);
    u32 edgeIndex = 0;

    for (u32 i = 0; i < insertionArrayLength; i++){
        // If insertionArray[i] == 0, the vertex i is not in the BFS tree.
        if (insertionArray[i] == 0){
            continue;
        }
        AddEdges(B , edgeIndex, insertionArray[i] - 1, i);
        edgeIndex++;
    }
    FormatEdges(B );
    return( B ) ;
}

// BFS : Graph ↦  Graph maps a graph G to its BFS tree 
// ℬ.. 
Graph BFS(Graph G, u32 s){

    u32 n = NumberOfVertices(G);
    // An array s.t. insertionArray[i] = (k+1) iff vertex i was enqueued
    // by vertex k.
    u32* insertionArray = (u32*)calloc(n, sizeof(u32*));
    u32 treeVertexCount = 1; // root included necessarily

    struct Queue* Q = createQueue();
    enQueue(Q, s);

    while (Q->front != NULL){

        u32 v = pop(Q);
        u32 d = Degree(v, G);

        for (u32 i = 0; i < d; i++){
            u32 iNeighbor = Neighbor(i, v, G);
            if (insertionArray[iNeighbor] != 0 || iNeighbor == s){
                continue;
            }
            insertionArray[iNeighbor] = v + 1; 
            treeVertexCount++;
            enQueue(Q, iNeighbor);
        }
    }
    dumpQueue(Q);
    Graph B = constructTreeFromArray(insertionArray, n, treeVertexCount); 
    free(insertionArray);
    return(B);

}

// Recursive DFS traversal using backtracking. Starts the recursion 
// from vertex `v` and keeps `track` of who included each neighbor 
// in an array of n elements. Returns the number of nodes in the tree.
// This is important to deal with graphs with >1 connected components.
u32 DFSRecursive(u32 v, u32* track, u32 root, Graph G){
    u32 n = 1;
    for (u32 i = 0; i < Degree(v, G); i++){
        u32 neighbor = Neighbor(i, v, G);
        if (neighbor == root || track[neighbor] != 0){
            continue;
        }
        track[neighbor] = v + 1;
        n += DFSRecursive(neighbor, track, root, G);
    }
    return n;
}

// Uses RecursiveDFS to span the DFS tree.
Graph DFS(Graph G, u32 s){

    u32 n = NumberOfVertices(G);
    u32 *insertionArray = (u32*)calloc(n, sizeof(u32*));
    u32 treeVertexCount = DFSRecursive(s, insertionArray, s, G);
    Graph D = constructTreeFromArray(insertionArray, n, treeVertexCount); 
    free(insertionArray);
    return(D);

}

// BFS : Graph ↦  Graph maps a graph G to its BFS tree 
// ℬ.. 
bool BFSSearch(Graph G, u32 s, u32 target){
    assert(s != target);

    u32 n = NumberOfVertices(G);
    u32* visited = (u32*)calloc(n, sizeof(u32*));

    struct Queue* Q = createQueue();
    enQueue(Q, s);

    while (Q->front != NULL){

        u32 v = pop(Q);
        u32 d = Degree(v, G);

        for (u32 i = 0; i < d; i++){
            u32 iNeighbor = Neighbor(i, v, G);
            if (iNeighbor == target && v == s){
                continue;
            }
            if (iNeighbor == target){
                dumpQueue(Q);
                free(visited);
                return true;
            }
            if (visited[iNeighbor] != 0 || iNeighbor == s){
                continue;
            }
            visited[iNeighbor] = 1; 
            enQueue(Q, iNeighbor);
        }
    }
    dumpQueue(Q);
    free(visited);
    return false;

}













