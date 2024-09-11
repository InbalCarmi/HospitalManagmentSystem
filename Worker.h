#pragma once

using namespace std;

#include "Visitable.h"
#include "Person.h"

class Worker : public Person, public Visitable
{
private:
    int seniority;
    int salary;
    double numOfHours;
    bool onShift;

public:
    // Constructors
    Worker(const string& firstName, const string& lastName, Date dof, int seniority, int salary, double numOfHours, bool onShift);

    // Destructor
    virtual ~Worker() = default;

    // Setters
    bool setSeniority(const int seniority);
    bool setSalary(const int salary);
    bool setNumOfHours(const double numOfHours);
    bool setOnShift(bool isOnShift);

    // Getters
    int getSeniority() const { return seniority; }
    int getSalary() const { return salary; }
    double getNumOfHours() const { return numOfHours; }
    bool getIsOnShift() const { return onShift; }

    // Member Functions
    void giveRaise(int money) { salary += money; }
    void giveHolidayGift(int money) { salary += money; }
    virtual void toOs(ostream& os) const override;

    // Visitor Pattern
    virtual void accept(Visitor* visitor) override { visitor->visit(this); }

    // Comparison Operators
    bool operator==(const Worker& other) const;
    bool operator!=(const Worker& other) const;
};
