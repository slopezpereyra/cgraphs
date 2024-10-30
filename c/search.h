#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "EstructuraGrafo24.h"

struct Graph *BFS(struct Graph *G, u32 s);
struct Graph *DFS(struct Graph *G, u32 s);
u32 DFSRecursive(u32 v, u32* track, u32 root, struct Graph *G);
bool BFSSearch(struct Graph *G, u32 s, u32 target);
bool isConnected(struct Graph *G);
struct Graph *_constructTreeFromArray(u32* insertionArray, u32 insertionArrayLength, u32 n);
