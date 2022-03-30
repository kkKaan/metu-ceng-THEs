#ifndef FLIGHT_H
#define FLIGHT_H

// DO NOT CHANGE THIS FILE.

#include <iostream>
#include <vector>

#include "Ticket.h"

class Ticket;

class Flight {
public:
    Flight() {}
    Flight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity);

    const std::string &getFlightCode() const;
    const std::string &getDepartureTime() const;
    const std::string &getArrivalTime() const;
    const std::string &getDepartureCity() const;
    const std::string &getArrivalCity() const;
    int getEconomyCapacity() const;
    int getBusinessCapacity() const;
    bool isCompleted() const;

    void setCompleted(bool completed);

    bool addTicket(const Ticket &ticket);

    bool operator<(const Flight &rhs) const;
    bool operator>(const Flight &rhs) const;
    bool operator==(const Flight &rhs) const;
    bool operator!=(const Flight &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Flight &flight);

private:
    std::string flightCode;
    std::string departureTime;
    std::string arrivalTime;
    std::string departureCity;
    std::string arrivalCity;
    int economyCapacity;
    int businessCapacity;
    bool completed;

    std::vector<Ticket> tickets;
};

#endif //FLIGHT_H