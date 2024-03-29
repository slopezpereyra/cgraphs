#include "APIG24.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <stdbool.h>
//#include <time.h>

u32 max(u32 x, u32 y) {
    if (x > y) {
        return (x);
    }
    return (y);
}

u32 min(u32 x, u32 y) {
    if (x < y) {
        return (x);
    }
    return (y);
}

/**
* Esta función establece una relación de orden ⪯ entre elementos de tipo
* `struct Lado`s.
* Un `Lado` A con valores x = a₁, y = a₂ y un `Lado` B con valores
* x = b₁, y = b₂ se ordenan bajo esta relación de la siguiente forma:
*
* A ≼ B ⟺  a₁ < b₁ o bien (a₁ = b₁ ∧ a₂ ≤ b₂)
*
* De este modo, si denotamos a un `Lado` simplemente con el par (x, y) de sus
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
int CompararLados(const void* a, const void* b) {
    Lado ladoA = (Lado)a;
    Lado ladoB = (Lado)b;

    // Compare first by x values
    if (ladoA->x != ladoB->x)
        return (ladoA->x - ladoB->x);

    // If x values are equal, compare by y values
    return (ladoA->y - ladoB->y);
}

/**
 * Inicializa un grafo de n vértices y m lados.
 */
Grafo InicializarGrafo(u32 n, u32 m) {
    Grafo G = (Grafo)malloc(sizeof(struct GrafoSt));
    G->n = n;
    G->m = m;
    G->delta = 0;
    G->_primerVecino = (u32*)calloc(n, sizeof(u32));
    G->_grados = (u32*)calloc(n, sizeof(u32));
    G->_colores = (u32*)calloc(n, sizeof(u32));
    G->_lados = (Lado)calloc(2 * m, sizeof(struct LadoSt));
    return (G);
}

/**
 * Dado un grafo `G` y nombres de vértices `x` e `y`, agrega en la
 * i-écima posición de `G -> _lados` el x ~ y. Posteriormente,
 * agrega en la "posición espejo" al lado y ~ x. Finalmente, aumenta
 * los grados de los lados involcurados en uno y recalcula Δ.
 */
void AgregarLados(Grafo G, u32 i, u32 x, u32 y) {
    assert(G != NULL);
    // Setear el lado x ~ y
    (G->_lados)[i].x = x;
    (G->_lados)[i].y = y;
    // Setear el lado y ~ x
    (G->_lados)[i + G->m].x = y;
    (G->_lados)[i + G->m].y = x;
    (G->_grados)[x]++;
    (G->_grados)[y]++;
    (G->delta) = max(max((G->_grados)[x], (G->_grados)[y]), G->delta);
}

/**
 * Lee un file hasta encontrar un `\n`.
 */
