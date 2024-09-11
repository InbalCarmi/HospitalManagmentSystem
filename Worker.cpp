#include <iostream>
using namespace std;

#include "Worker.h"

// Constructors
Worker::Worker(const string& firstName, const string& lastName, Date dof, int seniority, int salary, double numOfHours, bool onShift)
    : Person(firstName, lastName, dof), seniority(seniority), salary(salary), numOfHours(numOfHours), onShift(onShift)
{
}

// Setters
bool Worker::setSeniority(const int seniority)
{
    if (seniority < 0)
        return false;
    this->seniority = seniority;
    return true;
}

bool Worker::setSalary(const int salary)
{
    this->salary = salary;
    return true;
}

bool Worker::setNumOfHours(const double numOfHours)
{
    this->numOfHours = numOfHours;
    return true;
}

bool Worker::setOnShift(bool isOnShift)
{
    this->onShift = isOnShift;
    return true;
}

// Member Functions
void Worker::toOs(ostream& os) const
{
    os << "Seniority: " << seniority;
    os << ", Salary: " << salary;
    os << ", Number of Hours: " << numOfHours;
    os << ", On Shift: " << (onShift ? "Yes" : "No") << std::endl;
}

// Comparison Operators
bool Worker::operator==(const Worker& other) const
{
    return static_cast<const Person&>(*this) == static_cast<const Person&>(other) &&
        seniority == other.seniority &&
        salary == other.salary &&
        numOfHours == other.numOfHours &&
        onShift == other.onShift;
}

bool Worker::operator!=(const Worker& other) const
{
    return !(*this == other);
}
