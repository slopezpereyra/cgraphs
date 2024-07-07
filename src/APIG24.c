#include "APIG24.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

u32 max(u32 x, u32 y) {
    return ( x > y ? x : y );
}

u32 min(u32 x, u32 y) {
    return ( x > y ? y : x );
}

Edge newEdge(u32 x, u32 y){
    Edge e = (Edge) malloc(sizeof(struct EdgeSt));
    e -> x = x;
    e -> y = y;
    return(e);
}

/**
* Esta función establece una relación de orden ⪯ entre elementos de tipo
* `struct Edge`s.
* Un `Edge` A con valores x = a₁, y = a₂ y un `Edge` B con valores
* x = b₁, y = b₂ se ordenan bajo esta relación de la siguiente forma:
*
* A ≼ B ⟺  a₁ < b₁ o bien (a₁ = b₁ ∧ a₂ ≤ b₂)
*
* De este modo, si denotamos a un `Edge` simplemente con el par (x, y) de sus
* valores, la siguiente lista de lados:
*
* (1, 0)
* (0, 1)
* (2, 1)
* (1, 2)
*
* se ordenaría
*
* (0, 1)
* (1, 0)
* (1, 2)
* (2, 1)
*
* El propósito de esta función es poder ejecutar quicksort sobre la lista de
* lados de un grafo.
*
* Para una referencia acerca de cómo construimos esta función,
* consulte: http://arantxa.ii.uam.es/~swerc/ejemplos/csorting.html
*/
int CompareEdges(const void* a, const void* b) {
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
Graph InitGraph(u32 n, u32 m) {
    Graph G = (Graph)malloc(sizeof(struct GraphSt));
    G->n = n;
    G->m = m;
    G->Δ = 0;
    G->δ = 1024;
    G->_firstNeighbor = (u32*)calloc(n, sizeof(u32));
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

u32 edgeIndex(Graph G, int x, int y){
    u32 index = (G -> _firstNeighbor)[x];
    for (u32 i = 0; i < Degree(x, G); i++){
        if (Neighbor(i, x, G) == y){
            break;
        }index++;
    }
    return(index);

}

void removeEdge(Graph G, int x, int y) {
    assert(x < y);
   
    u32 index1 = edgeIndex(G, x, y);
    u32 index2 = edgeIndex(G, y, x) - 1;
    for (int i = index1; i < 2*(G -> m)-1; i++) {
        (G->_edges)[i] = (G->_edges)[i + 1];
    }
    for (int i = index2; i < 2*(G -> m) - 1; i++) {
            (G->_edges)[i] = (G->_edges)[i + 1];
    }
    (G->m)--;
    G->_edges = (Edge)realloc(G->_edges, 2*(G->m) * sizeof(struct EdgeSt));
    (G->_degrees)[x]--;
    (G->_degrees)[y]--;
    if ((G->_edges) == NULL) {
        printf("Error: Realloc failed\n");
        exit(1);
    }
    FormatEdges(G);
}

/**
 * Lee un file hasta encontrar un `\n`.
 */
static void SkipLine(FILE* file) {
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
 *    - Setea el firstNeighbor de cada vértice.
 */
Graph BuildGraph() {
    u32 n;              // Cant. Vertices
    u32 m;              // Cant. Edges
    FILE* file = stdin; // Standard input

    char c;
    while (1) {
        c = getc(file);
        if (c == 'c') {
            SkipLine(file);
        } else {
            break;
        }
    }

    // Esta mal el formato del archivo.
    if (c != 'p') {
        // printf("\nMal formato de archivo.\n"); // NOTE PrintConsole
        return NULL;
    }

    // Asignamos 6: 4 char para edge, 1 para \0
    // y 1 para chequear si esta mal la linea.
    char edge_str[6];
    int matched_format; // Por el ret de fscanf

    // Lectura del FILE hasta p edge
    matched_format = fscanf(file, "%s %u %u", edge_str, &n, &m);

    if (matched_format < 3) {
        printf("ERROR: No hay match.\n"); // NOTE PrintConsole
    }

    SkipLine(file);
    if (strcmp("edge", edge_str) != 0) {
        // printf("ERROR: No hay match en edge.\n"); // NOTE PrintConsole
        return NULL;
    }

    Graph G = InitGraph(n, m);

    for (u32 i = 0; i < m; i++) {
        u32 x, y;
        if (scanf("e %u %u\n", &x, &y) == 2) {
            AddEdges(G, i, x, y);
        } else {
            // printf("Error leyendo los lados del grafo.\n"); // NOTE PrintConsole
            return NULL; // Caso de error devuelvo NULL
        }
    };

    FormatEdges(G);

    return G;
}

void FormatEdges(Graph G){
    qsort(G->_edges, 2 * (G->m), sizeof(struct EdgeSt), CompareEdges);
    for (u32 j = 1; j < (G->n); j++) {
        (G->_firstNeighbor)[j] = (G->_firstNeighbor[j - 1]) + (G->_degrees)[j - 1];
    };
}

void DumpGraph(Graph G) {
    if (G != NULL) {
        free(G->_edges);
        free(G->_degrees);
        free(G->_colors);
        free(G->_firstNeighbor);
        free(G);
    }
}

u32 NumberOfVertices(Graph G) {
    assert(G != NULL);
    return G->n;
}

u32 NumberOfEdges(Graph G) {
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

u32 Degree(u32 i, Graph G) {
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
    // printf("Index out of bounds en Color(): Devolviendo 2^32  -1"); // NOTE PrintConsole
    return 4294967295; // 2^32 - 1 Revisar tipo para devolver! :)
}

struct EdgeSt getEdge(u32 i, Graph G) {
    assert(G != NULL && i < 2* NumberOfEdges(G));
    return ( G->_edges )[i];
}

void removeColors(Graph G) {
    for (u32 i = 0; i < G -> n; i++){
        (G -> _colors)[i] = 0;
    }
}

u32 Neighbor(u32 j, u32 i, Graph G) {
    assert(G != NULL);
    // NOTE: Empieza en 0 los vecinos.

    if (j >= Degree(i, G) || i >= NumberOfVertices(G)) {
         printf(
             "Index out of bounds en Neighbor(): devolviendo 2^32 -1; "
                "Arguments were: j = %d, i = %d\n",
                j, i);      // NOTE PrintConsole
        return 4294967295; // 2^32 - 1
    }
    u32 indexDei = (G->_firstNeighbor)[i];
    return ((G->_edges)[j + indexDei].y);
}

void setColor(color x, u32 i, Graph G) {
    assert(G != NULL);
    if (i >= NumberOfVertices(G)) {
        // printf("Index out of bounds en setColor\n");// NOTE PrintConsole
        return;
    }
    (G->_colors)[i] = x;
}

void extractColors(Graph G, color* Color) {
    assert(G != NULL);
    memcpy(Color, G -> _colors, (G -> n) * sizeof(color));
}

void PrintEdges(Graph G) {
    assert(G != NULL);
    printf("\nEdges:\n");
    for (u32 i = 0; i < 2 * (G->m); i++) {
        printf("%d ~ %d\n", G->_edges[i].x, G->_edges[i].y);
    };
}

void PrintVertices(Graph G) {
    assert(G != NULL);
    printf("\nVertices:\n");
    for (u32 i = 0; i < G->n; i++) {
        printf("Vértice %d: degree %d - Índice en lista de lados %d  - Color: %d\n", i,
               (G->_degrees)[i], (G->_firstNeighbor)[i], G->_colors[i]);
    };
}

void PrintGraph(Graph G) {
    assert(G != NULL);
    printf("\nn = %d\n", G->n);
    printf("m = %d\n", G->m);
    printf("Δ = %d\n\n", G->Δ);
    printf("δ = %d\n\n", G->δ);
    PrintVertices(G);
    PrintEdges(G);
}