static void Saltear_linea(FILE* file) {
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
 *    - Setea el primerVecino de cada vértice.
 */
Grafo ConstruirGrafo() {
    u32 n;              // Cant. Vertices
    u32 m;              // Cant. Lados
    FILE* file = stdin; // Standard input

    char c;
    while (1) {
        c = getc(file);
        if (c == 'c') {
            Saltear_linea(file);
        } else {
            break;
        }
    }

    // Esta mal el formato del archivo.
    if (c != 'p') {
        printf("\nMal formato de archivo.\n"); // NOTE PrintConsole
        return NULL;
    }

    // Asignamos 6: 4 char para edge, 1 para \0
    // y 1 para chequear si esta mal la linea.
    char edge_str[6];
    int matched_format; // Por el ret de fscanf

    /* Lectura del FILE hasta p edge */
    matched_format = fscanf(file, "%s %u %u", edge_str, &n, &m);

    if (matched_format < 3) {
        printf("ERROR: No hay match.\n"); // NOTE PrintConsole
    }

    Saltear_linea(file);
    if (strcmp("edge", edge_str) != 0) {
        printf("ERROR: No hay match en edge.\n"); // NOTE PrintConsole
        return NULL;
    }

    Grafo G = InicializarGrafo(n, m);

    for (u32 i = 0; i < m; i++) {
        // No hay comentarios dentro de lados
        u32 x, y;
        if (scanf("e %u %u\n", &x, &y) == 2) {
            AgregarLados(G, i, x, y);
        } else {
            printf("Error leyendo los lados del grafo.\n"); // NOTE PrintConsole
            return NULL; // Caso de error devuelvo NULL
        }
    };

    qsort(G->_lados, 2 * (G->m), sizeof(struct LadoSt), CompararLados);

    for (u32 j = 1; j < (G->n); j++) {
        (G->_primerVecino)[j] = (G->_primerVecino[j - 1]) + (G->_grados)[j - 1];
    };

    return G;
}

void DestruirGrafo(Grafo G) {
    if (G != NULL) {
        free(G->_lados);
        free(G->_grados);
        free(G->_colores);
        free(G->_primerVecino);
        free(G);
    }
}

u32 NumeroDeVertices(Grafo G) {
    assert(G != NULL);
    return G->n;
}

u32 NumeroDeLados(Grafo G) {
    assert(G != NULL);
    return G->m;
}

u32 Delta(Grafo G) {
    assert(G != NULL);
    return G->delta;
}

u32 Grado(u32 i, Grafo G) {
    assert(G != NULL);
    if (i < G->n) {
        return (G->_grados)[i];
    }
    return 0;
}

color Color(u32 i, Grafo G) {
    assert(G != NULL);
    if (i < G->n) {
        // NOTE: `i` es el nombre, y coincide con el indice.
        return G->_colores[i];
    }
    printf(
        "Index out of bounds en Color(): Devolviendo 2^32  -1"); // NOTE PrintConsole
    return 4294967295; // 2^32 - 1 Revisar tipo para devolver! :)
}

u32 Vecino(u32 j, u32 i, Grafo G) {
    assert(G != NULL);
    // NOTE: Empieza en 0 los vecinos.

    if (j >= Grado(i, G) || i >= NumeroDeVertices(G)) {
        printf("Index out of bounds en Vecino(): devolviendo 2^32 -1; "
               "Arguments were: j = %d, i = %d\n",
               j, i);      // NOTE PrintConsole
        return 4294967295; // 2^32 - 1
    }
    u32 indexDei = (G->_primerVecino)[i];
    return ((G->_lados)[j + indexDei].y);
}

void AsignarColor(color x, u32 i, Grafo G) {
    assert(G != NULL);
    if (i >= NumeroDeVertices(G)) {
        printf("Index out of bounds en AsignarColor\n");// NOTE PrintConsole
        return;
    }
    (G->_colores)[i] = x;
}

void ExtraerColores(Grafo G, color* Color) {
    assert(G != NULL);
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        Color[i] = (G->_colores)[i];
    };
}

void ImportarColores(color* Color, Grafo G) {
    assert(G != NULL);
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        (G->_colores)[i] = Color[i];
    };
}

void ImprimirLados(Grafo G) {
    assert(G != NULL);
    printf("\nLados:\n");
    for (u32 i = 0; i < 2 * (G->m); i++) {
        printf("%d ~ %d\n", G->_lados[i].x, G->_lados[i].y);
    };
}

void ImprimirVertices(Grafo G) {
    assert(G != NULL);
    printf("\nLados:\n");
    for (u32 i = 0; i < G->n; i++) {
        printf("Vértice %d: Grado %d - Índice en lista de lados %d \n", i,
               (G->_grados)[i], (G->_primerVecino)[i]);
    };
}

void ImprimirGrafo(Grafo G) {
    assert(G != NULL);
    printf("\nn = %d\n", G->n);
    printf("m = %d\n", G->m);
    printf("Δ = %d\n\n", G->delta);
    ImprimirVertices(G);
    ImprimirLados(G);
}
