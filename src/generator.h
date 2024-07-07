#include <stdio.h>
#include <stdlib.h>

#include "EstructuraGrafo24.h"

Graph genCompleteGraph(u32 n);
u32 generate_random_u32();
u32 generate_random_u32_in_range(u32 min, u32 max);
u32 edgeToIndex(u32 x, u32 y, u32 n);
Graph genConnectedGraph(u32 n, u32 m);