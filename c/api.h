#ifndef api_H
#define api_H

#include "graphStruct.h"
#include <stdbool.h>

u32 max(u32 x, u32 y);
u32 min(u32 x, u32 y);
void removeEdge(Graph *G, u32 x, u32 y);
void addEdge(Graph *G, u32 x, u32 y, u32 *w, u32 *c);
bool isNeighbour(u32 x, u32 y, Graph *G);
Graph *readGraph(char *filename);
Graph *initGraph(u32 n, u32 m, g_flag flags);
void setEdge(Graph *G, u32 i, u32 x, u32 y, u32 *w, u32 *c);
void formatEdges(Graph *G);
int compareEdges(const void *a, const void *b);
void printEdges(Graph *G);
void dumpGraph(Graph *G);
u32 numberOfVertices(Graph *G);
u32 numberOfEdges(Graph *G);
u32 Δ(Graph *G);
color getColor(u32 i, Graph *G);
u32 degree(u32 i, Graph *G);
Edge getIthEdge(u32 i, Graph *G);
void removeColors(Graph *G);
u32 neighbour(u32 j, u32 i, Graph *G);
void setColor(color x, u32 i, Graph *G);
void printGraph(Graph *G);
void writeGraph(Graph *G, char *fname);
u32 edgeIndex(Graph *G, u32 x, u32 y);
Edge getEdge(u32 x, u32 y, Graph *G);
bool isFormatted(Graph *G);
u32 firstNeighbourIndex(Graph *G, u32 x);

/**
 * @brief Retrieves the weight of an edge between two nodes in a graph.
 *
 * @param x The starting node of the edge.
 * @param y The ending node of the edge.
 * @param G Pointer to the Graph structure.
 * @return The weight of the edge between nodes x and y.
 *
 * @pre G must not be NULL.
 * @pre Graph must have the W_FLAG enabled for weighted edges.
 */
u32 getEdgeWeight(u32 x, u32 y, Graph *G);

/**
 * @brief Retrieves the capacity of an edge between two nodes in a graph.
 *
 * @param x The starting node of the edge.
 * @param y The ending node of the edge.
 * @param G Pointer to the Graph structure.
 * @return The capacity of the edge between nodes x and y.
 *
 * @pre G must not be NULL.
 * @pre Graph must have the F_FLAG enabled for capacity values.
 */
u32 getEdgeCapacity(u32 x, u32 y, Graph *G);

/**
 * @brief Retrieves the weight of the i-th edge in the graph.
 *
 * @param i The index of the edge.
 * @param G Pointer to the Graph structure.
 * @return The weight of the i-th edge in the graph.
 *
 * @pre G must not be NULL.
 * @pre Graph must have the W_FLAG enabled for weighted edges.
 */
u32 getIthEdgeWeight(u32 i, Graph *G);

/**
 * @brief Retrieves the capacity of the i-th edge in the graph.
 *
 * @param i The index of the edge.
 * @param G Pointer to the Graph structure.
 * @return The capacity of the i-th edge in the graph.
 *
 * @pre G must not be NULL.
 * @pre Graph must have the W_FLAG enabled for weighted edges.
 */
u32 getIthEdgeCapacity(u32 i, Graph *G);

/**
 * @brief Sets the weight of an edge between two nodes in a graph.
 *
 * @param x The starting node of the edge.
 * @param y The ending node of the edge.
 * @param w The weight to set for the edge.
 * @param G Pointer to the Graph structure.
 *
 * @pre G must not be NULL.
 * @pre Graph must have the W_FLAG enabled for weighted edges.
 * @pre If the F_FLAG is enabled, the weight must not exceed the edge capacity.
 */
void setEdgeWeight(u32 x, u32 y, u32 w, Graph *G);

/**
 * @brief Sets the capacity of an edge between two nodes in a graph.
 *
 * @param x The starting node of the edge.
 * @param y The ending node of the edge.
 * @param c The capacity to set for the edge.
 * @param G Pointer to the Graph structure.
 *
 * @pre G must not be NULL.
 * @pre Graph must have the W_FLAG enabled for weighted edges.
 */
void setEdgeCapacity(u32 x, u32 y, u32 c, Graph *G);

/**
 * @brief Sets the weight of the i-th edge in the graph.
 *
 * @param i The index of the edge.
 * @param w The weight to set for the edge.
 * @param G Pointer to the Graph structure.
 *
 * @pre G must not be NULL.
 * @pre Graph must have the W_FLAG enabled for weighted edges.
 * @pre If the F_FLAG is enabled, the weight must not exceed the edge capacity.
 */
void setIthEdgeWeight(u32 i, u32 w, Graph *G);

/**
 * @brief Sets the capacity of the i-th edge in the graph.
 *
 * @param i The index of the edge.
 * @param c The capacity to set for the edge.
 * @param G Pointer to the Graph structure.
 *
 * @pre G must not be NULL.
 * @pre Graph must have the W_FLAG enabled for weighted edges.
 */
void setIthEdgeCapacity(u32 i, u32 c, Graph *G);

/**
 * @brief Gets the remaining capacity of the edge {x, y} in
 * a network.
 *
 * @param x The starting node of the edge.
 * @param y The ending node of the edge.
 * @param G Pointer to the Graph structure.
 *
 * @pre G must not be NULL.
 * @pre Graph must have the F_FLAG.
 */
u32 getRemainingCapacity(u32 x, u32 y, Graph *G);

void increaseEdgeWeight(u32 x, u32 y, u32 delta, Graph *G);

#endif
