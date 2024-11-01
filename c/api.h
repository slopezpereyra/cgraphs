#ifndef api_H
#define api_H

#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
// El .h de abajo debe tener definida Graph, u32 y color.
#include "graphStruct.h"


u32 max(u32 x, u32 y);
u32 min(u32 x, u32 y);
void removeEdge(Graph *G, u32 x, u32 y);
void addEdge(Graph *G, u32 x, u32 y);
bool isNeighbour(u32 x, u32 y, Graph *G);
Graph * readGraph(char *filename);
Graph * initGraph(u32 n, u32 m);
Edge * newEdge(u32 x, u32 y);
void setEdge(Graph *G, u32 i, u32 x, u32 y);
void formatEdges(Graph *G);
int compareEdges(const void* a, const void* b);
void printEdges(Graph *G);
void dumpGraph(Graph *G);
u32 numberOfVertices(Graph *G);
u32 numberOfEdges(Graph *G);
u32 Δ(Graph *G);
color getColor(u32 i, Graph *G);
u32 degree(u32 i, Graph *G);
Edge getEdge(u32 i, Graph *G);
void removeColors(Graph *G);
u32 neighbour(u32 j, u32 i, Graph *G);
void setColor(color x, u32 i, Graph *G);
void printGraph(Graph *G);
void writeGraph(Graph *G, char* fname);
u32 edgeToIndex(u32 x, u32 y, u32 n);
u32 edgeIndex(Graph *G, u32 x, u32 y);

#endif
