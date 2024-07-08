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
    assert(*size != 0 && index < *size);
    // Shift elements to the left starting from index
    for (u32 i = index; i < *size - 1; i++) {
        (array)[i] = (array)[i + 1];
    }

    // Decrease the *size of the array
    *size -= 1;

    // Reallocate memory to shrink the array
    array = (u32*)realloc(array, (*size) * sizeof(u32));
}

void removeTargetElement(u32 *array, u32 *size, u32 target) {
    for (u32 i = 0; i < *size; i++) {
        if (array[i] == target) {
            removeElement(array, size, i);
            break;
        }
    }
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
    u32 *S = (u32*)calloc(M, sizeof(u32));
    u32 nCandidates = M;

    for (u32 i = 0; i < M; i++){
        S[i] = i;
    }

    while (NumberOfEdges(Kn) > m){
        if (nCandidates == 0){
            break;
        } 
        u32 choice = generate_random_u32_in_range(0, nCandidates);
        removeElement(S, &nCandidates, choice);
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

bool genConnectedRecursive(u32 m, u32 *S, u32 nCandidates, Graph K, u32 x, u32 y){

    // If this is a removing branch
    if (x != y){
        if (!BFSSearch(K, x, y)){
            return false;
        }
        if ( (K -> m) == m ){
            return true;
        }
    }

    if ((K->m) - m > nCandidates){
        return false;
    }

    if (nCandidates <= 0){
        return false;
    }


    // Choose random element
    u32 choice = generate_random_u32_in_range(0, nCandidates);
    removeElement(S, &nCandidates, choice);

    u32 v = (K ->_edges)[choice].x, w = (K ->_edges)[choice].y;
    x = min(v, w), y = max(v, w);
    if (Degree(x, K) == 1 || Degree(y, K) == 1){
        return(genConnectedRecursive(m, S, nCandidates, K, 0, 0));
    }
    removeEdge(K, x, y);


    if (genConnectedRecursive(m, S, nCandidates, K, x, y)){
        return(true);
    }else{
        //Backtrack
        addEdge(K, x, y);
        return(genConnectedRecursive(m, S, nCandidates, K, 0, 0));
    }
    

}

Graph genConnectedGraph2(u32 n, u32 m){
   
    u32 M = n*(n-1)/2; 
    Graph K = genCompleteGraph(n);
    u32 *S = (u32*)calloc(M, sizeof(u32));
    u32 nCandidates = M;
    bool generated = 0;


    while (!generated){
        generated = genConnectedRecursive(m, S, nCandidates, K, 0, 0);
    }
    FormatEdges(K);
    return(K);
}

Graph fromPruferSequence(u32* seq, u32 seq_len){

    u32 n = seq_len + 2;
    u32* degrees = (u32*)calloc(n, sizeof(u32));
    Graph T = InitGraph(n, 0); 

    for (u32 i = 0; i < n; i++){
        degrees[i] = 1;
    }

    for (u32 i = 0; i < seq_len; i++){
        u32 v = seq[i];
        degrees[v]++;
    }

    for (u32 i = 0; i < seq_len; i++){
        u32 v = seq[i];
        for (u32 j = 0; i < n; j++){
            if (degrees[j] == 1){
                addEdge(T, min(v, j), max(v, j));
                degrees[v]--;
                degrees[j]--;
                break;
            }
        }
    }

    u32 u = 0, v = 0;
    for (u32 i = 0; i < n; i++){
        if (degrees[i] == 1){
            if (u == 0){
                u = i;
            }else{
                v = i;
                break;
            }
        }
    }

    addEdge(T, min(u, v), max(u, v));
    return(T);

}

u32** genGammaComplements(Graph G){

    u32 n = G->n;
    u32** S = (u32**)calloc(n, sizeof(u32*));

    for (u32 i = 0; i < NumberOfVertices(G); i++){

        u32 d = Degree(i, G);
        u32* iGammaComplement = (u32*)calloc(n - d - 1, sizeof(u32));
        u32 jIndex = 0;
        for (u32 j = 0; j < n; j++){
            if (isNeighbor(j, i, G) || i == j){
                continue;
            }
            iGammaComplement[jIndex] = j;
            jIndex++;
        }
        S[i] = iGammaComplement;
    }
    return(S);
}

Graph genConnectedGraphFromST(u32 n, u32 m){
    assert(m <= n*(n-1)/2);

    u32* randSequence = (u32*)calloc(n-2, sizeof(u32));
    for (u32 i = 0; i < n - 2; i++){
        randSequence[i] = generate_random_u32_in_range(0, n-1);
    }

    Graph T = fromPruferSequence(randSequence, n-2);
    free(randSequence);
    u32** S = genGammaComplements(T); // S = { Γ(x)ᶜ : x ∈ V }
    // How many potential new neighbors each vertex has
    u32* nCandidates = (u32*)calloc(n, sizeof(u32));
    u32* vMatchable = (u32*)calloc(n, sizeof(u32));

    for (u32 i = 0; i < n; i++){
        nCandidates[i] = n - Degree(i, T) - 1;
        vMatchable[i] = i;
    }

    u32 nMatchable = n;
    while (NumberOfEdges(T) < m){
        u32 vIndex = generate_random_u32_in_range(0, nMatchable - 1);
        u32 v = vMatchable[vIndex];
        if (nCandidates[v] == 0){
            removeElement(vMatchable, &nMatchable, vIndex);
            continue;
        }
        u32 i = generate_random_u32_in_range(0, nCandidates[v] - 1);
        u32 w = S[v][i];
        removeElement(S[v], &( nCandidates[v] ), i);
        removeTargetElement(S[w], &( nCandidates[w] ), v);
        addEdge(T, min(v, w), max(v, w));
    }
    free(nCandidates);
    free(S);
    free(vMatchable);
    return(T);
}












