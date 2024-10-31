#include <stdio.h>
#include <stdlib.h>

#include "graphStruct.h"

Graph *genCompleteGraph(u32 n);
u32 generate_random_u32();
u32 generate_random_u32_in_range(u32 min, u32 max);
Graph *genConnectedGraph(u32 n, u32 m);
Graph *genConnectedGraph2(u32 n, u32 m);
Graph *fromPruferSequence(u32* seq, u32 seq_len);
u32** genGammaComplements(Graph *G);
Graph *genFromRandomTree(u32 n, u32 m);
Graph *genCGraphUnbound(u32 n);
Graph *genFromKn(u32 n, u32 m);
u32** genGammas(Graph *G);
Graph *randomTree(u32 n);
