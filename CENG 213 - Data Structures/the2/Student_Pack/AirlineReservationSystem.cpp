#include "AirlineReservationSystem.h"

void AirlineReservationSystem::addPassenger(const std::string &firstname, const std::string &lastname) 
{
    /* TODO */

    Passenger p1(firstname, lastname);
    (this->passengers).insert(p1);
}

Passenger *AirlineReservationSystem::searchPassenger(const std::string &firstname, const std::string &lastname) 
{
    /* TODO */

    Passenger p1(firstname, lastname);
    return &(((this->passengers).search(p1))->data);
}

void AirlineReservationSystem::addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) 
{
    /* TODO */

    Flight f1(flightCode, departureTime, arrivalTime, departureCity, arrivalCity, economyCapacity, businessCapacity);
    (this->flights).insert(f1);
}

void AirlineReservationSystem::searchRecF(const std::string &departureCity, const std::string &arrival, BSTNode<Flight> *rooty, std::vector<Flight *> &fl)
{
    if(!rooty){return;}
    if((rooty->data).getDepartureCity() == departureCity && (rooty->data).getArrivalCity() == arrival)
    {
        fl.push_back(&(rooty->data));
    }
    searchRecF(departureCity, arrival, rooty->left, fl);
    searchRecF(departureCity, arrival, rooty->right, fl);
}

std::vector<Flight *> AirlineReservationSystem::searchFlight(const std::string &departureCity, const std::string &arrivalCity) 
{
    /* TODO */ 
    std::vector<Flight *> fl;
    searchRecF(departureCity, arrivalCity, (this->flights).getRoot(), fl);
    return fl;
}

Flight *AirlineReservationSystem::searchRecFId(const std::string &flightCode, BSTNode<Flight> *rooty)
{
    if(!rooty){return NULL;}

    if((rooty->data).getFlightCode() < flightCode){return searchRecFId(flightCode, rooty->right);}
    else if((rooty->data).getFlightCode() > flightCode){return searchRecFId(flightCode, rooty->left);}
    return &(rooty->data);
}

void AirlineReservationSystem::issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType)
{
    /* TODO */
    
    Passenger *p1 = searchPassenger(firstname, lastname);
    if(!p1){return;}

    Flight *f1 = searchRecFId(flightCode, (this->flights).getRoot());
    if(!f1){return;}

    Ticket t1(p1, f1, ticketType);

    f1->addTicket(t1);
}

void AirlineReservationSystem::saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType)
{
    /* TODO */
    
    Passenger *p1 = searchPassenger(firstname, lastname);
    if(!p1){return;}

    Flight *f1 = searchRecFId(flightCode, (this->flights).getRoot());
    if(!f1){return;}

    Ticket t1(p1, f1, ticketType);
    (this->freeTicketRequests).enqueue(t1);
}

void AirlineReservationSystem::executeTheFlight(const std::string &flightCode)
{
    /* TODO */
    
    Flight *f1 = searchRecFId(flightCode, (this->flights).getRoot());
    int size = freeTicketRequests.size();
    
    if(!f1){return;}

    for(int i = 0; i < size; ++i)
    {
        Ticket t1 = freeTicketRequests.dequeue();

        if(t1.getFlight() == f1)
        {
            if(f1->addTicket(t1)){continue;}
            freeTicketRequests.enqueue(t1);
        }
        else{freeTicketRequests.enqueue(t1);}
    }
    f1->setCompleted(true);
}

void AirlineReservationSystem::print() const {
    std::cout << "# Printing the airline reservation system ..." << std::endl;

    std::cout << "# Passengers:" << std::endl;
    passengers.print(inorder);

    std::cout << "# Flights:" << std::endl;
    flights.print(inorder);

    std::cout << "# Free ticket requests:" << std::endl;
    freeTicketRequests.print();

    std::cout << "# Printing is done." << std::endl;
}
