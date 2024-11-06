#include "api.h"
#include "insertionArray.h"

typedef InsertionArray* (*SearchFunction)(Graph *G, u32 s, u32 target);

InsertionArray *flowBFS(Graph *G, u32 s, u32 target);
InsertionArray *flowDFS(Graph *G, u32 s, u32 target);
u32 greedyFlow(Graph *N, u32 s, u32 t, SearchFunction searchFunc);
