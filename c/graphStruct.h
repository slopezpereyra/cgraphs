#ifndef P1_ESTRUCTURAGRAFO24_H
#define P1_ESTRUCTURAGRAFO24_H

#include <stdint.h>
#include <stdbool.h>

typedef unsigned int g_flag;
#define C_FLAG (1 << 0)
#define W_FLAG (1 << 1)
#define STD_FLAG (0)

typedef uint32_t u32;
typedef u32 color;

typedef struct {
    u32 x; 
    u32 y; 
    u32 *w;
} Edge;


typedef struct {
    u32 n;              
    u32 m;              
    u32 Δ;          
    u32* _degrees;   
    Edge *_edges;        
    color* _colors;    
    u32* _firstneighbour; 
    bool _formatted;
    g_flag _g_flag;
} Graph;

#endif
