#include "APIG24.h"

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

/**
 * Encuentra el u32 key tal que ( G -> _vertices )[key] contiene al vértice
 * de nombre v.
 */
// u32 ObtenerVertexKey(u32 v, Grafo G) {
//     u32 vertex_key = Hashv(v) % G->n;
//     while ((G->_vertices)[vertex_key]->nombre != v) {
//         vertex_key++;
//     }
//     return (vertex_key);
// }

/**
 * Inicializa un grafo de n vértices y m lados.
 */
Grafo InicializarGrafo(u32 n, u32 m) {
    Grafo G = (Grafo)malloc(sizeof(struct GrafoSt));
    G->n = n;
    G->m = m;
    G->_vertices = (vertice*)malloc(n * sizeof(vertice));
    G->nextVertice = 0;
    G->_lados = (lado*)malloc(2 * m * sizeof(lado));
    G->nextLado = 0;

    return (G);
}

/**
 * Comprueba si un vértice de nombre `nombre` ya existe en el grafo `G`.
 * De ser así no hace nada. De no ser así, lo agrega a `G -> _vertices` en la
 * posición correspondiente a su hash code.
 */

/**
 * Agrega un vertice a partir de la lectura de un lado.
*/
void AgregarVertice(Grafo G, u32 nombre) {
    // NOTE: No hace falta chequear que si ya existe,
    // dado que es utilizado despues de ordenar los lados.
    (G->_vertices)[G->nextVertice] = (vertice)malloc(sizeof(struct Vertice));
    (G->_vertices)[G->nextVertice]->nombre = nombre;
    (G->_vertices)[G->nextVertice]->grado = 0;      // TODO Mejorar
    (G->_vertices)[G->nextVertice]->grado++;        // TODO Mejorar
    G->nextVertice++;
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
    G->nextLado++;
}

// TODO
// void IncremetarGrado(Grafo G, ) {
//     G->
// }

/**
 * Dado un grafo `G` y nombres de vertices `x` e `y`,
 * agrega a ambos vertices sus correspondiente vecino.
*/
void AgregarVecino(Grafo G, u32 x, u32 y) {
    // TODO AgregarVecino()
    // (G->_vertices)[]
}

// FIXME Esta mal el tipo del argumento
// void ImprimirLinea(char line) {
//     printf("%s", line);
// }

Grafo ConstruirGrafo() {
    char filename[100];
    FILE* file;
    // Ingresar nombre del archivo
    printf("Nombre del archivo a leer (dejelo vacío por ahora!): ");  // FIXME Input
    fgets(filename, sizeof(filename), stdin);  // FIXME Input

    // Abrir el archivo (notar que por ahora abre un archivo constante,
    // a modo de testeo).
    file = fopen("K5.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return NULL;
    }

    // Read and print the contents of the file
    char line[100];
    u32 n, m;
    Grafo G;
    while (fgets(line, sizeof(line), file) != NULL) {
        // ImprimirLinea(line);  // NOTE PrintConsole
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
    // TODO Agregar leer lados y generar vertices
    for (u32 i=0; i < G->m*2; i++) {
        AgregarVertice(G, (G->_lados[i])->xN);
        AgregarVertice(G, (G->_lados[i])->yN);
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
        // TODO change i if it's the name of the vertex, not the hash
        res = G->_vertices[i]->grado;
    }
    return res;
}

color Color(u32 i, Grafo G) {
    if (i < G->n) {
        // NOTE: Revisar que corresponda a lo solicitado en el PDF.
        return G->_vertices[i]->color_;
    }

    printf("NO CUMPLE! :( Revisar Grafo");
    return 4294967295; // 2^32 - 1 Revisar tipo para devolver! :)
}

u32 Vecino(u32 j, u32 i, Grafo G) { return 0; }

void AsignarColor(color x, u32 i, Grafo G) {
    if (i >= NumeroDeVertices(G)) {
        return;
    }

    // Asigno el color `x` al vertice `i`
    (G->_vertices)[i]->color_ = x;
}

void ExtraerColores(Grafo G, color* Color) {}

void ImportarColores(color* Color, Grafo G) {}


void ImprimirVertices(Grafo G) {
    printf("Vertices:\n");
    for (u32 i = 0; i < G->n; i++) {
        if (G->_vertices[i] != NULL) {
            printf("Vertice %d de grado %d \n", G->_vertices[i]->nombre, 
                                                G->_vertices[i] -> grado);
        }
    }
}

void ImprimirLados(Grafo G) {
    printf("\nLados:\n");
    for (u32 i = 0; i < 2*( G->m ); i++) {
        if (G->_lados[i] != NULL) {
            printf("%d ~ %d\n", G->_lados[i]->xN, G->_lados[i]->yN);
        }
    }
}

void ImprimirGrafo(Grafo G) {
    printf("\nn = %d\n", G -> n);
    printf("\nm = %d\n", G -> m);
    printf("\nΔ = %d\n", G -> delta);

    ImprimirVertices(G);

    ImprimirLados(G);
}

int main() {
    Grafo G = ConstruirGrafo();
    if (G != NULL) {
        printf("Comenzando descripción del grafo.\n");
        // ImprimirGrafo(G);  // NOTE PrintConsole
    } else {
        printf("Error construyendo el grafo.\n");
    }
    return 0;
}