CC=gcc
CFLAGS = -Wall -Wextra -O3 -std=c99 -g
# PATH_P1 = src/Parte1/
OBJS_P1 = main.o APIG24.o greedy.o queue.o search.o generator.o utils.o

VALGRIND_FLAGS = --leak-check=full --show-reachable=yes
VALGRIND_CMD = $(if $(VALGRIND),valgrind $(VALGRIND_FLAGS),)

.PHONY: clean

# main: main.c
# 		$(CC) $(CFLAGS) -o main main.c

parte1: test_graphs

final: $(OBJS_P1)
		$(CC) $(CFLAGS) -o final $(OBJS_P1)

# Necesario, no tocar.
main.o:
		$(CC) $(CFLAGS) -c src/main.c

# Realiza pruebas cortas sobre casos que deben funcionar.
# Correr con make
test_graphs: $(OBJS_P1)
		$(CC) $(CFLAGS) -o final $(OBJS_P1)
		@echo "\n\tCorriendo K5.txt"
		$(VALGRIND_CMD) ./final < graphs/K5.txt
		@echo "\n\tCorriendo F.txt"
		$(VALGRIND_CMD) ./final < graphs/F.txt
		@echo "\n\tCorriendo ErrorG.txt"
		$(VALGRIND_CMD) ./final < graphs/ErrorG.txt
		@echo "\n\tCorriendo NoEdge.txt"
		$(VALGRIND_CMD) ./final < graphs/NoEdge.txt
		@echo "\n\tCorriendo Golomb.txt"
		$(VALGRIND_CMD) ./final < graphs/Golomb.txt
		@echo "\n\tCorriendo C5.txt"
		$(VALGRIND_CMD) ./final < graphs/C5.txt

test_graphs_2: $(OBJS_P1)
		$(CC) $(CFLAGS) -o final $(OBJS_P1)
		@echo "\n\tCorriendo 10_20.txt"
		$(VALGRIND_CMD) ./final < graphs/10_20.txt

test_64_graph: $(OBJS_P1)
		$(CC) $(CFLAGS) -o final $(OBJS_P1)
		@echo "\n\tCorriendo 64gb.txt"
		$(VALGRIND_CMD) ./final < graphs/64gb.txt

gdb_run_64_graph: $(OBJS_P1)
		$(CC) $(CFLAGS) -o final $(OBJS_P1)
		gdb ./final

# Necesario, no tocar.
APIG24.o: src/APIG24.h src/EstructuraGrafo24.h 
		$(CC) $(CFLAGS) -c src/APIG24.c

greedy.o: src/APIG24.h src/EstructuraGrafo24.h src/greedy.h
		$(CC) $(CFLAGS) -c src/greedy.c
queue.o: src/queue.h
		$(CC) $(CFLAGS) -c src/queue.c
search.o: src/APIG24.h src/search.h
		$(CC) $(CFLAGS) -c src/search.c
generator.o: src/APIG24.h src/generator.h
		$(CC) $(CFLAGS) -c src/generator.c
utils.o: src/APIG24.h src/utils.h
		$(CC) $(CFLAGS) -c src/utils.c

clean:
	rm -f *.o final main a.out

# include all dependencies
# -include $(OBJS:%.o=%.d)
