/** MIT License
 *
 * Copyright (c) 2024 Santiago López Pereyra
 *
 * santiagolopezpereyra@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * The software is provided "as is", without warranty of any kind, express or
 * implied, including but not limited to the warranties of merchantability,
 * fitness for a particular purpose, and noninfringement. In no event shall the
 * authors or copyright holders be liable for any claim, damages, or other
 * liability, whether in an action of contract, tort, or otherwise, arising from,
 * out of or in connection with the software or the use or other dealings in the
 * software.
 */






#include "api.h"
#include "insertionArray.h"

typedef InsertionArray *(*SearchFunction)(Graph *G, u32 s, u32 target);

/**
 * @brief Performs a breadth-first search (BFS) on a flow network graph from a
 * source vertex to a target vertex.
 *
 * @param G Pointer to the flow network graph.
 * @param s The source vertex.
 * @param target The target vertex.
 * @return Pointer to an InsertionArray containing the path from source to
 * target if found, or NULL if no path exists.
 *
 * This function executes a BFS on the graph to find an augmenting path in a
 * flow network. It uses a queue to explore each vertex's neighbors and checks
 * for available capacity on each edge. The result is stored in an
 * InsertionArray which represents the path, if one is found.
 */
InsertionArray *flowBFS(Graph *G, u32 s, u32 target);

/**
 * @brief Recursively performs depth-first search (DFS) on a flow network graph
 * to find a path from the source to the target.
 *
 * @param v The current vertex being visited.
 * @param track Pointer to an InsertionArray that tracks the path from source to
 * target.
 * @param root The starting vertex for the DFS search.
 * @param t The target vertex to be reached.
 * @param flag Pointer to a boolean that signals whether the target has been
 * found.
 * @param G Pointer to the flow network graph.
 *
 * This recursive function navigates through each neighbor of the current
 * vertex, verifying available capacity on each edge, and stores the path in an
 * InsertionArray if a path to the target exists.
 */
void flowDFSRecursive(u32 v, InsertionArray *track, u32 root, u32 t, bool *flag,
                      Graph *G);

/**
 * @brief Initiates a depth-first search (DFS) on a flow network graph from a
 * source vertex to a target vertex.
 *
 * @param G Pointer to the flow network graph.
 * @param s The source vertex.
 * @param target The target vertex.
 * @return Pointer to an InsertionArray containing the path from source to
 * target if found, or NULL if no path exists.
 *
 * This function calls the recursive flowDFSRecursive function to perform DFS
 * and track the path from the source vertex to the target vertex. If a path is
 * found, it is stored in an InsertionArray and returned. Otherwise, it returns
 * NULL.
 */
InsertionArray *flowDFS(Graph *G, u32 s, u32 target);

/**
 * @typedef SearchFunction
 * @brief A function pointer type for search functions used in the greedyFlow
 * function.
 *
 * This function pointer allows either the flowBFS or flowDFS function to be
 * used as the path-finding method.
 */

/**
 * @brief Computes the maximum flow in a flow network graph using a search
 * function for path finding.
 *
 * @param N Pointer to the flow network graph.
 * @param s The source vertex.
 * @param t The target vertex.
 * @param searchFunc Pointer to the search function (either flowBFS or flowDFS)
 * to be used for finding paths.
 * @return The maximum flow value from source to target.
 *
 * This function computes the maximum flow in a graph by repeatedly finding
 * augmenting paths between the source and target vertices using the specified
 * search function. The flow along each found path is added to the total flow
 * and the graph's edges are updated accordingly.
 */
u32 greedyFlow(Graph *N, u32 s, u32 t, SearchFunction searchFunc);
