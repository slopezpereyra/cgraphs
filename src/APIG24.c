#include "APIG24.h"
#include "utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Edge newEdge(u32 x, u32 y){
    Edge e = (Edge) malloc(sizeof(struct EdgeSt));
    if (e == NULL){
        printf("Error: malloc failed\n");
        exit(1);
    }
    e -> x = x;
    e -> y = y;
    return(e);
}

bool isNeighbour(u32 x, u32 y, Graph G){
    for (u32 i = 0; i < degree(x, G); i++){
        if (neighbour(i,x, G) == y){
            return(true);
        }
    }
    return(false);
}

int compareEdges(const void* a, const void* b) {
    Edge ladoA = (Edge)a;
    Edge ladoB = (Edge)b;

    // Compare first by x values
    if (ladoA->x != ladoB->x)
        return (ladoA->x - ladoB->x);

    // If x values are equal, compare by y values
    return (ladoA->y - ladoB->y);
}

/**
 * Inicializa un grafo de n vértices y m lados.
 */
Graph initGraph(u32 n, u32 m) {
    Graph G = (Graph)malloc(sizeof(struct GraphSt));
    if (G == NULL){
        printf("Error: malloc failed\n");
        exit(1);
    }
    G->n = n;
    G->m = m;
    G->Δ = 0;
    G->δ = 1024;
    G->_firstneighbour = (u32*)calloc(n, sizeof(u32));
    G->_degrees = (u32*)calloc(n, sizeof(u32));
    G->_colors = (u32*)calloc(n, sizeof(u32));
    G->_edges = (Edge)calloc(2 * m, sizeof(struct EdgeSt));
    return (G);
}

/**
 * Dado un grafo `G` y nombres de vértices `x` e `y`, agrega en la
 * i-écima posición de `G -> _edges` el x ~ y. Posteriormente,
 * agrega en la "posición espejo" al lado y ~ x. Finalmente, aumenta
 * los degrees de los lados involcurados en uno y recalcula Δ.
 */
void AddEdges(Graph G, u32 i, u32 x, u32 y) {
    assert(G != NULL);
    // Setear el lado x ~ y
    (G->_edges)[i].x = x;
    (G->_edges)[i].y = y;
    // Setear el lado y ~ x
    (G->_edges)[i + G->m].x = y;
    (G->_edges)[i + G->m].y = x;
    (G->_degrees)[x]++;
    (G->_degrees)[y]++;
    (G->Δ) = max(max((G->_degrees)[x], (G->_degrees)[y]), G->Δ);
    (G->δ) = min(min((G->_degrees)[x], (G->_degrees)[y]), G->δ);
}

u32 edgeIndex(Graph G, u32 x, u32 y){
    u32 index = (G -> _firstneighbour)[x];
    for (u32 i = 0; i < degree(x, G); i++){
        if (neighbour(i, x, G) == y){
            break;
        }index++;
    }
    return(index);

}

