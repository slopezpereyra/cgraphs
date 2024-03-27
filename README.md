# Laboratorio de Matematica Discreta II

## Indice



Profesor: Daniel Penazzi.

## Objetivo

Los objetivos en este proyecto son:
1. Implementar un tema ensenado en clase en un lenguaje, observando las dificultades de pasar de la teoria a un
programa concreto.
2. Practicar programar funciones adhiriendose a las especificaciones de las mismas.
3. Practica de testeo de programas

## Integrantes

- Pereyra, Santiago.
- Quintero, Juan.
- Vispo, Solange Valentina.

## Como correr

### Compilacion

Compilaremos (con mains nuestros) usando gcc, -Wall, -Wextra, -O3, -std=c99 . Tambien haremos -I al directorio
donde pondremos los .h
Esas flags seran usadas para testear la velocidad, pero para testear grafos chicos podemos agregar otras flags.
Por ejemplo, podemos usar -DNDEBUG si vemos que estan mal usando asserts.
Tambien compilaremos, para testear grafos chicos, con flags que nos permitan ver si hay buffer overflows,
shadow variables o comportamientos indefinidos, en particular con -fsanitize=address,undefined. Su programa
DEBE compilar y correr correctamente con esa flag aunque para grafos grandes lo correremos con un ejecutable
compilado sin esa flag, dado que esa flag provoca una gran demora en la ejecuci´on.

### Proyecto

#### Correr parte 1

```bash
make clean && make final && valgrind ./final
```

### Tests

```bash
```

## Features

- [x] ConstruirGrafo()
- [x] DestruirGrafo()
- [x] NumeroDeVertices()
- [x] NumeroDeLados()
- [x] Delta()
- [x] Grado()
- [x] Color()
- [ ] Vecino()
- [x] AsignarColor()
- [ ] ExtraerColores() - Ver 6.2 del [PDF](PDFs/Parte1ProyectoMDII2024.pdf)
- [ ] ImportarColores() - Ver 6.3 del [PDF](PDFs/Parte1ProyectoMDII2024.pdf)

## Extensiones Visual Studio Code:

- C/C++
- Better Comments
- Comment Anchors
- Trailing Spaces
- vscode-pdf