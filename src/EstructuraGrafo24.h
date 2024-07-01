#ifndef P1_ESTRUCTURAGRAFO24_H
#define P1_ESTRUCTURAGRAFO24_H

#include <stdint.h>

typedef uint32_t u32;
typedef u32 color;
typedef struct Vertex* vertex; // Puntero al Vertice
typedef struct EdgeSt* Edge;     // Puntero al Edge
typedef struct GraphSt* Graph;
typedef struct EdgeSt* Pair;

struct GraphSt {
    u32 n;              // Numero de vertices del grafo.
    u32 m;              // Numero de lados del grafo.
    u32 Δ;          // Max de degrees. 
    u32 δ;          // Max de degrees. 
    u32* _degrees;       // Arreglo de degrees. Size `n`.
    Edge _edges;        // Arreglo de lados. Size `m*2`.
    color* _colors;    // Arreglo de colors. Size `n`.
    u32* _firstNeighbor; // An array s.t. _firstNeighbor[i] is the index of the first first neighbor of vertex `i`.
};

/**
 * Contiene los lados `xy` e `ye`.
 *
 * Size: `m * 2`
*/
struct EdgeSt {
    u32 x; // Nombre del vertice `x` del lado `xy`.
    u32 y; // Nombre del vertice `y` del lado `yx`.
};

#endif
