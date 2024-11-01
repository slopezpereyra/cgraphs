/**
 * @file wapi.c
 * @brief API for weighted graphs.
 */

#include "api.h"
#include "utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

u32 getEdgeWeight(u32 x, u32 y, Graph *G){
    assert(G->_G_FLAGS & W_FLAG);
    assert(isFormatted(G));
    if (x < y)
        swap_u32_pointers(&x, &y);

    u32 i = edgeIndex(G, x, y);
    u32 w = getIthWeight(i, G);
    return(w);

}

void setEdgeWeight(u32 x, u32 y, u32 w, Graph *G){
    assert(G->_G_FLAGS & W_FLAG);
    assert(isFormatted(G));
    if (x < y)
        swap_u32_pointers(&x, &y);

    u32 i = edgeIndex(G, x, y);
    (G->_weights)[i] = w;
}
