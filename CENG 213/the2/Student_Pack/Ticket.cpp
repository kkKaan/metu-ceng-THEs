#include "Ticket.h"

// DO NOT CHANGE THIS FILE.

Ticket::Ticket(Passenger *passenger, Flight *flight, TicketType ticketType) {
    static int ticketId = 1;

    this->passenger = passenger;
    this->flight = flight;
    this->ticketType = ticketType;
    this->ticketId = ticketId;

    ticketId += 1;
}

int Ticket::getTicketId() const {
    return ticketId;
}

Passenger *Ticket::getPassenger() const {
    return passenger;
}

Flight *Ticket::getFlight() const {
    return flight;
}

TicketType Ticket::getTicketType() const {
    return ticketType;
}

std::ostream &operator<<(std::ostream &os, const Ticket &ticket) {
    os << "Ticket(ticketId: " << ticket.ticketId;
    os << ", passenger: " << ticket.passenger->getFirstname() << " " << ticket.passenger->getLastname();
    os << ", flight: " << ticket.flight->getFlightCode();
    os << ", ticketType: " << (ticket.ticketType == economy ? "economy" : "business") << ")";
    return os;
}

