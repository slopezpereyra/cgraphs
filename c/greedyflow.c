/**
 * @file greedyflow.c
 * @brief Greedy algorithm for finding a network flow
 */

#include "api.h"
#include "search.h"
#include "queue.h"
#include "utils.h"
#include "limits.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Network search 
//

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
u32 *flowBFS(Graph *G, u32 s, u32 target){
    assert(s != target);
    assert(G->_g_flag == F_FLAG);

    u32 n = numberOfVertices(G);
    u32* visited = genArray(n);
    u32 treeVertexCount = 1; // root included necessarily
    u32* insertionArray = genArray(n);

    struct Queue* Q = createQueue();
    enQueue(Q, s);
    bool found = 0;

    while (Q->front != NULL && !found){

        u32 v = pop(Q);
        u32 d = degree(v, G);

        for (u32 i = 0; i < d; i++){
            u32 iNeighbour = neighbour(i, v, G);
            if (getRemainingCapacity(v, iNeighbour, G) == 0)
                continue;
            if (visited[iNeighbour] != 0 || iNeighbour == s){
                continue;
            }
            if (iNeighbour == target){
                insertionArray[target] = v;
                found = true;
                break;
            }
            visited[iNeighbour] = 1; 
            enQueue(Q, iNeighbour);
            insertionArray[iNeighbour] = v;
        }
    }

    dumpQueue(Q);
    free(visited);
    if (!found)
        return NULL;
    return insertionArray;
}


void greedyFlow(Graph *N, u32 s, u32 t){


    while (true){

        u32 *edgesInPath = flowBFS(N, s, t);
        if ( edgesInPath == NULL  )
            break;

        u32 v = t;
        u32 w;
        u32 flowToSend = INT_MAX;
        u32 remainingCapacity;
        while (v != s){
            w = edgesInPath[v];
            Edge e = getEdge(v, w, N);
            remainingCapacity = *e.c - *e.w;
            if (remainingCapacity < flowToSend)
               flowToSend = remainingCapacity;
            v = w;
        }
        v = t;
        while (v != s){
            w = edgesInPath[v];
            Edge e = getEdge(v, w, N);
            increaseEdgeWeight(e.x, e.y, flowToSend, N);
            v = w;
        }


    }

}




















