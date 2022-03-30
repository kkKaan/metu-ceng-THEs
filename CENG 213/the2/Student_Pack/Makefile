CC=g++
CFLAGS=-c -ansi -Wall -pedantic-errors -O0

all: bst ars

ars: main_ars.o flight.o passenger.o ticket.o ars.o
	$(CC) main_ars.o flight.o passenger.o ticket.o ars.o -o ars

bst: main_bst.o
	$(CC) main_bst.o -o bst

main_ars.o: main_ars.cpp
	$(CC) $(CFLAGS) main_ars.cpp -o main_ars.o

main_bst.o: main_bst.cpp
	$(CC) $(CFLAGS) main_bst.cpp -o main_bst.o

flight.o: Flight.cpp Flight.h
	$(CC) $(CFLAGS) Flight.cpp -o flight.o

passenger.o: Passenger.cpp Passenger.h
	$(CC) $(CFLAGS) Passenger.cpp -o passenger.o

ticket.o: Ticket.cpp Ticket.h
	$(CC) $(CFLAGS) Ticket.cpp -o ticket.o

ars.o: AirlineReservationSystem.cpp AirlineReservationSystem.h Flight.cpp Flight.h Passenger.cpp Passenger.h Ticket.cpp Ticket.h BST.h BSTNode.h Queue.h QueueException.h
	$(CC) $(CFLAGS) AirlineReservationSystem.cpp -o ars.o

clean:
	rm *o
	rm bst
	rm ars
