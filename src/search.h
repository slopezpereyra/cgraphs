#include <stdio.h>
#include <stdlib.h>

#include "EstructuraGrafo24.h"

Graph BFS(Graph G, u32 s);
Graph DFS(Graph G, u32 s);
void DFSRecursive(u32 v, u32* track, Graph G);
