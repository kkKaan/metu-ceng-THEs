# Airline Reservation System

This project implements an Airline Reservation System with features such as managing passengers, flights, and ticket bookings.

## Table of Contents

- [BST.h](#bsth)
- [AirlineReservationSystem.cpp](#airlinereservationsystemcpp)
- [Flight.cpp](#flightcpp)
- [Passenger.cpp](#passengercpp)
- [Ticket.cpp](#ticketcpp)

### BST.h

#### Binary Search Tree (BST) Class

`BST` is a templated binary search tree class that allows you to perform various operations like insertion, deletion, searching, and traversal. It uses the `BSTNode` class internally to represent tree nodes.

##### Public Member Functions

- `BST()`: Constructor for creating an empty binary search tree.
- `BST(const BST<T> &obj)`: Copy constructor.
- `~BST()`: Destructor for cleaning up the tree.
- `BSTNode<T> *getRoot() const`: Get the root node of the tree.
- `bool isEmpty() const`: Check if the tree is empty.
- `bool contains(BSTNode<T> *node) const`: Check if the tree contains a specific node.
- `void insert(const T &data)`: Insert data into the tree.
- `void remove(const T &data)`: Remove data from the tree.
- `void removeAllNodes()`: Remove all nodes from the tree.
- `BSTNode<T> *search(const T &data) const`: Search for a node with specific data.
- `BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const`: Get the successor node based on a specified traversal plan.
- `void print(TraversalPlan tp = inorder) const`: Print the tree using a specified traversal plan.
- `BST<T> &operator=(const BST<T> &rhs)`: Assignment operator.

##### Private Member Functions

- Several private member functions to assist in tree manipulation, including recursive insertions, deletions, clear operations, and finding minimum and maximum nodes.

### AirlineReservationSystem.cpp

#### Airline Reservation System Class

`AirlineReservationSystem` is a class that manages passengers, flights, ticket bookings, and free ticket requests using a binary search tree for passengers and flights.

##### Public Member Functions

- `void addPassenger(const std::string &firstname, const std::string &lastname)`: Add a passenger to the system.
- `Passenger *searchPassenger(const std::string &firstname, const std::string &lastname)`: Search for a passenger by name.
- `void addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity)`: Add a flight to the system.
- `std::vector<Flight *> searchFlight(const std::string &departureCity, const std::string &arrivalCity)`: Search for flights based on departure and arrival cities.
- `void issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType)`: Issue a ticket to a passenger for a flight.
- `void saveFreeTicketRequest(const std::string &firstname, the std.::string &lastname, the std.::string &flightCode, the TicketType ticketType)`: Save a free ticket request from a passenger.
- `void executeTheFlight(const std::string &flightCode)`: Execute a flight, fulfilling free ticket requests.
- `void print() const`: Print information about passengers, flights, and free ticket requests.

### Flight.cpp

#### Flight Class

`Flight` represents flight details such as flight code, departure time, arrival time, and passenger capacity. It also includes methods for managing tickets.

##### Public Member Functions

- `Flight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity)`: Constructor for creating a flight.
- ... (other functions from Flight.cpp)

### Passenger.cpp

#### Passenger Class

`Passenger` represents passenger information, including first name and last name.

##### Public Member Functions

- `Passenger(std::string firstname, std::string lastname)`: Constructor for creating a passenger.
- ... (other functions from Passenger.cpp)

### Ticket.cpp

#### Ticket Class

`Ticket` represents a ticket associated with a passenger and a flight. It includes a unique ticket ID and ticket type.

##### Public Member Functions

- `Ticket(Passenger *passenger, Flight *flight, TicketType ticketType)`: Constructor for creating a ticket.
- ... (other functions from Ticket.cpp)

---

This README provides an overview of the Airline Reservation System project, including the structure of the code files and their functionalities. You can explore the individual code files for more detailed information and implementation details.
