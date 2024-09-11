#pragma once

#include <chrono>
#include <iostream>

class Date
{
private:
    int day;
    int month;
    int year;

    // Private methods
    bool isLeapYear(int year) const;
    bool isValidDate(int day, int month, int year) const;

public:
    // Constructors
    Date();
    Date(int d, int m, int y);

    // Getters
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    // Setters
    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);

    // Operators
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;

    // Friend functions
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
};
