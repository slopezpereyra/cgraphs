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
Graph constructTreeFromArray(u32* insertionArray, u32 n, u32 treeRoot){
    Graph ℬ = InitGraph(n, n-1);
    u32 shift = 0;
    for (u32 i = 0; i < n; i++){
        if (i == treeRoot){
            shift = 1;
            continue;
        }
        AddEdges(ℬ , i - shift, insertionArray[i] - 1, i);
    }
    FormatEdges(ℬ );
    return( ℬ ) ;
}

// BFS : Graph ↦  Graph maps a graph G to its BFS tree 
// ℬ.. 
Graph BFS(Graph G, u32 s){
    
    u32 n = NumberOfVertices(G);
    u32 *insertionArray = (u32*)calloc(n, sizeof(u32*));

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
            enQueue(Q, iNeighbor);
        }

    }
    
    Graph B = constructTreeFromArray(insertionArray, n, s); 
    free(insertionArray);
    free(Q);
    return(B);

}

// Recursive DFS traversal using backtracking. Starts the recursion 
// from vertex `v` and keeps `track` of who included each neighbor 
// in an array of n elements.
void DFSRecursive(u32 v, u32* track, Graph G){
    for (u32 i = 0; i < Degree(v, G); i++){
        u32 neighbor = Neighbor(i, v, G);
        if (track[neighbor] == 0){
            track[neighbor] = v + 1;
            DFSRecursive(neighbor, track, G);
        }
    }
    return;
}

// Uses RecursiveDFS to span the DFS tree.
Graph DFS(Graph G, u32 s){

    u32 n = NumberOfVertices(G);
    u32 *insertionArray = (u32*)calloc(n, sizeof(u32*));
    insertionArray[s] = -1; // nobody insertionArray s
    DFSRecursive(s, insertionArray, G);
    Graph D = constructTreeFromArray(insertionArray, n, s); 
    free(insertionArray);
    return(D);

}















