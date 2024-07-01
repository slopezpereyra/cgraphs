#include "greedy.h"

#include "APIG24.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


