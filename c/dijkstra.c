/**
 * @file wapi.c
 * @brief API for weighted graphs.
 */

#include "api.h"
#include "utils.h"
#include "wapi.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

u32 *dijkstra(u32 s, Graph *G){
    assert(G->_G_FLAGS & W_FLAG);

    u32 n = numberOfVertices(G);
    u32 *distances = genArray(n);
    u32 *visited = genArray(n);

    // Initial distances
    for (u32 i = 0; i < n; i++){
        distances[i] = INT_MAX;
    }
    distances[s] = 0;

    while (true){

        u32 v; 
        u32 vDistance = INT_MAX;
        for (u32 w = 0; w < n; w++){
            if (visited[w] != 0 || distances[w] == INT_MAX)
                continue;
            if (distances[w] < vDistance) {
                vDistance = distances[w];
                v = w;
            }
        }
        visited[v] = 1;

        // This only happens if all vertices were visited
        if (vDistance == INT_MAX){
            return distances;
        }

        // Traverse neighbours of v and update its distances 
        for (u32 i = 0; i < degree(v, G); i++){
            u32 iNeighbour = neighbour(i, v, G);
            if (visited[iNeighbour])
                continue;
            u32 weight = getEdgeWeight(v, iNeighbour, G);
            distances[iNeighbour] = min( distances[iNeighbour], vDistance + weight);
        }

    }

}
