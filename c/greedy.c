/**
 * @file coloring.c
 * @brief Graph coloring and order generation functions.
 */

#include "api.h"
#include "coloring.h"
#include "queue.h"
#include "utils.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Comparison function for qsort to sort vertices in descending order by
 * color.
 * @param a Pointer to the first element to compare.
 * @param b Pointer to the second element to compare.
 * @param arg Pointer to the graph structure.
 * @return 1 if color of a < color of b, -1 if color of a > color of b, 0 if
 * equal.
 */
int compareColor(const void *a, const void *b, void *arg) {
  u32 index_a = *(const u32 *)a;
  u32 index_b = *(const u32 *)b;
  Graph *graph = (Graph *)arg;

  if (graph->_colors[index_a] < graph->_colors[index_b]) {
    return 1;
  } else if (graph->_colors[index_a] > graph->_colors[index_b]) {
    return -1;
  } else {
    return 0;
  }
}

/**
 * @brief Generates a natural ordering of the vertices in a graph.
 * @param G Pointer to the graph.
 * @return Array containing the natural order of vertices.
 */
u32 *naturalOrder(Graph *G) {
  u32 *order = genArray(numberOfVertices(G));
  for (u32 i = 0; i < numberOfVertices(G); i++) {
    order[i] = i;
  }
  return order;
}

/**
 * @brief Colors the graph using a greedy coloring algorithm.
 *
 * The algorithm iterates over the vertices, assigning the smallest available
 * color to each vertex based on the colors of its neighbors.
 *
 * @param G Pointer to the graph.
 * @param Order Array containing the order of vertices for coloring.
 * @return The number of colors used to color the graph.
 */
u32 greedy(Graph *G, u32 *Order) {
  u32 *usedColorsDyn = genArray(Δ(G) + 1);
  u32 *usedColorsStatic = genArray(Δ(G) + 1);
  u32 colorsUsed = 0;

  for (u32 i = 0; i < numberOfVertices(G); i++) {
    u32 v = Order[i];
    u32 d = degree(v, G);

    for (u32 j = 0; j < d; j++) {
      u32 jNeighbour = neighbour(j, v, G);
      color jNeighbourColor = (G->_colors)[jNeighbour];
      if (jNeighbourColor != 0) {
        usedColorsDyn[jNeighbourColor - 1] = 1;
      }
    }

    bool colored = false;
    for (u32 j = 0; j < Δ(G) + 1; j++) {
      if (usedColorsDyn[j] == 0 && !colored) {
        (G->_colors)[v] = j + 1;
        if (usedColorsStatic[j] == 0) {
          usedColorsStatic[j] = 1;
        }
        colored = true;
      }
      usedColorsDyn[j] = 0;
    }
  }

  for (u32 i = 0; i < Δ(G) + 1; i++) {
    if (usedColorsStatic[i] == 1) {
      colorsUsed++;
    }
  }
  free(usedColorsDyn);
  free(usedColorsStatic);
  return colorsUsed;
}

/**
 * @brief Checks if a graph is two-colorable.
 *
 * This function uses a BFS traversal to check if the graph can be colored with
 * two colors.
 * @param G Pointer to the graph.
 * @return True if the graph is two-colorable, false otherwise.
 */
bool twoColorable(Graph *G) {
  struct Queue *Q = createQueue();
  enQueue(Q, 0);
  setColor(1, 0, G);

  while (!isEmpty(Q)) {
    u32 pivot = pop(Q);
    u32 pivotColor = getColor(pivot, G);
    u32 d = degree(pivot, G);
    for (u32 i = 0; i < d; i++) {
      u32 iNeighbour = neighbour(i, pivot, G);
      if (getColor(iNeighbour, G) == 0) {
        enQueue(Q, iNeighbour);
        setColor(3 - pivotColor, iNeighbour, G);
      }
      if (getColor(iNeighbour, G) == pivotColor) {
        dumpQueue(Q);
        return false;
      }
    }
  }
  dumpQueue(Q);
  return true;
}

