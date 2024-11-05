#include "api.h"

typedef u32* (*SearchFunction)(Graph *G, u32 s, u32 target);

u32 *flowBFS(Graph *G, u32 s, u32 target);
u32 *flowDFS(Graph *G, u32 s, u32 target);
void greedyFlow(Graph *N, u32 s, u32 t, SearchFunction searchFunc);
