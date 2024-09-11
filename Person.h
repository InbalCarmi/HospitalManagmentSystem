#pragma once

#include <iostream>
#include "Date.h"

class Person {
protected:
    static int counter;
    std::string firstName;
    std::string lastName;
    int id;
    Date dateOfBirth;

    Person(const std::string& firstName, const std::string& lastName, const Date& dob);

public:
    // Setters
    void setFirstName(const std::string& n);
    void setLastName(const std::string& n);

    // Getters
    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    int getId() const { return id; }
    Date getDateOfBirth() const { return dateOfBirth; }

    // Virtual Functions
    virtual void toOs(std::ostream& os) const {}

    // Equality Operators
    bool operator==(const Person& other) const;
    bool operator!=(const Person& other) const;

    // Friend Functions
    friend std::ostream& operator<<(std::ostream& os, const Person& person);

    // Destructor
    virtual ~Person() = default;
};
