#include "search.h"

#include "queue.h"
#include "APIG24.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// BFS : Graph ↦  Graph maps a graph G to its BFS tree 
// ℬ.. 
Graph BFS(Graph G, u32 s){

    u32 m = 0;
    u32 *added = (u32*)calloc(NumberOfVertices(G), sizeof(u32*));

    struct Queue* Q = createQueue();
    enQueue(Q, s);
    

    while (Q->front != NULL){

        u32 v = pop(Q);
        u32 d = Degree(v, G);

        for (u32 i = 0; i < d; i++){
            u32 iNeighbor = Neighbor(i, v, G);
            if (added[iNeighbor] != 0 || iNeighbor == s){
                continue;
            }
            added[iNeighbor] = v + 1; // ensure non-zero predecessor for all added neighbors
            m++;
            enQueue(Q, iNeighbor);
        }

    }
    Graph ℬ = InitGraph(NumberOfVertices(G), m);
    for (u32 i = 0; i < NumberOfVertices(G); i++){
        if (i == s){
            continue;
        }
        AddEdges(ℬ, i, i, added[i] - 1);
    }
    FormatEdges(ℬ );
    return( ℬ ) ;



}

