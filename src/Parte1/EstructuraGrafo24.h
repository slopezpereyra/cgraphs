#ifndef P1_ESTRUCTURAGRAFO24_H
#define P1_ESTRUCTURAGRAFO24_H

#include <stdint.h>

typedef uint32_t u32;
typedef u32 color;
typedef struct Vertice* vertice; // Puntero al Vertice
typedef struct Lado* lado;       // Puntero al Lado
typedef struct GrafoSt* Grafo;

struct GrafoSt {
    u32 n;              // Numero de vertices del grafo
    u32 m;              // Numero de lados del grafo
    u32 delta;          // Max de grados
    u32 sigma;          // Min de grados
    vertice* _vertices; // Arreglo de punteros a Vertice
    lado* _lados;
};

struct Vertice {
    u32 nombre; // Nombre del vertice
    u32 grado;  // Numero de vecinos
    color color_;
    // Modificar
    u32* Vecinos; // Puntero al indice del primer vecino
};

struct Lado {
    u32 x;
    u32 y;
};

#endif
