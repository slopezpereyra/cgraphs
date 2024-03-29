#ifndef P1_ESTRUCTURAGRAFO24_H
#define P1_ESTRUCTURAGRAFO24_H

#include <stdint.h>

typedef uint32_t u32;
typedef u32 color;
typedef struct Vertice* vertice; // Puntero al Vertice
typedef struct LadoSt* Lado;     // Puntero al Lado
typedef struct GrafoSt* Grafo;

struct GrafoSt {
    u32 n;              // Numero de vertices del grafo
    u32 m;              // Numero de lados del grafo
    u32 delta;          // Max de grados
    u32* _grados;       // Max de grados
    Lado _lados;        // Arreglo de lados
    color* _colores;    // Arreglo de colores
    u32* _primerVecino; // Indice al primer vecino
};

/**
 * Contiene los lados `xy` e `ye`.
 *
 * Size: `m * 2`
*/
struct LadoSt {
    u32 x; // Nombre del vertice `x` del lado `xy`
    u32 y; // Nombre del vertice `y` del lado `yx`
};

#endif
