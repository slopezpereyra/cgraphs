#ifndef api_H
#define api_H

#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
// El .h de abajo debe tener definida Graph, u32 y color.
#include "EstructuraGrafo24.h"


u32 max(u32 x, u32 y);
u32 min(u32 x, u32 y);
void removeEdge(struct Graph *G, u32 x, u32 y);
void addEdge(struct Graph *G, u32 x, u32 y);
bool isNeighbour(u32 x, u32 y, struct Graph *G);
struct Graph * readGraph(char *filename);
struct Graph * initGraph(u32 n, u32 m);
struct Edge * newEdge(u32 x, u32 y);
void setEdge(struct Graph *G, u32 i, u32 x, u32 y);
void formatEdges(struct Graph *G);
int compareEdges(const void* a, const void* b);
void printEdges(struct Graph *G);
void dumpGraph(struct Graph *G);
u32 numberOfVertices(struct Graph *G);
u32 numberOfEdges(struct Graph *G);
u32 Δ(struct Graph *G);
color getColor(u32 i, struct Graph *G);
u32 degree(u32 i, struct Graph *G);
struct Edge getEdge(u32 i, struct Graph *G);
void removeColors(struct Graph *G);
u32 neighbour(u32 j, u32 i, struct Graph *G);
void setColor(color x, u32 i, struct Graph *G);
void printGraph(struct Graph *G);
void writeGraph(struct Graph *G, char* fname);
u32 edgeToIndex(u32 x, u32 y, u32 n);
bool isEdge(struct Graph *G, u32 x, u32 y);
u32 edgeIndex(struct Graph *G, u32 x, u32 y);

#endif
