# Compiler and flags
CC=gcc
CFLAGS = -Wall -Wextra -O3 -std=c99 -g
OBJS_P1 = api.o coloring.o queue.o heap.o search.o generator.o utils.o dijkstra.o prim.o

VALGRIND_FLAGS = --leak-check=full --show-reachable=yes
VALGRIND_CMD = $(if $(VALGRIND),valgrind $(VALGRIND_FLAGS),)

.PHONY: clean

parte1: test_graphs

final: main.o $(OBJS_P1)
	$(CC) $(CFLAGS) -o final main.o $(OBJS_P1)


# Compile and run the tests in test_generator.c
test_graphs: test_utils.o test_generator.o test_search.o test_api.o test_dijkstra.o test_prim.o test_network.o $(OBJS_P1)
	$(CC) $(CFLAGS) -o test_graphs test_utils.o $(OBJS_P1)
	@echo "\nRunning utilities tests..."
	$(VALGRIND_CMD) ./test_graphs
	$(CC) $(CFLAGS) -o test_graphs test_api.o $(OBJS_P1)
	@echo "\nRunning API tests..."
	$(VALGRIND_CMD) ./test_graphs
	$(CC) $(CFLAGS) -o test_graphs test_network.o $(OBJS_P1)
	@echo "\nRunning API tests for flow networks..."
	$(VALGRIND_CMD) ./test_graphs
	$(CC) $(CFLAGS) -o test_graphs test_search.o $(OBJS_P1)
	@echo "\nRunning tests for search functions..."
	$(VALGRIND_CMD) ./test_graphs
	$(CC) $(CFLAGS) -o test_graphs test_generator.o $(OBJS_P1)
	@echo "\nRunning tests for generator functions..."
	$(VALGRIND_CMD) ./test_graphs
	$(CC) $(CFLAGS) -o test_graphs test_dijkstra.o $(OBJS_P1)
	@echo "\nRunning tests for Dijkstra..."
	$(VALGRIND_CMD) ./test_graphs
	$(CC) $(CFLAGS) -o test_graphs test_prim.o $(OBJS_P1)
	@echo "\nRunning tests for Prim..."
	$(VALGRIND_CMD) ./test_graphs

# Individual object file compilation
main.o: c/main.c
	$(CC) $(CFLAGS) -c c/main.c
api.o: c/api.c c/api.h c/graphStruct.h
	$(CC) $(CFLAGS) -c c/api.c
coloring.o: c/coloring.c c/api.h c/graphStruct.h c/coloring.h
	$(CC) $(CFLAGS) -c c/coloring.c
queue.o: c/queue.c c/queue.h
	$(CC) $(CFLAGS) -c c/queue.c
heap.o: c/heap.c c/heap.h
	$(CC) $(CFLAGS) -c c/heap.c
search.o: c/search.c c/api.h c/search.h
	$(CC) $(CFLAGS) -c c/search.c
generator.o: c/generator.c c/api.h c/generator.h
	$(CC) $(CFLAGS) -c c/generator.c
utils.o: c/utils.c c/api.h c/utils.h
	$(CC) $(CFLAGS) -c c/utils.c
dijkstra.o: c/dijkstra.c
	$(CC) $(CFLAGS) -c c/dijkstra.c
prim.o: c/prim.c
	$(CC) $(CFLAGS) -c c/prim.c
test_generator.o: 
	$(CC) $(CFLAGS) -c c/test_generator.c
test_search.o: 
	$(CC) $(CFLAGS) -c c/test_search.c
test_api.o: 
	$(CC) $(CFLAGS) -c c/test_api.c
test_utils.o: 
	$(CC) $(CFLAGS) -c c/test_utils.c
test_network.o: 
	$(CC) $(CFLAGS) -c c/test_network.c
test_dijkstra.o: 
	$(CC) $(CFLAGS) -c c/test_dijkstra.c
test_prim.o: 
	$(CC) $(CFLAGS) -c c/test_prim.c



clean:
	rm -f *.o final main a.out test_graphs
