#include <stdio.h>
#include <stdlib.h>

// El .h de abajo debe tener definida GraphSt, u32 y color.
#include "EstructuraGrafo24.h"

u32* NaturalOrder(Graph G);
u32 Greedy(Graph G, u32* Order);
bool twoColorable(Graph G);
u32* reverseOrder(Graph G, u32 nColorsUsed);
u32* cardinalityOrder(Graph G, u32 nColorsUsed);
struct Queue** genColorQueues(Graph G, u32 nColorsUsed);
u32* divisibilityOrder(Graph G, u32 nColorsUsed);
