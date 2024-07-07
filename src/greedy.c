#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "greedy.h"
#include "APIG24.h"
#include "queue.h"



// Comparison function for qsort to sort in descending order by color
int compareColor(const void *a, const void *b, void *arg) {
    u32 index_a = *(const u32 *)a;
    u32 index_b = *(const u32 *)b;
    Graph graph = (Graph )arg;

    // Sort by color in descending order
    if (graph->_colors[index_a] < graph->_colors[index_b]) {
        return 1;
    } else if (graph->_colors[index_a] > graph->_colors[index_b]) {
        return -1;
    } else {
        return 0;
    }
}

u32* NaturalOrder(Graph G){

    u32* order = (u32*)calloc(NumberOfVertices(G), sizeof(u32));
    for (u32 i = 0; i < NumberOfVertices(G); i++){
        order[i] = i;
    }
    return(order);
}

// The Greedy part of the algorithm (deciding the coloring) is done 
// by traversing all edges twice:
// 
//                      ∑ d(x) = 2m  
//
// Its complexity is O(2m) = O(m).
//
// But we reset usedColorsDyn[i] = 0 ∀i exactly `n` times. 
//
// Final complexity of coloring: O(m + n).
//
// Because we are interested in the number of colors used, we added a final 
// operation of complexity O(Δ + 1) = O(Δ) = O(n-1) = O(2m) = O(m).
//
// Then the total complexity is 
//
//                      O(m + n) + O(m) = O(m+n)
//
//
u32 Greedy(Graph G, u32 *Order){
        
    u32* usedColorsDyn = (u32*)calloc(Δ(G) + 1, sizeof(u32));
    u32* usedColorsStatic = (u32*)calloc(Δ(G) + 1, sizeof(u32));
    u32 colorsUsed = 0;

    for (u32 i = 0; i < NumberOfVertices(G); i++) {

        u32 v = Order[i];
        u32 d = Degree(v, G);

        for (u32 j = 0; j < d; j++){
            u32 jNeighbour = Neighbor(j, v, G);
            color jNeighbourColor = (G -> _colors)[jNeighbour];
            if (jNeighbourColor != 0){
                usedColorsDyn[jNeighbourColor - 1] = 1; // color j is the (j-1)th color 
                                                     // colors range from {1, ..., Δ + 1}
                                                     // but usedColorsDyn from {0, ..., Δ}
            }
        }

        int colored = 0;
        for (u32 j = 0; j < Δ(G) + 1; j++){
            if (usedColorsDyn[j] == 0 && colored != 1){
                (G -> _colors)[v] = j + 1;
                if (usedColorsStatic[j] == 0){
                    usedColorsStatic[j] = 1; 
                }
                colored = 1;
            }
            usedColorsDyn[j] = 0;
        }
    }
    for (u32 i = 0; i < Δ(G) + 1; i++){
        if (usedColorsStatic[i] == 1){ colorsUsed++; }
    }
    free(usedColorsDyn);
    free(usedColorsStatic);
    return(colorsUsed);
}

bool twoColorable(Graph G){

    struct Queue* Q = createQueue();
    enQueue(Q, 0);
    setColor(1, 0, G);

    while (!isEmpty(Q)){
        u32 pivot = pop(Q);
        u32 pivotColor = getColor(pivot, G);
        u32 degree = Degree(pivot, G);
        for (u32 i = 0; i < degree; i++){
            u32 iNeighbor = Neighbor(i, pivot, G);
            if (getColor(iNeighbor, G) == 0){
                enQueue(Q, iNeighbor);
                setColor(3 - pivotColor, iNeighbor, G);
            }
            if (getColor(iNeighbor, G) == pivotColor){
                dumpQueue(Q);
                return false;
            }
        }
    }
    dumpQueue(Q);
    return true;
}

struct Queue** genColorQueues(Graph G, u32 nColorsUsed){
    struct Queue** D = (struct Queue**) calloc(nColorsUsed, sizeof(struct Queue**));

    for (u32 i = 0; i < nColorsUsed; i++){
        D[i] = createQueue();
    }

    for (u32 i = 0; i < NumberOfVertices(G); i++){
        color c = getColor(i, G);
        struct Queue * q = D[c-1];
        enQueue(q, i);
    }

    return D;
}

u32* unfoldColorQueues(Graph G, u32 nColorsUsed, struct Queue** D){
    u32* order = (u32*)calloc(NumberOfVertices(G), sizeof(u32));
    u32 j = NumberOfVertices(G) - 1;
    for (u32 i = 0; i < nColorsUsed; i++){
        struct Queue * q = D[i];
        while (q -> front != NULL){
            u32 x = pop(q);
            order[j] = x;
            j--;
        }
        free(q);
    }

    free(D);
    return(order);
}


u32* cardinalityOrder(Graph G, u32 nColorsUsed){
    struct Queue** D = genColorQueues(G, nColorsUsed);
    qsort(D, nColorsUsed, sizeof(struct Queue*), compareQueue);
    return ( unfoldColorQueues(G, nColorsUsed, D) );
}

u32* reverseOrder(Graph G, u32 nColorsUsed){

    struct Queue** D = genColorQueues(G, nColorsUsed);
    return( unfoldColorQueues(G, nColorsUsed, D) );


}

u32* divisibilityOrder(Graph G, u32 nColorsUsed){

    struct Queue** D = genColorQueues(G, nColorsUsed);
    u32 nColorsDivisibleByFour = 0;
    u32 nColorsDivisibleByTwo = 0;

    for (u32 i = 0; i < nColorsUsed; i++){
        struct Queue * q = D[i];
        if (( i+1 ) % 4 == 0){
           nColorsDivisibleByFour += q->count; 
        }else if (( i+1 ) % 2 == 0 ){
           nColorsDivisibleByTwo += q->count; 
        }
    }

    u32* order = (u32*)calloc(NumberOfVertices(G), sizeof(u32));
    u32 u = 0, v = 0, w = 0;
    for (u32 i = 0; i < nColorsUsed; i++){
        struct Queue * q = D[i];
        u32 color = i + 1;
        while (q -> front != NULL){
            u32 x = pop(q);
            u32 index;
            if (color % 4 == 0){
                index = u;
                u++;
            }
            else if (color % 2 == 0){
                index = nColorsDivisibleByFour + v;
                v++;
            }
            else{
                index = nColorsDivisibleByFour + nColorsDivisibleByTwo + w;
                w++;
            }
            order[index] = x;
        }
        dumpQueue(q);
    }

    free(D);
    return(order);
    

}














