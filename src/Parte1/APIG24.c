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
    lado ladoA = *(lado*)a;
    lado ladoB = *(lado*)b;

    // Compare first by x values
    if (ladoA->xN != ladoB->xN)
        return (ladoA->xN - ladoB->xN);

    // If x values are equal, compare by y values
    return (ladoA->yN - ladoB->yN);
}

vertice ObtenerVertice(u32 v, Grafo G) { return G->_vertices[v]; }

vertice ObtenerVerticeOld(u32 v, Grafo G) {
    u32 inf = 0;
    u32 sup = NumeroDeVertices(G);
    u32 j = 0;
    u32 mid;

    while (low <= high) {
        mid = low + (high - low) / 2;
        if (G->_vertices[mid]->nombre == v) {
            return G->_vertices[mid];
        }
        if (G->_vertices[mid]->nombre < v) {
            low = mid + 1;
        } else{
            high = mid - 1;
        }
    }
    printf("Returnign NULL en ObtenerVertice!\n");
    return NULL;
}

/**
 * Inicializa un grafo de n vértices y m lados.
 */
Grafo InicializarGrafo(u32 n, u32 m) {
    Grafo G = (Grafo)malloc(sizeof(struct GrafoSt));
    G->n = n;
    G->m = m;
    G->delta = 0;
    G->_vertices = (vertice*)calloc(n, sizeof(vertice));
    G->_lados = (lado*)malloc(2 * m * sizeof(lado));
    G->nextLado = 0;

    return (G);
}

/**
 * Actualiza delta del grafo en caso de ser necesario.
*/
void ActualizarGradosGrafo(Grafo G, u32 grado) {
    if (G->delta < grado) {
        G->delta = grado;
    }
}

/**
 * Agrega un vertice a partir de la lectura de un lado.
 *
 * `i` es el indice del array de lados.
 *
 * `vIndex` es el indice del array de vertices.
 *
 * `nombre` es el nombre del vertice xN del array de lados.
*/
void AgregarVertice(Grafo G, u32 i, u32 vIndex, u32 nombre) {
    if (G->_vertices[vIndex] == NULL) {
        G->_vertices[vIndex] = (vertice)malloc(sizeof(struct Vertice));
        G->_vertices[vIndex]->nombre = nombre;
        G->_vertices[vIndex]->grado = 1; // Porque es un lado, tiene un vecino.
        G->_vertices[vIndex]->color_ = 0;
        G->_vertices[vIndex]->primerVecino = i;
    }

    // // Agrego el vertice x del lado
    // (G->_lados)[i]->xV = G->_vertices[vIndex];

    ActualizarGradosGrafo(G, G->_vertices[vIndex]->grado);
}

/**
 * Dado un grafo `G` y nombres de vértices `x` e `y`, agrega en  `G -> _lados`
 * el puntero al `Lado` x ~ y. Lo agrega en la posición dada por el hash code
 * del lado.
 */
void AgregarLado(Grafo G, u32 x, u32 y) {
    (G->_lados)[G->nextLado] = (lado)malloc(sizeof(struct Lado));
    (G->_lados)[G->nextLado]->xN = x;
    (G->_lados)[G->nextLado]->yN = y;

    // Sabemos que los nombres de los vertices van de
    // 0 a n-1, por eso podemos
    AgregarVertice(G, G->nextLado, x, x);
    AgregarVertice(G, G->nextLado, y, y); // FIXME

    // Entonces podemos agregar los vertices
    // por el nombre como indice
    (G->_lados)[G->nextLado]->xV = G->_vertices[x];
    (G->_lados)[G->nextLado]->xV = G->_vertices[y];

    G->nextLado++;
}

void ImprimirLinea(char* line) { printf("%s", line); }

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
    file = fopen("K5.txt", "r"); // NOTE FILENAME
    // file = fopen(sfilename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return NULL;
    }

    // Read and print the contents of the file
    char line[100];
    u32 n, m;
    Grafo G;
    while (fgets(line, sizeof(line), file) != NULL) {
        // ImprimirLinea(line); // NOTE PrintConsole
        // printf("%s", line);  // NOTE PrintConsole

        // Extraer n y m de la línea de la forma "p edge n m".
        if (sscanf(line, "p edge %d %d", &n, &m) == 2) {
            G = InicializarGrafo(n, m);
        }
        if (sscanf(line, "e %d %d", &n, &m) == 2) {
            AgregarLado(G, n, m);
            AgregarLado(G, m, n);
        }
    }
    fclose(file);

    // Ordenamos el array de lados
    qsort(G->_lados, 2 * (G->m), sizeof(lado), CompararLados);

    // Una vez tenemos ordenado lados, procedemos a crear los vertices
    // NOTA: Los vertices van a ser guardados ordenados.
    u32 vIndex = 0;

    for (u32 i = 1; i < G->m * 2; i++) {
        // Si xV != xN Significa que tenemos un x diferente.

        u32 nombre = G->_lados[i]->xN; // Nombre del vertice `x`.

        // Como agregamos el primero, el primero nunca es NULL
        // a pesar de utilizar calloc.
        if (G->_vertices[vIndex]->nombre == nombre) {
            // Tenemos un lado con el mismo xV
            // Entonces tiene un vecino mas
            (G->_vertices[vIndex]->grado)++;
            ActualizarGradosGrafo(G, G->_vertices[vIndex]->grado);
        } else {
            vIndex++;
            G->_vertices[vIndex]->primerVecino = i;
            ActualizarGradosGrafo(G, G->_vertices[vIndex]->grado);
        }
    }
    return G;
}

