#include "graphStruct.h"

u32* naturalOrder(Graph *G);
u32 greedy(Graph *G, u32* Order);
bool twoColorable(Graph *G);
u32* reverseOrder(Graph *G, u32 nColorsUsed);
u32* cardinalityOrder(Graph *G, u32 nColorsUsed);
struct Queue** genColorQueues(Graph *G, u32 nColorsUsed);
u32* divisibilityOrder(Graph *G, u32 nColorsUsed);
