#include "APIG24.h"

#include <stdio.h>
#include <stdlib.h>

u32 max(u32 x, u32 y){
    if (x > y) { return(x); }return(y);
}

u32 min(u32 x, u32 y){
    if (x < y) { return(x); }return(y);
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
    if (ladoA->x != ladoB->x)
        return (ladoA->x - ladoB->x);

    // If x values are equal, compare by y values
    return (ladoA->y - ladoB->y);
}

/**
 * Encuentra el u32 key tal que ( G -> _vertices )[key] contiene al vértice 
 * de nombre v.
 */
u32 ObtenerVertexKey(u32 v, Grafo G){
    u32 vertex_key = Hashv(v) % G -> n;
    while ( (G -> _vertices)[vertex_key] -> nombre != v ){
        vertex_key++;
    }
    return(vertex_key);
}


/**
 * Inicializa un grafo de n vértices y m lados.
 */
Grafo InicializarGrafo(u32 n, u32 m){
    Grafo G = (Grafo) malloc(sizeof(struct GrafoSt));
    G -> n = n;
    G -> m = m;
    G -> _vertices = (vertice *) malloc(n * sizeof(vertice));
    G -> _lados = (lado *) malloc(2 * m * sizeof(lado));

    return(G);
}

/**
 * Comprueba si un vértice de nombre `nombre` ya existe en el grafo `G`.
 * De ser así no hace nada. De no ser así, lo agrega a `G -> _vertices` en la 
 * posición correspondiente a su hash code.
 */
void AgregarVertice(Grafo G, u32 nombre){
    u32 key = Hashv(nombre) % (G -> n);
    while ( (G -> _vertices)[key] != NULL ){
        if ( ( G -> _vertices[key] ) -> nombre == nombre ){
            // This vertex has already been included.
            return;
        }
        key++;
    }
    ( G ->_vertices )[key] = (vertice)malloc(sizeof(struct Vertice));
    ( G ->_vertices )[key] -> nombre = nombre;
}

/**
 * Dado un grafo `G` y nombres de vértices `x` e `y`, agrega en  `G -> _lados` 
 * el puntero al `Lado` x ~ y. Lo agrega en la posición dada por el hash code 
 * del lado.
 * 
 */
void AgregarLado(Grafo G, u32 x, u32 y){
    // Como Hashl -> 0, esta funcion agrega los lados en el orden en que 
    // son cargados.
    u32 index = Hashl(x, y);
    // Handle collisions
    while ( (G -> _lados)[index] != NULL ){
        index++;
    }
    ( G ->_lados )[index] = (lado)malloc(sizeof(struct Lado));
    ( G ->_lados )[index] -> x = x;
    ( G ->_lados )[index] -> y = y;
    u32 vertex_key = ObtenerVertexKey(x, G);
    ( G -> _vertices )[vertex_key] -> grado = ( G -> _vertices )[vertex_key] -> grado + 1;
}

Grafo ConstruirGrafo(){
    char filename[100];
    FILE *file;
    // Ingresar nombre del archivo
    printf("Nombre del archivo a leer (dejelo vacío por ahora!): ");
    fgets(filename, sizeof(filename), stdin);

    // Abrir el archivo (notar que por ahora abre un archivo constante, 
    // a modo de testeo).
    file = fopen("2gb.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return NULL;
    }

    // Read and print the contents of the file
    char line[100];
    u32 n, m;
    u32 n_key = 0, m_key = 0;
    Grafo G;
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
        // Extraer n y m de la línea de la forma "p edge n m".
        if (sscanf(line, "p edge %d %d", &n, &m) == 2) {
            G = InicializarGrafo(n, m);
        } 
        if (sscanf(line, "e %d %d", &n, &m) == 2) {
            AgregarVertice(G, n);
            AgregarVertice(G, m);
            AgregarLado(G, n, m);
            AgregarLado(G, m, n);
            n_key = ObtenerVertexKey(n, G);
            m_key = ObtenerVertexKey(m, G);
            G -> delta = max( max(G -> _vertices[n_key] -> grado, 
                                  G -> _vertices[m_key] -> grado),
                              G -> delta);
        } 
    }
    fclose(file);
    qsort(G -> _lados, 2 * ( G -> m ), sizeof(lado), CompararLados);

    return G;
}

u32 NumeroDeVertices(Grafo G) {
    return 0;
}

u32 NumeroDeLados(Grafo G) {
    return G->m;
}

u32 Delta(Grafo G) {
    return 0;
}

u32 Grado(u32 i, Grafo G){
    return 0;
}

color Color(u32 i, Grafo G){
    return 0;
}

u32 Vecino(u32 j, u32 i, Grafo G){
    return 0;
}

u32 Hashv(u32 x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return(x);
}

// u32 UnHashv() {
//     x = ((x >> 16) ^ x) * 0x119de1f3;
//     x = ((x >> 16) ^ x) * 0x119de1f3;
//     x = (x >> 16) ^ x;
//     return x;
// }

u32 Hashl(u32 x, u32 y) {
    return 0;
}


void ImprimirGrafo(Grafo G) {
    printf("\nn = %d\n", G -> n);
    printf("\nm = %d\n", G -> m);
    printf("\nΔ = %d\n", G -> delta);
    printf("Vertices:\n");
    for (u32 i = 0; i < G->n; i++) {
        if (G->_vertices[i] != NULL) {
            printf("Vertice %d de grado %d \n", G->_vertices[i]->nombre, 
                                                G->_vertices[i] -> grado);
        }
    }

    printf("\nLados:\n");
    for (u32 i = 0; i < 2*( G->m ); i++) {
        if (G->_lados[i] != NULL) {
            printf("%d ~ %d\n", G->_lados[i]->x, G->_lados[i]->y);
        }
    }
}

int main() {
    Grafo G = ConstruirGrafo();
    if (G != NULL) {
        printf("Comenzando descripción del grafo.\n");
        ImprimirGrafo(G);
    } else {
        printf("Error construyendo el grafo.\n");
    }
    return 0;
}
