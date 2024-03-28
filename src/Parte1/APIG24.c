#include "APIG24.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
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

// TODO: Agregar asserts correspondientes
/**
 * Construye un grafo desde una .txt file dada en standard input. Hace los 
 * siguientes pasos: 
 *    - Inicialización del grafo.
 *    - Scaneo línea por línea, agregando los lados al grafo.
 *    - Quick sort sobre los lados. 
 *    - Setea el primerVecino de cada vértice. 
 */
Grafo ConstruirGrafo() {
    u32 n, m;

    if (scanf("p edge %u %u\n", &n, &m) == 2) {
        Grafo G = InicializarGrafo(n, m);
        for (u32 i = 0; i < m; i++) {
            u32 x, y;
            if (scanf("e %u %u\n", &x, &y) == 2) {
                AgregarLados(G, i, x, y);
            } else {
                printf("Error leyendo los lados del grafo.\n");
                return NULL; // Caso de error devuelvo NULL
            }
        };

        // Ordenamos el array de lados
        qsort(G->_lados, 2 * (G->m), sizeof(struct LadoSt), CompararLados);

        for (u32 j = 1; j < (G->n); j++) {
            (G->_primerVecino)[j] =
                (G->_primerVecino[j - 1]) + (G->_grados)[j - 1];
        };
        return G;
    } else {
        printf("Error leyendo la descripción del grafo.\n");
    }
    return NULL; // Caso de error devuelvo NULL
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

u32 NumeroDeVertices(Grafo G) { return G->n; }

u32 NumeroDeLados(Grafo G) { return G->m; }

u32 Delta(Grafo G) { return G->delta; }

u32 Grado(u32 i, Grafo G) {
    if (i < G->n) {
        return (G->_grados)[i];
    }
    return 0;
}

color Color(u32 i, Grafo G) {
    if (i < G->n) {
        // NOTE: `i` es el nombre, y coincide con el indice.
        return G->_colores[i];
    }
    printf("Index out of bounds en Color(): Devolviendo 2^32  -1");
    return 4294967295; // 2^32 - 1 Revisar tipo para devolver! :)
}

u32 Vecino(u32 j, u32 i, Grafo G) {
    // NOTE: Empieza en 0 los vecinos.

    if (j >= Grado(i, G) || i >= NumeroDeVertices(G)) {
        printf("Index out of bounds en Vecino(): devolviendo 2^32 -1; "
               "Arguments were: j = %d, i = %d\n",
               j, i);
        return 4294967295; // 2^32 - 1
    }
    u32 indexDei = (G->_primerVecino)[i];
    return ((G->_lados)[j + indexDei].y);
}

void AsignarColor(color x, u32 i, Grafo G) {
    if (i >= NumeroDeVertices(G)) {
        printf("Index out of bounds en AsignarColor\n");
        return;
    }
    (G->_colores)[i] = x;
}

void ExtraerColores(Grafo G, color* Color) {
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        Color[i] = (G->_colores)[i];
    };
}

void ImportarColores(color* Color, Grafo G) {
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        (G->_colores)[i] = Color[i];
    };
}

void ImprimirLados(Grafo G) {
    printf("\nLados:\n");
    for (u32 i = 0; i < 2 * (G->m); i++) {
        printf("%d ~ %d\n", G->_lados[i].x, G->_lados[i].y);
    };
}

void ImprimirVertices(Grafo G) {
    printf("\nLados:\n");
    for (u32 i = 0; i < G->n; i++) {
        printf("Vértice %d: Grado %d - Índice en lista de lados %d \n", i,
               (G->_grados)[i], (G->_primerVecino)[i]);
    };
}

void ImprimirGrafo(Grafo G) {
    printf("\nn = %d\n", G->n);
    printf("m = %d\n", G->m);
    printf("Δ = %d\n\n", G->delta);
    ImprimirVertices(G);
    ImprimirLados(G);
}

int main() {
    // clock_t t;
    // t = clock();
    printf("Comenzando la creacion del grafo.\n");     // NOTE PrintConsole
    Grafo G = ConstruirGrafo();
    if (G != NULL) {
        printf("Comenzando descripción del grafo.\n"); // NOTE PrintConsole
        //ImprimirGrafo(G);                              // NOTE PrintConsole

        // PRUEBAS VECINO //
        // u32 j = 3; // y
        // u32 i = 3; // x
        // ProbarVecino(j, i, G);
        // END PRUEBAS //

        printf("Destruyendo grafo...\n"); // NOTE PrintConsole
        DestruirGrafo(G);
    } else {
        printf("Error construyendo el grafo.\n");
    }
    // t = clock() - t;
    // double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    // printf("main() took %f seconds to execute \n", time_taken);
    return 0;
}
