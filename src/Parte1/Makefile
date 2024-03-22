CC=gcc
CFLAGS = -Wall -Wextra -O3 -std=c99
PATH_P1 = src/Parte1/
# OBJS_P1 = $(PATH_P1)main.o
# $(PATH_P1)main.o $(PATH_P1)APIG24.o $(PATH_P1)EstructuraGrafo24.o

# all: main.o
# 		$(CC) $(CFLAGS) -o main.o

# $(CC) $(CFLAGS) -c main.c

.PHONY: clean

main: main.c
		$(CC) $(CFLAGS) -o main main.c

run:
		./main

clean:
		rm -f all main.o main