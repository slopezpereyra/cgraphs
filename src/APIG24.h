#ifndef APIG24_H
#define APIG24_H

#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
// El .h de abajo debe tener definida GraphSt, u32 y color.
#include "EstructuraGrafo24.h"


u32 max(u32 x, u32 y);
u32 min(u32 x, u32 y);
void removeEdge(Graph G, u32 x, u32 y);
void addEdge(Graph G, u32 x, u32 y);
bool isNeighbour(u32 x, u32 y, Graph G);
Graph buildGraph();
Graph initGraph(u32 n, u32 m);
Edge newEdge(u32 x, u32 y);
void AddEdges(Graph G, u32 i, u32 x, u32 y);
void formatEdges(Graph G);
int compareEdges(const void* a, const void* b);
void printEdges(Graph G);
void dumpGraph(Graph G);
u32 numberOfVertices(Graph G);
u32 numberOfEdges(Graph G);
u32 Δ(Graph G);
color getColor(u32 i, Graph G);
u32 degree(u32 i, Graph G);
struct EdgeSt getEdge(u32 i, Graph G);
void removeColors(Graph G);
u32 neighbour(u32 j, u32 i, Graph G);
void setColor(color x, u32 i, Graph G);
void extractColors(Graph G, color* Color);
void printGraph(Graph G);

#endif
