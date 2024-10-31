/**
 * @file api.c
 * @brief API for the Graph struct, including creating, formatting, printing, and writing graphs.
 */

#include "api.h"
#include "utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/**
 * @brief Allocate a new Edge between vertices `x` and `y`. 
 *
 * The values `x` and `y` are abstract, i.e. they do not relate to 
 * any particular graph.
 *
 * @param `u32` x 
 * @param `u32 y  
 * @return A pointer to the allocated Edge.
 */
Edge * newEdge(u32 x, u32 y){
    Edge *e = (Edge*) malloc(sizeof(Edge));
    if (e == NULL){
        printf("Error: malloc failed\n");
        exit(1);
    }
    e -> x = x;
    e -> y = y;
    return(e);
}


/**
 * @brief Test if {x, y} ∈ E(G).
 *
 *
 * @return `true` if `{x, y} ∈ E(G)`, `false` otherwise.
 */
bool isNeighbour(u32 x, u32 y, Graph *G){
    for (u32 i = 0; i < degree(x, G); i++){
        if (neighbour(i,x, G) == y){
            return(true);
        }
    }
    return(false);
}

/**
 * @brief Define an order between Edge structs.
 * 
 * If (a, b) and (x, y) are the fields of two edges E₁, E₂
 * respectively, we say E₁ < E₂ if a < x, or if 
 * a = x but b < y. 
 *
 * We say E₁ = E₂ if a = x, y = b.
 *
 */
int compareEdges(const void* a, const void* b) {
    Edge *ladoA = (Edge *)a;
    Edge *ladoB = (Edge *)b;

    // Compare first by x values
    if (ladoA->x != ladoB->x)
        return (ladoA->x - ladoB->x);

    // If x values are equal, compare by y values
    return (ladoA->y - ladoB->y);
}

/**
 * @brief Allocates and initializes a Graph structure with `n` vertices
 * and `m` edges.
 *
 * The `m` edges are allocated with `calloc` and thus their `{x, y}` values
 * are set to zero. Informally, this means that, after initializing G,
 * E(G) = {{0, 0}, {0, 0}, ..., {0, 0}} - were we take the liberty of speaking
 * of a set with repeated elements.
 * 
 * The color, first neighbor and degree of all vertices is of course also set to
 * zero.
 *
 * Importantly, the callocated `_edges` array contains 2m structs edges, because
 * for each edge {x, y} in the graph we also store an edge {y, x}.
 *
 * @return A pointer to the allocated Graph structure.
 */
Graph *initGraph(u32 n, u32 m) {
    Graph *G = (Graph*)malloc(sizeof(Graph));
    if (G == NULL){
        printf("Error: malloc failed\n");
        exit(1);
    }
    G->n = n;
    G->m = m;
    G->Δ = 0;
    G->_firstneighbour = (u32*)calloc(n, sizeof(u32));
    G->_degrees = (u32*)calloc(n, sizeof(u32));
    G->_colors = (u32*)calloc(n, sizeof(u32));
    G->_edges = (Edge*)calloc(2 * m, sizeof(Edge));
    return (G);
}

/**
 * @brief Set the `x` and `y` fields of the ith Edge structure of `G` to the
 * parameters `x` and `y`.
 *
 * If `m` is the number of edges in the graph, this function also sets
 * the (i + m)th edge structure to represent {y, x}.
 *
 * Upon setting an edge, the degree of the involved vertices and Δ
 * are updated.
 *
 * @note formatEdges(G) should be called after setting edges. It is not 
 *       included in the function because setEdges is typically called 
 *       several times repeatedly, and formatEdges(G) should be called 
 *       once after all these calls for efficiency.
 *
 */
void setEdge(Graph *G, u32 i, u32 x, u32 y) {
    assert(G != NULL);

    // If the edge was previously set, reduce 
    if ((G -> _edges)[i].x != 0){
        u32 old_x = (G -> _edges)[i].x;
        u32 old_y = (G -> _edges)[i].y;
        (G->_degrees)[old_x]--;
        (G->_degrees)[old_y]--;
        (G->Δ) = max(max((G->_degrees)[old_x], (G->_degrees)[old_y]), G->Δ);
    }
    (G->_edges)[i].x = x;
    (G->_edges)[i].y = y;
    (G->_edges)[i + G->m].x = y;
    (G->_edges)[i + G->m].y = x;
    (G->_degrees)[x]++;
    (G->_degrees)[y]++;
    (G->Δ) = max(max((G->_degrees)[x], (G->_degrees)[y]), G->Δ);
}


/**
 * @brief Find the position of the edge {x, y} in the _edges array of 
 * a graph G.
 *
 * @return `i` if `E := (G -> _edges)[i]` satisfies `E.x == x` and `E.y == y`.
 */
u32 edgeIndex(Graph *G, u32 x, u32 y){
    u32 index = (G -> _firstneighbour)[x];
    for (u32 i = 0; i < degree(x, G); i++){
        if (neighbour(i, x, G) == y){
            break;
        }index++;
    }
    return(index);

}

/**
 * @brief Add the new edge {x, y} to a Graph.
 *
 * This function reallocates the memory assigned to `G -> _edges` to include 
 * two extra `Edge struct` (which accounts for one extra edge in the graph).
 * The Edge structs' fields are set to {x, y} and {y, x}. The whole array 
 * of edges is reformatted to place the edges at their correct locations.
 *
 * @param G 
 * @param x 
 * @param y 
 */
void addEdge(Graph *G, u32 x, u32 y) {
    assert(x < y);
    
    (G->m)++;
    G->_edges = (Edge*)realloc(G->_edges, 2*(G->m) * sizeof(Edge));
    (G->_edges)[2*( G->m )-2].x = x;
    (G->_edges)[2*( G->m )-2].y = y;
    (G->_edges)[2*( G->m )-1].x = y;
    (G->_edges)[2*( G->m )-1].y = x;
   
    (G->_degrees)[x]++;
    (G->_degrees)[y]++;
    (G -> Δ) = max( G -> Δ, max((G->_degrees)[x], (G->_degrees)[y])  );
    if ((G->_edges) == NULL) {
        printf("Error: Realloc failed\n");
        exit(1);
    }
    formatEdges(G);
}

/**
 * @brief Remove the edge {x, y} from a Graph.
 *
 * This function removes the two Edge structs corresponding to the edge {x, y}
 * from a Graph's array of Edge structs, reallocating its assigned memory.
 * The whole array of of edges is reformatted to place the remaining edges at
 * their correct locations. The degrees of vertices `x` and `y` are adjusted 
 * as well as `G -> m` are adjusted.
 *
 */
void removeEdge(Graph *G, u32 x, u32 y) {
    assert(x < y);
    assert((G -> m) > 1);
   
    u32 index1 = edgeIndex(G, x, y);
    u32 index2 = edgeIndex(G, y, x) - 1;
    for (u32 i = index1; i < 2*(G -> m)-1; i++) {
        (G->_edges)[i] = (G->_edges)[i + 1];
    }
    for (u32 i = index2; i < 2*(G -> m) - 1; i++) {
            (G->_edges)[i] = (G->_edges)[i + 1];
    }
    (G->m)--;
    Edge *temp = (Edge *)realloc(G->_edges, 2 * (G->m) * sizeof(Edge));
    if (temp == NULL && 2 * (G->m) > 0) {
        exit(1);
    }
    G->_edges = temp;
    (G->_degrees)[x]--;
    (G->_degrees)[y]--;
    if ((G->_edges) == NULL) {
        printf("Error: Realloc failed\n");
        exit(1);
    }
    formatEdges(G);
}

/**
 * @brief Helper function. Reads a file until a new line character is found.
 *
 */
static void skipLine(FILE* file) {
    while (getc(file) != '\n') {
        continue;
    }
}

/**
 * @brief Builds a graph from a .txt file in the Penazzi format, specified in the docs.
 * The file is read from standard input.
 *
 * @return A pointer to the built Graph struct.
 */
Graph * readGraph(char *filename) {
    u32 n;              
    u32 m;             
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    char c;
    while (1) {
        c = getc(file);
        if (c == 'c') {
            skipLine(file);
        } else {
            break;
        }
    }

    // Corrupted file format
    if (c != 'p') {
        return NULL;
    }

    // Asignamos 6: 4 char para edge, 1 para \0
    // y 1 para chequear si esta mal la linea.
    char edge_str[6];
    int matched_format; // Por el ret de fscanf

    // Lectura del FILE hasta p edge
    matched_format = fscanf(file, "%s %u %u", edge_str, &n, &m);

    if (matched_format < 3) {
        printf("ERROR: No hay match.\n"); // NOTE printConsole
    }

    skipLine(file);
    if (strcmp("edge", edge_str) != 0) {
        return NULL;
    }

    Graph *G = initGraph(n, m);

    for (u32 i = 0; i < m; i++) {
        u32 x, y;
        if (scanf("e %u %u\n", &x, &y) == 2) {
            setEdge(G, i, x, y);
        } else {
            return NULL; // Caso de error devuelvo NULL
        }
    };

    formatEdges(G);

    return G;
}


/**
 * @brief Format the edges of a Graph struct, ordering them and setting the `_firstneighbour`
 * field of all vertices.
 *
 * After this function is executed, edges are sorted and each vertex `x` points to 
 * 
 * λ = min ⱼ { y : {x, y} ∈ E(G) }
 *
 */
void formatEdges(Graph *G){
    qsort(G->_edges, 2 * (G->m), sizeof(Edge), compareEdges);
    for (u32 j = 1; j < (G->n); j++) {
        (G->_firstneighbour)[j] = (G->_firstneighbour[j - 1]) + (G->_degrees)[j - 1];
    };
}

/**
 * @brief Frees all memory associated to a Graph structure.
 *
 * @param G 
 */
void dumpGraph(Graph *G) {
    if (G != NULL) {
        free(G->_edges);
        free(G->_degrees);
        free(G->_colors);
        free(G->_firstneighbour);
        free(G);
    }
}

/**
 * @brief Return the number of vertices in the graph.
 *
 */
u32 numberOfVertices(Graph *G) {
    assert(G != NULL);
    return G->n;
}


/**
 * @brief Return the number of edges in the graph.
 *
 */
u32 numberOfEdges(Graph *G) {
    assert(G != NULL);
    return G->m;
}

/**
 * @brief Return the maximum degree of the graph.
 *
 */
u32 Δ(Graph *G) {
    assert(G != NULL);
    return G->Δ;
}


/**
 * @brief Return the degree of the ith edge.
 *
 */
u32 degree(u32 i, Graph *G) {
    assert(G != NULL);
    if (i < G->n) {
        return (G->_degrees)[i];
    }
    return 0;
}

/**
 * @brief Return the color of vertex `i`.
 *
 */
color getColor(u32 i, Graph *G) {
    assert(G != NULL);
    if (i < G->n) {
        // NOTE: `i` es el nombre, y coincide con el indice.
        return G->_colors[i];
    }
    // printf("Index out of bounds en Color(): Devolviendo 2^32  -1"); // NOTE printConsole
    return 4294967295; // 2^32 - 1 Revisar tipo para devolver! :)
}

/**
 * @brief Return the `i`th edge of the graph.
 *
 */
Edge getEdge(u32 i, Graph *G) {
    assert(G != NULL && i < 2* numberOfEdges(G));
    return ( G->_edges )[i];
}

/**
 * @brief Return true if {x, y} ∈ E(G), false otherwise.
 *
 */
bool isEdge(Graph *G, u32 x, u32 y) {
    assert(G != NULL && x < numberOfVertices(G) && y < numberOfVertices(G));
    for (u32 i = 0; i < 2*numberOfEdges(G); i++){
        Edge e = (G->_edges)[i];
        if ((e.x == x && e.y == y) || (e.x == y && e.y == x)){
            return true;
        }
    }
    return false;
}


/**
 * @brief Converts an edge (x, y) to its corresponding index.
 * 
 * @param x The starting vertex.
 * @param y The ending vertex.
 * @param n The total number of vertices.
 * @return The index corresponding to the edge.
 */
u32 edgeToIndex(u32 x, u32 y, u32 n) {
    u32 xIndex = x*n - (x*(x+1)/2);
    return xIndex + (y - (x+1));
}

/**
 * @brief Set all colors in the graph to zero.
 *
 */
void removeColors(Graph *G) {
    for (u32 i = 0; i < G -> n; i++){
        (G -> _colors)[i] = 0;
    }
}

/**
 * @brief Get the `j`th neighbour of vertex `i`, if it exists. 
 *
 * Upon failing returns 2^32 - 1. 
 *
 */
u32 neighbour(u32 j, u32 i, Graph *G) {
    assert(G != NULL);

    if (j >= degree(i, G) || i >= numberOfVertices(G)) {
         printf(
             "Index out of bounds en neighbour(): devolviendo 2^32 -1; "
                "Arguments were: j = %d, i = %d\n",
                j, i);      // NOTE printConsole
        return 4294967295; // 2^32 - 1
    }
    u32 indexDei = (G->_firstneighbour)[i];
    return ((G->_edges)[j + indexDei].y);
}


/**
 * @brief Sets to `x` the color of vertex `i`.
 *
 */
void setColor(color x, u32 i, Graph *G) {
    assert(G != NULL);
    if (i >= numberOfVertices(G)) {
        return;
    }
    (G->_colors)[i] = x;
}


/**
 * @brief Prints all edges in the graph.
 *
 */
void printEdges(Graph *G) {
    assert(G != NULL);
    printf("\nEdges:\n");
    for (u32 i = 0; i < 2 * (G->m); i++) {
        printf("%d ~ %d\n", G->_edges[i].x, G->_edges[i].y);
    };
}

/**
 * @brief Prints the relevant information of each vertex: its degree, 
 * its color and its index in the array of Edges.
 *
 */
void printVertices(Graph *G) {
    assert(G != NULL);
    printf("\nVertices:\n");
    for (u32 i = 0; i < G->n; i++) {
        printf("Vértice %d: degree %d - Índice en lista de lados %d  - Color: %d\n", i,
               (G->_degrees)[i], (G->_firstneighbour)[i], G->_colors[i]);
    };
}

/**
 * @brief Prints relevant information of a Graph struct:
 * its min and max degrees, number of vertices and edges, 
 * vertex information and edges. 
 *
 */
void printGraph(Graph *G) {
    assert(G != NULL);
    printf("\nn = %d\n", G->n);
    printf("m = %d\n", G->m);
    printf("Δ = %d\n\n", G->Δ);
    printVertices(G);
    printEdges(G);
}

/**
 * @brief Writes a graph in Penazzi format into a file 
 * of name `fname`.
 *
 */
void writeGraph(Graph *G, char* fname){
    assert(G != NULL);
    FILE *f = fopen(fname, "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f, "p %d  %d\n", G->n, G->m);
    for (u32 i = 0; i < 2 * (G->m); i++) {
        fprintf(f, "e %d  %d\n", G->_edges[i].x, G->_edges[i].y);
    };
    fclose(f);
}

