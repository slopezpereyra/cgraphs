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
#include "greedyflow.h"


// Network search 
//

InsertionArray *flowBFS(Graph *G, u32 s, u32 target){
    assert(s != target);
    assert(G->_g_flag == F_FLAG);

    u32 n = numberOfVertices(G);
    u32* visited = genArray(n);
    u32 treeVertexCount = 1; // root included necessarily
    InsertionArray* insertionArray = createInsertionArray(n);

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
                
                insArrayStore(target, v, insertionArray);
                found = true;
                break;
            }
            visited[iNeighbour] = 1; 
            enQueue(Q, iNeighbour);
            insArrayStore(iNeighbour, v, insertionArray);
        }
    }

    dumpQueue(Q);
    free(visited);
    if (!found)
        return NULL;
    return insertionArray;
}


void flowDFSRecursive(u32 v, InsertionArray *track, u32 root, u32 t, bool *flag, Graph *G){
    assert(G->_g_flag == F_FLAG);
    for (u32 i = 0; i < degree(v, G); i++){
        if (*flag)
            return;
        u32 iNeighbour = neighbour(i, v, G);
        if (getRemainingCapacity(v, iNeighbour, G) == 0)
            continue;
        // insArrayGet(index, insArray) is not -1 only if the index has been 
        // previously set, i.e. the vertex has been traversed already
        if (insArrayGet(iNeighbour, track) != -1)
            continue;
        
        insArrayStore(iNeighbour, v, track);
        if (iNeighbour == t){
            *flag = true;
            return;
        }
        flowDFSRecursive(iNeighbour, track, iNeighbour, t, flag, G);
    }
}

InsertionArray *flowDFS(Graph *G, u32 s, u32 target){
    assert(G->_g_flag == F_FLAG);

    bool *flag = (bool *)malloc(sizeof(bool));
    *flag = false;
    u32 n = numberOfVertices(G);
    InsertionArray *insertionArray = createInsertionArray(n);
    insArrayStore(s, n + 1, insertionArray);
    flowDFSRecursive(s, insertionArray, s, target, flag, G);
    if (insArrayGet(target, insertionArray) == -1)
        return NULL;
    return(insertionArray);

}

// Function pointer type for the search functions
// Modify `greedyFlow` to accept a `SearchFunction` parameter
u32 greedyFlow(Graph *N, u32 s, u32 t, SearchFunction searchFunc) {
    assert(N != NULL);
    assert(N->_g_flag == F_FLAG);

    u32 flowValue = 0;

    while (true) {
        // Use the search function pointer to decide between BFS or DFS
        InsertionArray *edgesInPath = searchFunc(N, s, t);
        if (edgesInPath == NULL)
            break;

        printf("\n****************************************\n");
        printInsertionArray(edgesInPath);
        printf("\n****************************************\n");

        u32 v = t;
        u32 flowToSend = INT_MAX;
        u32 w, remainingCapacity;
        
        // Traverse the insertion array to find the maximum flow
        while (v != s) {
            w = insArrayGet(v, edgesInPath);
            Edge e = getEdge(v, w, N);
            remainingCapacity = *e.c - *e.w;
            if (remainingCapacity < flowToSend)
               flowToSend = remainingCapacity;
            v = w;
        }
        // Traverse the insertion array again to update the flow
        v = t;
        flowValue += flowToSend;
        while (v != s) {
            w = insArrayGet(v, edgesInPath);
            Edge e = getEdge(v, w, N);
            increaseEdgeWeight(e.x, e.y, flowToSend, N);
            v = w;
        }
    }
    return(flowValue);
}




















