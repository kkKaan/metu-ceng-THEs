CC=g++
LFLAGS=
CFLAGS=-c -g -ansi -Wall -pedantic-errors -O0

all: Graph HashTable METUMaps

# EXECUTABLES
METUMaps: main_METUMaps.o Graph.o HashTable.o METUMaps.o
	$(CC) $(LFLAGS) main_METUMaps.o Graph.o HashTable.o METUMaps.o -o METUMaps

Graph: main_Graph.o Graph.o
	$(CC) $(LFLAGS) main_Graph.o Graph.o -o Graph

HashTable: main_HashTable.o HashTable.o
	$(CC) $(LFLAGS) main_HashTable.o HashTable.o -o HashTable

# MAIN FUNCTIONS
main_METUMaps.o: main_METUMaps.cpp METUMaps.h
	$(CC) $(CFLAGS) main_METUMaps.cpp -o main_METUMaps.o

main_Graph.o: main_Graph.cpp Graph.h
	$(CC) $(CFLAGS) main_Graph.cpp -o main_Graph.o

main_HashTable.o: main_HashTable.cpp HashTable.h
	$(CC) $(CFLAGS) main_HashTable.cpp -o main_HashTable.o

# INDIVIDUAL OBJECTS
METUMaps.o:	METUMaps.cpp Graph.h HashTable.h METUMaps.h GraphExceptions.h
	$(CC) $(CFLAGS) METUMaps.cpp -o METUMaps.o

Graph.o: Graph.cpp Graph.h GraphExceptions.h
	$(CC) $(CFLAGS) Graph.cpp -o Graph.o

HashTable.o: HashTable.cpp HashTable.h
	$(CC) $(CFLAGS) HashTable.cpp -o HashTable.o

# Clean
clean:
	rm -f *.o
	rm -f METUMaps
	rm -f Graph
	rm -f HashTable