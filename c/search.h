#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graphStruct.h"

Graph *BFS(Graph *G, u32 s);
Graph *DFS(Graph *G, u32 s);
u32 DFSRecursive(u32 v, u32* track, u32 root, Graph *G);
bool BFSSearch(Graph *G, u32 s, u32 target);
bool isConnected(Graph *G);
Graph *_constructTreeFromArray(u32* insertionArray, u32 insertionArrayLength, u32 n);
