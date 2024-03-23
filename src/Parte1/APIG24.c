#include "APIG24.h"

#include <stdio.h>
#include <stdlib.h>

u32 NumeroDeVertices(Grafo G) {
    return 0;
}

u32 NumeroDeLados(Grafo G) {
    return 0;
}

u32 Delta(Grafo G) {
    return G->delta;
}

u32 Grado(u32 i, Grafo G){
    return 0;
}

color Color(u32 i, Grafo G){
    return 0;
}

u32 Vecino(u32 j, u32 i, Grafo G){
    return 0;
}

u32 Hashv(u32 x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

// u32 UnHashv() {
//     x = ((x >> 16) ^ x) * 0x119de1f3;
//     x = ((x >> 16) ^ x) * 0x119de1f3;
//     x = (x >> 16) ^ x;
//     return x;
// }

u32 Hashl(u32 x, u32 y) {
    return 0;
}