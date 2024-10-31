#ifndef P1_ESTRUCTURAGRAFO24_H
#define P1_ESTRUCTURAGRAFO24_H

#include <stdint.h>

typedef uint32_t u32;
typedef u32 color;


typedef struct {
    u32 x; 
    u32 y; 
} Edge;


typedef struct {
    u32 n;              
    u32 m;              
    u32 Δ;          
    u32* _degrees;   
    Edge *_edges;        
    color* _colors;    
    u32* _firstneighbour; 
} Graph;

#endif
