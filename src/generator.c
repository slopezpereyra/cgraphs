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

    while (NumberOfEdges(Kn) > m){
        u32 v = generate_random_u32_in_range(0, n), w = generate_random_u32_in_range(0, n);
        u32 x = min(v, w), y = max(v, w);
        u32 edgeIndex = edgeToIndex(x, y, n);
        if (v == w || (Degree(x, Kn) == 1 || Degree(w, Kn) == 1) || chosen[edgeIndex] != 0){
            continue;
        }

        chosen[edgeIndex] = 1;

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

















