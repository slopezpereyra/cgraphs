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
//     while (G->_vertices[vertex_key]->nombre != v) {
//         vertex_key++;
//     }
//     return (vertex_key);
// }

vertice ObtenerVertice(u32 v, Grafo G) {
    u32 inf = 0;
    u32 sup = NumeroDeVertices(G);
    u32 j = 0;
    u32 mid = sup / 2;

    // char band = 'F';

    while ((inf < sup) && (j < NumeroDeVertices(G))) {
        if (G->_vertices[mid]->nombre == v) {
            // band = 'V';
            return G->_vertices[mid];
            break; // FIXME Esta de mas
        }
        if (G->_vertices[mid]->nombre > v) {
            printf("%s", "\nestoy entre : ");
            printf("%d", G->_vertices[inf]->nombre);
            printf("%s", " y ");
            printf("%d", G->_vertices[mid]->nombre);
            sup = mid;
            mid = (inf + sup) / 2;
            if (sup == mid) {
                return NULL; // FIXME
                break;
            }
        } else if (G->_vertices[mid]->nombre < v) {
            printf("%s", "\nestoy entre : ");        // FIXME
            printf("%d", G->_vertices[inf]->nombre); // FIXME
            printf("%s", " y ");                     // FIXME
            printf("%d", G->_vertices[mid]->nombre); // FIXME
            inf = mid;
            mid = (inf + sup) / 2;
            if (inf == mid) {
                return NULL; // FIXME
                break;
            }
        }
        j++;
    }
}

/**
 * Inicializa un grafo de n vértices y m lados.
 */
Grafo InicializarGrafo(u32 n, u32 m) {
    Grafo G = (Grafo)malloc(sizeof(struct GrafoSt));
    G->n = n;
    G->m = m;
    G->_vertices = (vertice*)calloc(n, sizeof(vertice));
    // G->nextVertice = 0;
    G->_lados = (lado*)malloc(2 * m * sizeof(lado));
    G->nextLado = 0;

    return (G);
}

// TODO Mejorar el nombre
/**
 * Actualiza delta y sigma del grafo en caso de ser necesario.
*/
void ActualizarGradosGrafo(Grafo G, u32 grado) {
    if (G->delta < grado) {
        G->delta = grado;
    }

    if (G->sigma > grado) {
        G->sigma = grado;
        return;
    }
}

/**
 * Actualiza el grado de un vertice incrementandolo en 1.
*/
void IncrementarGradoVertice(Grafo G, u32 nombre) {
    vertice v = ObtenerVertice(nombre, G);
    v->grado++;
    ActualizarGradosGrafo(G, v->grado);
}

/**
 * Comprueba si un vértice de nombre `nombre` ya existe en el grafo `G`.
 * De ser así no hace nada. De no ser así, lo agrega a `G -> _vertices` en la
 * posición correspondiente a su hash code.
 */

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
    // NOTE: No hace falta chequear que si ya existe,
    // dado que es utilizado despues de ordenar los lados.
    G->_vertices[vIndex] = (vertice)malloc(sizeof(struct Vertice));
    G->_vertices[vIndex]->nombre = nombre;
    G->_vertices[vIndex]->grado = 1; // Porque es un lado, tiene un vecino.
    G->_vertices[vIndex]->color_ = 0;
    G->_vertices[vIndex]->primerVecino = i;

    // Agrego el vertice x del lado
    (G->_lados)[i]->xV = G->_vertices[vIndex]; // FIXME

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
    G->nextLado++;
}

/**
 * Dado un grafo `G` y nombres de vertices `x` e `y`,
 * agrega a ambos vertices sus correspondiente vecino.
*/
// void AgregarVecino(Grafo G, u32 x, u32 y) {
//     // TODO AgregarVecino()
//     // G->_vertices[]
// }

void ImprimirLinea(char* line) { printf("%s", line); }

Grafo ConstruirGrafo() {
    char filename[100];
    FILE* file;
    // Ingresar nombre del archivo
    // printf(
    // "Nombre del archivo a leer (dejelo vacío por ahora!): "); // FIXME Input
    // char sfilename[] =
    fgets(filename, sizeof(filename), stdin); // FIXME Input

    // Abrir el archivo (notar que por ahora abre un archivo constante,
    // a modo de testeo).
    file = fopen("K5.txt", "r");
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
    // Agregamos el primer vertice.
    AgregarVertice(G, 0, 0, G->_lados[0]->xN);

    for (u32 i = 1; i < G->m * 2; i++) {
        // Si xV != xN Significa que tenemos un x diferente.
        // printf("cx: %d, currentVx: %d\n", (G->_lados[i])->xN, currentVx);

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
            // printf("index: %d", vIndex);
            AgregarVertice(G, i, vIndex, nombre);
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
        // NOTE: Corroborar
        vertice v = ObtenerVertice(i, G);
        return v->grado;
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
    G->_vertices[i]->color_ = x;
}

void ExtraerColores(Grafo G, color* Color) {}

void ImportarColores(color* Color, Grafo G) {}

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

    ImprimirVertices(G);
    ImprimirLados(G);
}

int main() {
    Grafo G = ConstruirGrafo();
    if (G != NULL) {
        // printf("Comenzando descripción del grafo.\n"); // NOTE PrintConsole
        // ImprimirGrafo(G); // NOTE PrintConsole
        // printf("\nGrado= %d\n", Grado(4, G)); // NOTE PrintConsole
        // printf("Destruyendo grafo...\n");              // NOTE PrintConsole
        DestruirGrafo(G);
    } else {
        printf("Error construyendo el grafo.\n");
    }
    return 0;
}