void addEdge(Graph G, u32 x, u32 y) {
    assert(x < y);
    
    (G->m)++;
    G->_edges = (Edge)realloc(G->_edges, 2*(G->m) * sizeof(struct EdgeSt));
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

void removeEdge(Graph G, u32 x, u32 y) {
    assert(x < y);
   
    u32 index1 = edgeIndex(G, x, y);
    u32 index2 = edgeIndex(G, y, x) - 1;
    for (u32 i = index1; i < 2*(G -> m)-1; i++) {
        (G->_edges)[i] = (G->_edges)[i + 1];
    }
    for (u32 i = index2; i < 2*(G -> m) - 1; i++) {
            (G->_edges)[i] = (G->_edges)[i + 1];
    }
    (G->m)--;
    Edge temp = (Edge)realloc(G->_edges, 2 * (G->m) * sizeof(struct EdgeSt));
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
 * Lee un file hasta encontrar un `\n`.
 */
static void skipLine(FILE* file) {
    while (getc(file) != '\n') {
        continue;
    }
}

/**
 * Construye un grafo desde una .txt file dada en standard input. Hace los
 * siguientes pasos:
 *    - Inicialización del grafo.
 *    - Scaneo línea por línea, agregando los lados al grafo.
 *    - Quick sort sobre los lados.
 *    - Setea el firstneighbour de cada vértice.
 */
Graph buildGraph() {
    u32 n;              // Cant. Vertices
    u32 m;              // Cant. Edges
    FILE* file = stdin; // Standard input

    char c;
    while (1) {
        c = getc(file);
        if (c == 'c') {
            skipLine(file);
        } else {
            break;
        }
    }

    // Esta mal el formato del archivo.
    if (c != 'p') {
        // printf("\nMal formato de archivo.\n"); // NOTE printConsole
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
        // printf("ERROR: No hay match en edge.\n"); // NOTE printConsole
        return NULL;
    }

    Graph G = initGraph(n, m);

    for (u32 i = 0; i < m; i++) {
        u32 x, y;
        if (scanf("e %u %u\n", &x, &y) == 2) {
            AddEdges(G, i, x, y);
        } else {
            // printf("Error leyendo los lados del grafo.\n"); // NOTE printConsole
            return NULL; // Caso de error devuelvo NULL
        }
    };

    formatEdges(G);

    return G;
}

void formatEdges(Graph G){
    qsort(G->_edges, 2 * (G->m), sizeof(struct EdgeSt), compareEdges);
    for (u32 j = 1; j < (G->n); j++) {
        (G->_firstneighbour)[j] = (G->_firstneighbour[j - 1]) + (G->_degrees)[j - 1];
    };
}

void dumpGraph(Graph G) {
    if (G != NULL) {
        free(G->_edges);
        free(G->_degrees);
        free(G->_colors);
        free(G->_firstneighbour);
        free(G);
    }
}

u32 numberOfVertices(Graph G) {
    assert(G != NULL);
    return G->n;
}

u32 numberOfEdges(Graph G) {
    assert(G != NULL);
    return G->m;
}

u32 Δ(Graph G) {
    assert(G != NULL);
    return G->Δ;
}

u32 δ(Graph G) {
    assert(G != NULL);
    return G->δ;
}

u32 degree(u32 i, Graph G) {
    assert(G != NULL);
    if (i < G->n) {
        return (G->_degrees)[i];
    }
    return 0;
}

color getColor(u32 i, Graph G) {
    assert(G != NULL);
    if (i < G->n) {
        // NOTE: `i` es el nombre, y coincide con el indice.
        return G->_colors[i];
    }
    // printf("Index out of bounds en Color(): Devolviendo 2^32  -1"); // NOTE printConsole
    return 4294967295; // 2^32 - 1 Revisar tipo para devolver! :)
}

struct EdgeSt getEdge(u32 i, Graph G) {
    assert(G != NULL && i < 2* numberOfEdges(G));
    return ( G->_edges )[i];
}

void removeColors(Graph G) {
    for (u32 i = 0; i < G -> n; i++){
        (G -> _colors)[i] = 0;
    }
}

u32 neighbour(u32 j, u32 i, Graph G) {
    assert(G != NULL);
    // NOTE: Empieza en 0 los vecinos.

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

void setColor(color x, u32 i, Graph G) {
    assert(G != NULL);
    if (i >= numberOfVertices(G)) {
        // printf("Index out of bounds en setColor\n");// NOTE printConsole
        return;
    }
    (G->_colors)[i] = x;
}

void extractColors(Graph G, color* Color) {
    assert(G != NULL);
    memcpy(Color, G -> _colors, (G -> n) * sizeof(color));
}

void printEdges(Graph G) {
    assert(G != NULL);
    printf("\nEdges:\n");
    for (u32 i = 0; i < 2 * (G->m); i++) {
        printf("%d ~ %d\n", G->_edges[i].x, G->_edges[i].y);
    };
}

void printVertices(Graph G) {
    assert(G != NULL);
    printf("\nVertices:\n");
    for (u32 i = 0; i < G->n; i++) {
        printf("Vértice %d: degree %d - Índice en lista de lados %d  - Color: %d\n", i,
               (G->_degrees)[i], (G->_firstneighbour)[i], G->_colors[i]);
    };
}

void printGraph(Graph G) {
    assert(G != NULL);
    printf("\nn = %d\n", G->n);
    printf("m = %d\n", G->m);
    printf("Δ = %d\n\n", G->Δ);
    printf("δ = %d\n\n", G->δ);
    printVertices(G);
    printEdges(G);
}

void writeGraph(Graph G, char* fname){
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

