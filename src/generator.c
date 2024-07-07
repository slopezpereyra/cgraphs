#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "greedy.h"
#include "APIG24.h"
#include "queue.h"
#include "search.h"
#include <time.h>
#include <stdlib.h>

void removeElement(u32 *array, u32 *size, u32 index) {
    if (*size == 0 || index >= *size) {
        return; // If array is empty or index is out of bounds, do nothing
    }

    // Shift elements to the left starting from index
    for (u32 i = index; i < *size - 1; i++) {
        (array)[i] = (array)[i + 1];
    }

    // Decrease the size of the array
    *size -= 1;

    // Reallocate memory to shrink the array
    array = (u32*)realloc(array, (*size) * sizeof(u32));
}

u32 generate_random_u32() {
    u32 random_num = ((u32)rand() << 16) | (u32)rand();
    return random_num;
}

u32 generate_random_u32_in_range(u32 min, u32 max) {
    u32 range = max - min + 1;
    u32 limit = UINT32_MAX - (UINT32_MAX % range);
    u32 random_num;

    do {
        random_num = generate_random_u32();
    } while (random_num >= limit);

    return (random_num % range) + min;
}

Graph genCompleteGraph(u32 n){

    Graph G = InitGraph(n, n*(n-1)/2);
    u32 edgeIndex = 0;
    for (u32 i = 0; i < n; i++){
        for (u32 j = 1+i; j < n; j++){
            AddEdges(G, edgeIndex, i, j);
            edgeIndex++;
        }
    }
    FormatEdges(G);
    return(G);

}

u32 edgeToIndex(u32 x, u32 y, u32 n){
    u32 xIndex = x*n - (x*(x+1)/2);
    return xIndex + (y - (x+1));
}

Graph genConnectedGraph(u32 n, u32 m){
   
    u32 M = n*(n-1)/2; 
    Graph Kn = genCompleteGraph(n);
    u32 *chosen = (u32*)calloc(M, sizeof(u32));
    u32 edgesToChoseFrom = M;

    for (u32 i = 0; i < M; i++){
        chosen[i] = i;
    }

    while (NumberOfEdges(Kn) > m){
        if (edgesToChoseFrom == 0){
            printf("No more edges to choose from, failed to create connected graph from the choices made\n");
            break;
        } 
        u32 choice = generate_random_u32_in_range(0, edgesToChoseFrom);
        removeElement(chosen, &edgesToChoseFrom, choice);
        u32 v = (Kn ->_edges)[choice].x, w = (Kn ->_edges)[choice].y;
        u32 x = min(v, w), y = max(v, w);
        if ((Degree(x, Kn) == 1 || Degree(w, Kn) == 1)){
            continue;
        }

        if (!BFSSearch(Kn, x, y)){
            continue;
        }

        removeEdge(Kn, x, y);
        

    }
    FormatEdges(Kn);
    return(Kn);
}


// 0 -> 1 
// 0 -> 2 
// 0 -> 3 
// 1 -> 0 
// 1 -> 2  
// 1 -> 3 
// 2 -> 0 
// 2 -> 1 
// 2 -> 3

















