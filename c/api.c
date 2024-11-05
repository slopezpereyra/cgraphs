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


Graph *initGraph(u32 n, u32 m, g_flag flags) {
    Graph *G = (Graph*)malloc(sizeof(Graph));
    if (G == NULL){
        printf("Error: malloc failed\n");
        exit(1);
    }
    G->n = n;
    G->m = m;
    G->Δ = 0;
    G->_edges = (Edge*)calloc(2 * m, sizeof(Edge));
    G->_firstneighbour = (u32*)calloc(n, sizeof(u32));
    G->_degrees = (u32*)calloc(n, sizeof(u32));
    G->_formatted = true;
    G->_g_flag = flags;

    G->_colors = (flags & C_FLAG) ? (u32*)calloc(n, sizeof(u32)) : NULL;
    
    return (G);
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
    Edge *A = (Edge *)a;
    Edge *B = (Edge *)b;

    // Compare first by x values
    if (A->x != B->x)
        return (A->x - B->x);

    // If x values are equal, compare by y values
    return (A->y - B->y);
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
void setEdge(Graph *G, u32 i, u32 x, u32 y, u32 *w, u32 *c) {
    assert(G != NULL);
    assert(i < numberOfEdges(G));
    if (w != NULL) {assert(G->_g_flag & W_FLAG);}
    if (c != NULL) {assert(G->_g_flag & F_FLAG);}

    (G->_edges)[i].x = x;
    (G->_edges)[i].y = y;
    if (w != NULL){
        (G->_edges)[i].w = (u32*)malloc(sizeof(u32));
        *(G->_edges)[i].w = *w;
        (G->_edges)[i + G->m].w = (u32*)malloc(sizeof(u32));
        *(G->_edges)[i + G->m].w = *w;
    }
    if (c != NULL){
        (G->_edges)[i].c = (u32*)malloc(sizeof(u32));
        *(G->_edges)[i].c = *c;
        (G->_edges)[i + G->m].c = (u32*)malloc(sizeof(u32));
        *(G->_edges)[i + G->m].c = *c;
    }
    (G->_edges)[i + G->m].x = y;
    (G->_edges)[i + G->m].y = x;
    (G->_degrees)[x]++;
    (G->_degrees)[y]++;
    (G->Δ) = max(max((G->_degrees)[x], (G->_degrees)[y]), G->Δ);
    G->_formatted = false;
}

bool isFormatted(Graph *G){
    return(G->_formatted);
}


/**
 * @brief Find the position of the edge {x, y} in the _edges array of 
 * a graph G.
 *
 * @return `i` if `E := (G -> _edges)[i]` satisfies `E.x == x` and `E.y == y`.
 */
u32 edgeIndex(Graph *G, u32 x, u32 y){
    assert(isFormatted(G));
    u32 index = (G -> _firstneighbour)[x];
    for (u32 i = 0; i < degree(x, G); i++){
        if (neighbour(i, x, G) == y){
            break;
        }index++;
    }
    return(index);

}

u32 firstNeighbourIndex(Graph *G, u32 x){
    return(G->_firstneighbour[x]);
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
void addEdge(Graph *G, u32 x, u32 y, u32 *w, u32 *c) {
    assert(G != NULL);
    assert(x != y);
    if (w != NULL) {assert(G->_g_flag & W_FLAG);}
    if (c != NULL) {assert(G->_g_flag & F_FLAG);}

    (G->m)++;
    G->_edges = (Edge*)realloc(G->_edges, 2*(G->m) * sizeof(Edge));
    (G->_edges)[2*( G->m )-2].x = x;
    (G->_edges)[2*( G->m )-2].y = y;
    (G->_edges)[2*( G->m )-1].x = y;
    (G->_edges)[2*( G->m )-1].y = x;

    if (w != NULL){
        (G->_edges)[2*( G->m )-2].w = (u32*)malloc(sizeof(u32));
        (G->_edges)[2*( G->m )-1].w = (u32*)malloc(sizeof(u32));
        *((G->_edges)[2*( G->m )-2].w) = *w; 
        *((G->_edges)[2*( G->m )-1].w) = *w; 
    }
    if (c != NULL){
        (G->_edges)[2*( G->m )-2].c = (u32*)malloc(sizeof(u32));
        (G->_edges)[2*( G->m )-1].c = (u32*)malloc(sizeof(u32));
        *((G->_edges)[2*( G->m )-2].c) = *c; 
        *((G->_edges)[2*( G->m )-1].c) = *c; 
    }
   
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
    assert(isFormatted(G));
    assert(x != y);
    assert((G -> m) > 1);

    if (x > y){
        u32 temp = x;
        x = y;
        y = temp;
    }
    
    assert(isNeighbour(x, y, G));
   
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
    g_flag FLAG;
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
    char flag_str[10];
    int matched_format; // Por el ret de fscanf

    // Lectura del FILE hasta p edge
    matched_format = fscanf(file, "%s %u %u %s", edge_str, &n, &m, flag_str);

    if (matched_format < 3) {
        printf("ERROR: No hay match.\n"); // NOTE printConsole
    }

    skipLine(file);
    if (strcmp("edge", edge_str) != 0) {
        return NULL;
    }

    if (strcmp(flag_str, "W_FLAG") == 0) {
        FLAG = W_FLAG;
    }else if (strcmp(flag_str, "F_FLAG") == 0) {
        FLAG = F_FLAG;
    }else if (strcmp(flag_str, "C_FLAG") == 0) {
        FLAG = C_FLAG;
    } else if (strcmp(flag_str, "STD_FLAG") == 0) {
        FLAG = STD_FLAG;
    } else {
        printf("ERROR: Unknown flag '%s'.\n", flag_str);
        return NULL;
    }

    Graph *G = initGraph(n, m, FLAG);
    printf("Initialized\n");

    for (u32 i = 0; i < m; i++) {
        u32 x, y, w, c;
        if (FLAG == F_FLAG){
            if (fscanf(file, "e %u %u %d %d\n", &x, &y, &w, &c) == 4)
                setEdge(G, i, x, y, &w, &c);
            else{

                printf("Failed to read line %d\n", i+1);
                return NULL;
            }
        }
        else if (FLAG & W_FLAG){
            if (fscanf(file, "e %u %u %d\n", &x, &y, &w) == 3)
                setEdge(G, i, x, y, &w, NULL);
            else
                return NULL;
        }else{
            if (fscanf(file, "e %u %u\n", &x, &y) == 2)
                setEdge(G, i, x, y, NULL, NULL);
            else 
                return NULL;
        }
    };

    formatEdges(G);
    fclose(file);

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
    G->_formatted = true;
}

/**
 * @brief Frees all memory associated to a Graph structure.
 *
 * @param G 
 */
void dumpGraph(Graph *G) {
    if (G != NULL) {
        if (G->_g_flag & W_FLAG)
        {
            for (u32 i = 0; i < 2*G->m; i++){
                free(G->_edges[i].w);
            }

        }
        free(G->_edges);
        free(G->_degrees);
        free(G->_firstneighbour);
        if (G->_colors != NULL)
        {
            free(G->_colors);

        }
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
Edge getIthEdge(u32 i, Graph *G) {
    assert(G != NULL && i < 2* numberOfEdges(G));
    return ( G->_edges )[i];
}



/**
 * @brief Return the Edge {x, y}
 *
 */
Edge getEdge(u32 x, u32 y, Graph *G) {
    assert(G != NULL && x <  numberOfVertices(G) && y < numberOfVertices(G));
    assert(isFormatted(G));
    if (x > y)
        swap_u32_pointers(&x, &y);
    u32 i = edgeIndex(G, x, y);
    return (G ->_edges )[i];
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
    assert(isFormatted(G));

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
        Edge e = getIthEdge(i, G);
        if (G -> _g_flag == F_FLAG) 
            printf("%d ~ %d  (%d)  [%d]\n", e.x, e.y, *e.w, *e.c);
        else if (G->_g_flag & W_FLAG)
            printf("%d ~ %d  (%d)\n", e.x, e.y, *e.w);
        else
            printf("%d ~ %d\n", e.x, e.y);
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
        printf("Vertex %d: degree %d - Index in edge array %d\n", i,
               (G->_degrees)[i], (G->_firstneighbour)[i]);
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


// ~~~~~~~~~~~~~~~~~~~ Network flow API ~~~~~~~~~~~~~~~~~~~~~


u32 getEdgeWeight(u32 x, u32 y, Graph *G){
    assert(G != NULL);
    assert(G->_g_flag & W_FLAG);
    return *(getEdge(x, y, G).w);
}


u32 getEdgeCapacity(u32 x, u32 y, Graph *G){
    assert(G != NULL);
    assert(G->_g_flag == F_FLAG);
    return *(getEdge(x, y, G).c);
}


u32 getIthEdgeWeight(u32 i, Graph *G){
    assert(G != NULL);
    assert(G->_g_flag & W_FLAG);
    return *(getIthEdge(i, G).w);
}


u32 getIthEdgeCapacity(u32 i, Graph *G){
    assert(G != NULL);
    assert(G->_g_flag == F_FLAG);
    return *(getIthEdge(i, G).c);
}


void setEdgeWeight(u32 x, u32 y, u32 w, Graph *G){
    assert(G != NULL);
    assert(G->_g_flag & W_FLAG);
    Edge e = getEdge(x, y, G);
    if (G -> _g_flag & F_FLAG)
        assert(w <= *e.c);
    *e.w = w;
}


void increaseEdgeWeight(u32 x, u32 y, u32 delta, Graph *G){
    assert(G != NULL);
    assert(G->_g_flag & W_FLAG);
    Edge e = getEdge(x, y, G);
    if (G -> _g_flag & F_FLAG)
        assert(*e.w + delta <= *e.c);
    *e.w = *e.w + delta;
}


void setEdgeCapacity(u32 x, u32 y, u32 c, Graph *G){
    assert(G != NULL);
    assert(G->_g_flag == F_FLAG);
    *getEdge(x, y, G).c = c;
}


void setIthEdgeWeight(u32 i, u32 w, Graph *G){
    assert(G != NULL);
    assert(G->_g_flag & W_FLAG);
    Edge e = getIthEdge(i, G);
    if (G -> _g_flag & F_FLAG)
        assert(w <= *e.c);
    *e.w = w;
}


void setIthEdgeCapacity(u32 i, u32 c, Graph *G){
    assert(G != NULL);
    assert(G->_g_flag == F_FLAG);
    *getIthEdge(i, G).c = c;
}


u32 getRemainingCapacity(u32 x, u32 y,  Graph *G){
    assert(G != NULL);
    assert(G->_g_flag == F_FLAG);
    Edge e = getEdge(x, y, G);
    return *e.c - *e.w;

}
















