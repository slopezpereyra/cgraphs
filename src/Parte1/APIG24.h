#ifndef APIG24_H
#define APIG24_H


#include <stdio.h>
#include <stdlib.h>

// El .h de abajo debe tener definida GrafoSt, u32 y color.
#include "EstructuraGrafo24.h"

// Grafo es un puntero a una estructura GrafoSt,
// la cual debe estar definida en el .h de arriba

typedef GrafoSt *Grafo;

// Construccion/destruccion

// Debe leer desde stdin
/**
 * La funcion aloca memoria, inicializa lo que haya que inicializar de una estructura GrafoSt ,lee un grafo desde
standard input en el formato indicado en la ´ultima secci´on, lo carga en la estructura, colorea todos los vertices
con el color 0, y devuelve un puntero a la estructura.
En caso de error, la funcion devolver´a un puntero a NULL. (errores posibles pueden ser falla en alocar memoria,
pero tambi´en que el formato de entrada no sea vaalido.
 *
 * NOTA: Dado que esta funcion debe como m´ınimo leer todos los lados de los datos de entrada, su complejidad no puede ser inferior a O(m), pero esta funcion NO PUEDE ser O(n2) (y MENOS puede ser O(mn)) pues en los grafos de testeo habr´a grafos con millones de vertices, y un grafo asi con un algoritmo O(n2) no terminara en un tiempo razonable. En cuanto a m, puede estar en el orden de millones tambien, y puede ser m = O(n2), pero s´olo para n del orden
de miles, mientras que cuando n sea del orden de millones, m no ser´a O(n2) sino O(n), pues como dijimos arriba
esta funcion no puede tener complejidad menor a O(m) y un m de pej miles de millones haria que demorara mucho.
Asi que deberian pensar una estructura tal que esta funcion sea, idealmente, O(m). En a˜nos anteriores, con las
especificaciones dadas entonces, esto parecia ser muy dificil, asi que O(mlogm) era perfectamente aceptable. Este
a˜no, con las especificaciones dadas, deberian poder hacerlo en tiempo O(m), pero tambien aceptaremos O(mlogm). (el c´odigo para O(mlogm) es probablemente mas corto, dependiendo como programen).
*/
Grafo ConstruirGrafo();

/**
 * Destruye G y libera la memoria alocada.
 *
 * NOTA: Esta funcion tambien deberia tener una complejidad razonable, no hay razon para que sea mayor a O(m) e incluso puede ser menor, pero O(m) es aceptable.
*/
void DestruirGrafo(Grafo G);

// *Funciones para extraer datos del grafo. u32 debe estar definida en el .h de arriba

/**
 * Devuelve el numero de vertices de G.
*/
u32 NumeroDeVertices(Grafo G);

/**
 * Devuelve el numero de lados de G.
*/
u32 NumeroDeLados(Grafo G);

/**
 * Devuelve ∆(G), es decir, el mayor grado.
 *
 * NOTA: Esta funcion esta detallada aca para ser usada en algunos casos y no tener que recalcular ∆, asi que si, en vez de hacer el caalculo una vez durante la construccion del grafo y guardar el resultado para que esta funcion lo pueda leer en O(1), lo que hacen es recalcular ∆ cada vez que se llama esta funcion, tendran descuento de puntos.
*/
u32 Delta(Grafo G);

// *Funciones de extraccion de informacion de vertices

u32 Grado(u32 i,Grafo G);
color Color(u32 i, Grafo G);

/**
 * Si i es menor que el numero de vertices y j es menor que el grado del vertice i y el vecino j-esimo del vertice i es el vertice k entonces Vecino(j,i,G) es igual a k.
 *
 * NOTA: Podemos usar M como cota para la asignacion de vecinos.
*/
u32 Vecino(u32 j, u32 i, Grafo G);


// *Funciones con colores

/**
 * Si i es mayor o igual que el numero de vertices, esta funcion no hace nada.
 * Si i es menor que el numero de vertices, la funcion asigna el color x al vertice i.
*/
void AsignarColor(color x, u32 i, Grafo  G);

/**
 * Si n es el numero de vertices de G, esta funcion asigna a Color[i] el color que tiene el vertice i en G, para cada i entre 0 y n − 1.
 *
 * NOTA: SE ASUME que Color es un array que apunta a un lugar de memoria con n lugares.
 *
 * NO ES REQUERIMIENTO que la funcion preserve el color de los vertices. Es decir, luego de llamar a esta funcion, los colores de los vertices de G pueden ser distintos de los originales. (dependiendo de quien implemente
esta funcion).
 *
 * Por lo tanto, el usuario de esta funcion debe tener en cuenta esto.
*/
void ExtraerColores(Grafo G, color* Color);

/**
 * Si n es el n´umero de v´ertices de G, esta funcion asigna al v´ertice i de G el color Color[i], para cada i entre 0 y
n − 1.
 *
 * NOTA: SE ASUME que Color es un array que apunta a un lugar de memoria con n lugares.
 *
 * NO ES REQUERIMIENTO que la funcion preserve los valores originales que tenia Color. Es decir, luego de
llamar a esta funcion, el array Color puede tener cualquier cosa. (dependiendo de quien implemente esta funcion).
 *
 * Por lo tanto, el usuario de esta funcion debe tener en cuenta esto
*/
void ImportarColores(color* Color, Grafo  G);

#endif
