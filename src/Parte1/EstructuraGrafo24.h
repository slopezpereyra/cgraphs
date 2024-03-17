#ifndef P1_ESTRUCTURAGRAFO24_H
#define P1_ESTRUCTURAGRAFO24_H

# include <stdint.h>

typedef uint32_t u32;

typedef u32 color;

typedef struct GrafoSt {
    u32 numVertices;
    u32 numLados;  // Numero de lados del grafo
    u32 delta;  // Max de grados
    u32 sigma;  // Min de grados
    struct Vertice *Vertices;  // Lista de vertices
};

typedef struct Vertice {
    u32 nombre;  // Nombre del vertice
    u32 grado;  // Numero de vecinos
    u32 **vecinos;  // Lista de vecinos
};

#endif