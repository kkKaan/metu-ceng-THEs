#ifndef PASSENGER_H
#define PASSENGER_H

// DO NOT CHANGE THIS FILE.

#include <iostream>

class Passenger {
public:
    Passenger() {}
    Passenger(std::string firstname, std::string lastname);

    const std::string &getFirstname() const;
    const std::string &getLastname() const;

    bool operator<(const Passenger &rhs) const;
    bool operator>(const Passenger &rhs) const;
    bool operator==(const Passenger &rhs) const;
    bool operator!=(const Passenger &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Passenger &passenger);

private:
    std::string firstname;
    std::string lastname;
};

#endif //PASSENGER_H
