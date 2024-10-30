#include <stdio.h>
#include <stdlib.h>

#include "EstructuraGrafo24.h"

struct Graph *genCompleteGraph(u32 n);
u32 generate_random_u32();
u32 generate_random_u32_in_range(u32 min, u32 max);
struct Graph *genConnectedGraph(u32 n, u32 m);
struct Graph *genConnectedGraph2(u32 n, u32 m);
struct Graph *fromPruferSequence(u32* seq, u32 seq_len);
u32** genGammaComplements(struct Graph *G);
struct Graph *genCGraph(u32 n, u32 m);
struct Graph *genCGraphUnbound(u32 n);
struct Graph *genConnectedGraphFromKn(u32 n, u32 m);
u32** genGammas(struct Graph *G);
struct Graph *randomTree(u32 n);