/**
 * @brief Generates queues of vertices, grouped by color.
 * @param G Pointer to the graph.
 * @param nColorsUsed Number of colors used in the graph.
 * @return Array of queues, each queue containing vertices of a specific color.
 */
struct Queue **genColorQueues(Graph *G, u32 nColorsUsed) {
  struct Queue **D =
      (struct Queue **)calloc(nColorsUsed, sizeof(struct Queue **));
  if (D == NULL) {
    printf("Error: calloc failed\n");
    exit(1);
  }

  for (u32 i = 0; i < nColorsUsed; i++) {
    D[i] = createQueue();
  }

  for (u32 i = 0; i < numberOfVertices(G); i++) {
    color c = getColor(i, G);
    struct Queue *q = D[c - 1];
    enQueue(q, i);
  }

  return D;
}

/**
 * @brief Unfolds color queues into an ordered array of vertices.
 *
 * This function creates an array of vertices sorted by their color queues.
 * @param G Pointer to the graph.
 * @param nColorsUsed Number of colors used in the graph.
 * @param D Array of queues, each queue containing vertices of a specific color.
 * @return Array of vertices ordered by color.
 */
u32 *unfoldColorQueues(Graph *G, u32 nColorsUsed, struct Queue **D) {
  u32 *order = genArray(numberOfVertices(G));
  u32 j = numberOfVertices(G) - 1;
  for (u32 i = 0; i < nColorsUsed; i++) {
    struct Queue *q = D[i];
    while (q->front != NULL) {
      u32 x = pop(q);
      order[j] = x;
      j--;
    }
    free(q);
  }

  free(D);
  return order;
}

/**
 * @brief Generates a vertex order based on the cardinality of each color queue.
 * @param G Pointer to the graph.
 * @param nColorsUsed Number of colors used in the graph.
 * @return Array of vertices ordered by color queue cardinality.
 */
u32 *cardinalityOrder(Graph *G, u32 nColorsUsed) {
  struct Queue **D = genColorQueues(G, nColorsUsed);
  qsort(D, nColorsUsed, sizeof(struct Queue *), compareQueue);
  return unfoldColorQueues(G, nColorsUsed, D);
}

/**
 * @brief Generates a reverse order of vertices based on color queues.
 * @param G Pointer to the graph.
 * @param nColorsUsed Number of colors used in the graph.
 * @return Array of vertices in reverse order by color queues.
 */
u32 *reverseOrder(Graph *G, u32 nColorsUsed) {
  struct Queue **D = genColorQueues(G, nColorsUsed);
  return unfoldColorQueues(G, nColorsUsed, D);
}

/**
 * @brief Generates an order of vertices based on color divisibility.
 *
 * Vertices are grouped based on divisibility of their color: divisible by 4,
 * divisible by 2, and all other colors.
 *
 * @param G Pointer to the graph.
 * @param nColorsUsed Number of colors used in the graph.
 * @return Array of vertices ordered by divisibility of colors.
 */
u32 *divisibilityOrder(Graph *G, u32 nColorsUsed) {
  struct Queue **D = genColorQueues(G, nColorsUsed);
  u32 nColorsDivisibleByFour = 0;
  u32 nColorsDivisibleByTwo = 0;

  for (u32 i = 0; i < nColorsUsed; i++) {
    struct Queue *q = D[i];
    if ((i + 1) % 4 == 0) {
      nColorsDivisibleByFour += q->count;
    } else if ((i + 1) % 2 == 0) {
      nColorsDivisibleByTwo += q->count;
    }
  }

  u32 *order = genArray(numberOfVertices(G));
  u32 u = 0, v = 0, w = 0;
  for (u32 i = 0; i < nColorsUsed; i++) {
    struct Queue *q = D[i];
    u32 color = i + 1;
    while (q->front != NULL) {
      u32 x = pop(q);
      u32 index;
      if (color % 4 == 0) {
        index = u;
        u++;
      } else if (color % 2 == 0) {
        index = nColorsDivisibleByFour + v;
        v++;
      } else {
        index = nColorsDivisibleByFour + nColorsDivisibleByTwo + w;
        w++;
      }
      order[index] = x;
    }
    dumpQueue(q);
  }

  free(D);
  return order;
}