void DestruirGrafo(Grafo G) {
    if (G != NULL) {
        for (u32 i = 0; i < G->m * 2; i++) {
            free(G->_lados[i]);
        }

        for (u32 i = 0; i < G->n; i++) {
            free(G->_vertices[i]);
        }

        free(G->_lados);
        free(G->_vertices);
        free(G);
    }
}

u32 NumeroDeVertices(Grafo G) { return G->n; }

u32 NumeroDeLados(Grafo G) { return G->m; }

u32 Delta(Grafo G) { return G->delta; }

u32 Grado(u32 i, Grafo G) {
    int res = 0;
    if (i < G->n) {
        return ObtenerVertice(i, G)->grado;
    }
    return res;
}

color Color(u32 i, Grafo G) {
    if (i < G->n) {
        // NOTE: `i` es el nombre, y coincide con el indice.
        return G->_vertices[i]->color_;
    }

    printf("NO CUMPLE! :( Revisar Grafo");
    return 4294967295; // 2^32 - 1 Revisar tipo para devolver! :)
}

u32 Vecino(u32 j, u32 i, Grafo G) {
    // NOTE: Empieza en 0 los vecinos.
    vertice v = G->_vertices[i];
    u32 grado = v->grado; // Grado del vertice `i`

    // NOTE: If expression evaluates to TRUE, assert() does nothing. If expression evaluates to FALSE, assert() displays an error message on stderr (standard error stream to display error messages and diagnostics) and aborts program execution.
    // assert(grado - 1 > j);  // FIXME Debe tirar un assert??
    if (grado - 1 < j) {
        printf(
            ">>>>>>>>>>>>>>>> ERROR en Vecino()"); // NOTE Revisar formato que debe devolver!
        return NULL;
    }

    u32 pV = v->primerVecino;

    if (j < grado) {
        return G->_lados[pV + j]->yN;
    }
}

void AsignarColor(color x, u32 i, Grafo G) {
    if (i >= NumeroDeVertices(G)) {
        return;
    }

    // Asigno el color `x` al vertice `i`
    G->_vertices[i]->color_ = x;
}

void ExtraerColores(Grafo G, color* Color) {
    for (u32 i = 0; i < NumeroDeVertices(G); i++){
        vertice v = ObtenerVertice(i, G);
        Color[i] = v -> color_;
    }
}

void ImportarColores(color* Color, Grafo G) {
    for (u32 i = 0; i < NumeroDeVertices(G); i++){
        vertice v = ObtenerVertice(i, G);
        v -> color_ = Color[i];
    }
}

void ProbarVecino(u32 j, u32 i, Grafo G) {
    printf("\nVecino(%d, %d) = %d\n", j, i, Vecino(j, i, G));
}

void ImprimirInfoVertice(vertice v) {
    printf("[Vertice = Nombre %d Grado %d Color %d Primer Vecino %d]",
           v->nombre, v->grado, v->color_, v->primerVecino);
}

void ImprimirVertices(Grafo G) {
    printf("Vertices:\n");
    for (u32 i = 0; i < G->n; i++) {
        if (G->_vertices[i] != NULL) {
            printf("Vertice %d de grado %d \n", G->_vertices[i]->nombre,
                   G->_vertices[i]->grado);
        }
    }
}

void ImprimirLados(Grafo G) {
    printf("\nLados:\n");
    for (u32 i = 0; i < 2 * (G->m); i++) {
        if (G->_lados[i] != NULL) {
            printf("%d ~ %d\n", G->_lados[i]->xN, G->_lados[i]->yN);
        }
    }
}

void ImprimirGrafo(Grafo G) {
    printf("\nn = %d\n", G->n);
    printf("m = %d\n", G->m);
    printf("Δ = %d\n\n", G->delta);
    printf("3er vecino del vértice 0: %d\n", Vecino(3, 0, G));
    printf("1er vecino del vértice 1: %d\n", Vecino(1, 1, G));
    printf("2do vecino del vértice 4: %d\n", Vecino(2, 4, G));
    printf("0 vecino del vértice 3: %d\n", Vecino(0, 3, G));
    ImprimirVertices(G);
    ImprimirLados(G);
}

int main() {
    Grafo G = ConstruirGrafo();
    if (G != NULL) {
        // printf("Comenzando descripción del grafo.\n"); // NOTE PrintConsole
        // ImprimirGrafo(G);                      // NOTE PrintConsole
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
