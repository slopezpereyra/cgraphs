CC=gcc
CFLAGS = -Wall -Wextra -O3 -std=c99
# PATH_P1 = src/Parte1/
OBJS_P1 = main.o APIG24.o

VALGRIND = valgrind --leak-check=full --show-reachable=yes

.PHONY: clean

# main: main.c
# 		$(CC) $(CFLAGS) -o main main.c

parte1: test_graphs

final:
		$(CC) $(CFLAGS) -c main.c -o final

# Necesario, no tocar.
main.o:
		$(CC) $(CFLAGS) -c main.c

# Realiza pruebas cortas sobre casos que deben funcionar.
# Correr con make
test_graphs: $(OBJS_P1)
		$(CC) $(CFLAGS) -o final $(OBJS_P1)
		@echo "\n\tCorriendo K5.txt"
		./final < K5.txt
		@echo "\n\tCorriendo F.txt"
		./final < F.txt
		# @echo "\n\tCorriendo 10_20.txt"
		# ./final < 10_20.txt
		@echo "\n\tCorriendo ErrorG.txt"
		./final < ErrorG.txt
		@echo "\n\tCorriendo NoEdge.txt"
		./final < NoEdge.txt

# Necesario, no tocar.
APIG24.o: APIG24.h EstructuraGrafo24.h
		$(CC) $(CFLAGS) -c APIG24.c

clean:
	rm -f *.o final main a.out

# include all dependencies
# -include $(OBJS:%.o=%.d)