CC=gcc
CFLAGS = -Wall -Wextra -O3 -std=c99
# PATH_P1 = src/Parte1/
# OBJS_P1 = $(PATH_P1)main.o
# $(PATH_P1)main.o $(PATH_P1)APIG24.o $(PATH_P1)EstructuraGrafo24.o

.PHONY: clean

# main: main.c
# 		$(CC) $(CFLAGS) -o main main.c

all: apig24

final:
		$(CC) $(CFLAGS) APIG24.c -o final

apig24: APIG24.o EstructuraGrafo24.h
		$(CC) $(CFLAGS) -o LABP1

APIG24.o: APIG24.c
		$(CC) $(CFLAGS) -c APIG24.c

clean:
	rm -f *.o LABP1 final main a.out

# include all dependencies
# -include $(OBJS:%.o=%.d)