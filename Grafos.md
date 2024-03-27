# Indice
- [Indice](#indice)
- [Grafos que estan OK](#grafos-que-estan-ok)
  - [K5masunoslados.txt](#k5masunosladostxt)
  - [2gb.txt o Grafo chico](#2gbtxt-o-grafo-chico)
  - [64gb.txt](#64gbtxt)
  - [4CBQ10](#4cbq10)
  - [8suCBQ10.txt o Grafo mediano](#8sucbq10txt-o-grafo-mediano)
  - [PGJ10\_500.txt o Grafo Grande](#pgj10_500txt-o-grafo-grande)
  - [PGJ10\_500.txt o Harkon](#pgj10_500txt-o-harkon)
  - [8suPGJ.txt o Grafo muy grande](#8supgjtxt-o-grafo-muy-grande)
- [Grafos que son para los asserts](#grafos-que-son-para-los-asserts)
  - [F.txt](#ftxt)


# Grafos que estan OK

## K5masunoslados.txt

```
p edge 9 14
e 1 5
e 2 6
e 2 7
e 3 8
e 1 0
e 2 4
e 1 4
e 2 0
e 3 2
e 0 3
e 3 4
e 2 1
e 4 0
e 1 3
```

## 2gb.txt o Grafo chico

8 vertices, 10 lados, Delta 3. vertices 0-7.

```
Delta(G) = 3
```

```
Grado(0) = 2
Grado(1) = 2
Grado(2) = 2
Grado(3) = 2
Grado(4) = 3
Grado(5) = 3
Grado(6) = 3
Grado(7) = 3
```

```txt
p edge 8 10
e 1 7
e 2 6
e 1 4
e 2 5
e 3 7
e 0 6
e 3 4
e 0 5
e 4 7
e 5 6
```

## 64gb.txt

256 vertices, 320 lados, Delta 3 vertices 0-255

## 4CBQ10

536 vertices, 114036 lados, Delta 437

vertices 0-535

## 8suCBQ10.txt o Grafo mediano

1072 vertices, 84424 lados, Delta 169.
vertices 0-1071.

## PGJ10_500.txt o Grafo Grande

250000 vertices, 899501 lados, Delta 1004
vertices 0-249999

```
...
Vertice 16102 de grado 5
Comenzando a destruir el grafo G
./a.out  1124,44s user 2,86s system 99% cpu 18:47,85 total
```

- Construir funciona
- Destruir funciona

## PGJ10_500.txt o Harkon

Grafo con 6160 vertices, 18092520 lados, Delta 6057

Nota: este grafo tiene muchos menos vertices que el anterior "grafo grande", pero tiene muchos mas lados, mas incluso que el siguiente grafo.

## 8suPGJ.txt o Grafo muy grande

2000000 vertices, 7196008 lados

vertices 0-1999999

# Grafos que son para los asserts

## F.txt

Este grafo sirve para corroborar un assert en el cual se devuelve `NULL`.

```txt
p edgee 5 10
e 1 0
e 2 4
e 1 4
e 2 0
e 3 2
e 0 3
e 3 4
e 2 1
e 4 0
e 1 3
```