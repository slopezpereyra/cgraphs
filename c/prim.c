/**
 * @file prim.c
 * @brief An implementation of Prim's algorithm for generating a spanning tree 
 * of a weighted graph which minimizes the sum of the weights of the used edges.
 */

#include "api.h"
#include "utils.h"
#include "wapi.h"
#include "queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

Graph *prim(u32 s, Graph *G){
    assert(G != NULL);
    assert(G->_G_FLAGS & W_FLAG);


    u32 n = numberOfVertices(G);
    u32 *visited = genArray(n);

    struct Queue* Q = createQueue();
    enQueue(Q, s);
    Graph *T = initGraph(n, 0, STD_FLAG);

    u32 nCount = 0;

    while (nCount < n-1){
        nCount++;
        u32 v = pop(Q);
        visited[v] = 1;
      
        // Find closes neighbour
        u32 curWeight = INT_MAX;
        u32 w;
        printf("\nPivoting at %d with w = %d\n", v, w);
        for (u32 i = 0; i < degree(v, G); i++){
            u32 iNeighbour = neighbour(i, v, G);
            if (visited[iNeighbour] != 0)
                continue;
            u32 weight = getEdgeWeight(v, iNeighbour, G);
            enQueue(Q, iNeighbour);
            if (weight < curWeight)
                w = iNeighbour;
        }
        printf("\nSelected neighbour %d\n", w);
        addEdge(T, v, w);
    }

    formatEdges(T);
    return T;
}
