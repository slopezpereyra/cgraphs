#include <stdio.h>
#include <stdlib.h>

// El .h de abajo debe tener definida Graph, u32 y color.
#include "EstructuraGrafo24.h"

u32* naturalOrder(struct Graph *G);
u32 greedy(struct Graph *G, u32* Order);
bool twoColorable(struct Graph *G);
u32* reverseOrder(struct Graph *G, u32 nColorsUsed);
u32* cardinalityOrder(struct Graph *G, u32 nColorsUsed);
struct Queue** genColorQueues(struct Graph *G, u32 nColorsUsed);
u32* divisibilityOrder(struct Graph *G, u32 nColorsUsed);
