#include "APIG24.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>



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
* Esta función establece una relación de orden estricto entre `struct Lado`s.
* Un `Lado` A con valores x = a₁, y = a₂ y un `Lado` B con valores
* x = b₁, y = b₂ se ordenan bajo esta relación de la siguiente forma:
*
* A menor o igual a B ⟺  a₁ < b₁ o bien (a₁ = b₁ ∧ a₂ ≤ b₂)
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
    G-> _primerVecino = (u32*)calloc(n, sizeof(u32));
    G->_grados = (u32*)calloc(n, sizeof(u32));
    G->_colores = (u32*)calloc(n, sizeof(u32));
    G->_lados = (Lado)calloc(2 * m, sizeof(struct LadoSt));
    return (G);
}


/**
 * Dado un grafo `G` y nombres de vértices `x` e `y`, agrega en  `G -> _lados`
 * el puntero al `Lado` x ~ y. Lo agrega en la posición dada por el hash code
 * del lado.
 */
void AgregarLados(Grafo G, u32 i, u32 x, u32 y) {
    printf("Poniendo lado %d ~ %d\n", x, y);
    // Setear el lado x ~ y
    (G -> _lados)[i].x = x;
    (G -> _lados)[i].y = y;
    // Setear el lado y ~ x
    (G -> _lados)[i + G -> m].x = y;
    (G -> _lados)[i + G -> m].y = x;
    (G -> _grados)[x]++;
    (G -> _grados)[y]++;
    (G -> delta) = max( max((G -> _grados)[x], (G -> _grados)[y]), G -> delta );
}

// TODO: Agregar asserts correspondientes
Grafo ConstruirGrafo() {
    char filename[100];
    FILE* file;
    // Ingresar nombre del archivo
    printf(
        "Nombre del archivo a leer (dejelo vacío por ahora!): "); // FIXME Input
    // char sfilename[] =
    fgets(filename, sizeof(filename), stdin); // FIXME Input

    // Abrir el archivo (notar que por ahora abre un archivo constante,
    // a modo de testeo).
    file = fopen("2gb.txt", "r"); // NOTE FILENAME
    // file = fopen(sfilename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return NULL;
    }

    // Read and print the contents of the file
    char line[100];
    u32 n, m;
    u32 i = 0;
    Grafo G;
    while (fgets(line, sizeof(line), file) != NULL) {
        // ImprimirLinea(line); // NOTE PrintConsole
        // printf("%s", line);  // NOTE PrintConsole

        // Extraer n y m de la línea de la forma "p edge n m".
        if (sscanf(line, "p edge %d %d", &n, &m) == 2) {
            G = InicializarGrafo(n, m);
        }
        if (sscanf(line, "e %d %d", &n, &m) == 2) {
            AgregarLados(G, i, n, m);
            i++;
        }
    }
    
    fclose(file);

    // Ordenamos el array de lados
 
    qsort(G->_lados, 2 * (G->m), sizeof(struct LadoSt), CompararLados);
   
    printf("N = %d\n", G -> n);
    for (u32 j = 1; j < (G -> n); j++) {
        printf("Setting primer vecino de %d\n", j);
        (G -> _primerVecino)[j] = (G -> _primerVecino[j - 1]) + (G -> _grados)[j-1];
    }
    printf("Exiting!");

    return(G);
}

void DestruirGrafo(Grafo G) {
    if (G != NULL) {
        free(G -> _lados);
        free(G -> _grados);
        free(G -> _colores);
        free(G);
    }
}

u32 NumeroDeVertices(Grafo G) { return G->n; }

u32 NumeroDeLados(Grafo G) { return G->m; }

u32 Delta(Grafo G) { return G->delta; }

u32 Grado(u32 i, Grafo G) {
    if (i < G->n) {
        return (G -> _grados)[i];
    }
    return 0;
}

color Color(u32 i, Grafo G) {
    if (i < G->n) {
        return G->_colores[i];
    } else {
        return 4294967295; 
    }
}

//u32 Vecino(u32 j, u32 i, Grafo G) {
//    // NOTE: Empieza en 0 los vecinos.
//    vertice v = ( G->_vertices[i] );
//    u32 grado = v->grado; // Grado del vertice `i`
//
//    if (j >= grado || i >= NumeroDeVertices(G)) {
//        printf("IndexError en Vecino() con j = %d, i = %d, n = %d, grado = %d\n", 
//                j, i, G -> n, grado);
//        return 4294967295; // 2^32 - 1 
//    }
//
//    u32 pV = v->primerVecino;
//    return G->_lados[pV + j]->yN;
//}

//void AsignarColor(color x, u32 i, Grafo G) {
//    if (i >= NumeroDeVertices(G)) {
//        return;
//    }
//
//    // Asigno el color `x` al vertice `i`
//    G->_vertices[i]->color_ = x;
//}

//void ExtraerColores(Grafo G, color* Color) {
//    for (u32 i = 0; i < NumeroDeVertices(G); i++){
//        vertice v = ObtenerVertice(i, G);
//        Color[i] = v -> color_;
//    }
//}
//
//void ImportarColores(color* Color, Grafo G) {
//    for (u32 i = 0; i < NumeroDeVertices(G); i++){
//        vertice v = ObtenerVertice(i, G);
//        v -> color_ = Color[i];
//    }
//}
//


void ImprimirLados(Grafo G) {
    printf("\nLados:\n");
    for (u32 i = 0; i < 2 * (G->m); i++) {
        printf("%d ~ %d\n", 
                G->_lados[i].x, 
                G->_lados[i].y);
    }
}

void ImprimirVertices(Grafo G) {
    printf("\nLados:\n");
    for (u32 i = 0; i < G -> n; i++) {
        printf("Vértice %d: Grado %d - Índice en lista de lados %d \n", 
              i, (G -> _grados)[i], (G -> _primerVecino)[i]);
    }
}

void ImprimirGrafo(Grafo G) {
    printf("\nn = %d\n", G->n);
    printf("m = %d\n", G->m);
    printf("Δ = %d\n\n", G->delta);
    ImprimirVertices(G);
    ImprimirLados(G);
}

int main() {
    Grafo G = ConstruirGrafo();
    if (G != NULL) {
        printf("Comenzando descripción del grafo.\n"); // NOTE PrintConsole
        ImprimirGrafo(G);                      // NOTE PrintConsole
        // vertice v = ObtenerVertice(3, G);      // NOTE Vertice
        // ImprimirInfoVertice(v);                // NOTE PrintConsole

        // PRUEBAS VECINO //
        // u32 j = 3; // y
        // u32 i = 3; // x
        // ProbarVecino(j, i, G);
        // END PRUEBAS //

        // printf("Destruyendo grafo...\n");              // NOTE PrintConsole
        DestruirGrafo(G);
    } else {
        printf("Error construyendo el grafo.\n");
    }
    return 0;
}
