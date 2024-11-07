#ifndef P1_ESTRUCTURAGRAFO24_H
#define P1_ESTRUCTURAGRAFO24_H

#include <stdint.h>
#include <stdbool.h>

typedef unsigned int g_flag;

#define STD_FLAG (0)    // 0000
#define C_FLAG (1 << 0) // 0001
#define W_FLAG (1 << 1) // 0010 
#define D_FLAG (1 << 2) // 0100
#define F_FLAG (W_FLAG | D_FLAG) // 0110

typedef uint32_t u32;
typedef u32 color;

typedef struct {
    u32 x; 
    u32 y; 
    u32 *w; // weight, or distance, or flow in case of flow networks
    u32 *c; //  capacity, a limit for the weight/flow
} Edge;


typedef struct {
    u32 n;              
    u32 m;              
    u32 Δ;          
    u32* _degrees;   
    u32* _outdegrees;   
    u32* _indegrees;   
    Edge *_edges;        
    u32 _edgeArraySize;        
    color* _colors;    
    u32* _firstneighbour; 
    bool _formatted;
    g_flag _g_flag;
} Graph;

#endif
