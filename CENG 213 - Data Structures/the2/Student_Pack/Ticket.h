#ifndef TICKET_H
#define TICKET_H

// DO NOT CHANGE THIS FILE.

#include <iostream>

#include "Passenger.h"
#include "Flight.h"

enum TicketType {economy, business};

class Flight;

class Ticket {
public:
	Ticket() {}
	Ticket(Passenger *passenger, Flight *flight, TicketType ticketType);

    int getTicketId() const;
    Passenger *getPassenger() const;
    Flight *getFlight() const;
    TicketType getTicketType() const;
    
	friend std::ostream &operator<<(std::ostream &os, const Ticket &ticket);

private:
	int ticketId;
    Passenger *passenger;
    Flight *flight;
    TicketType ticketType;
};

#endif //TICKET_H
