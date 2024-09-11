#include <iostream>
#include <utility> // For std::swap
#include "Person.h"

int Person::counter = 0;

// Constructor
Person::Person(const std::string& firstName, const std::string& lastName, const Date& dob)
    : dateOfBirth(dob), firstName(firstName), lastName(lastName), id(++counter) {}

// Equality Operator
bool Person::operator==(const Person& other) const {
    return firstName == other.firstName &&
        lastName == other.lastName &&
        id == other.id &&
        dateOfBirth == other.dateOfBirth;
}

// Inequality Operator
bool Person::operator!=(const Person& other) const {
    return !(*this == other);
}

// Setters
void Person::setFirstName(const std::string& n) {
    firstName = n;
}

void Person::setLastName(const std::string& n) {
    lastName = n;
}

// Stream Insertion Operator
std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << "First Name: " << person.firstName
        << ", Last Name: " << person.lastName
        << ", ID: " << person.id
        << ", Date of Birth: " << person.dateOfBirth << std::endl;
    person.toOs(os);
    return os;
}
