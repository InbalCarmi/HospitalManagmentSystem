#include "Date.h"
#include <iostream>
#include <stdexcept>  // Include this for std::invalid_argument

// Private Methods
bool Date::isLeapYear(int year) const {
    if (year % 4 != 0) return false;
    if (year % 100 != 0) return true;
    if (year % 400 != 0) return false;
    return true;
}

bool Date::isValidDate(int day, int month, int year) const {
    if (year < 1 || month < 1 || month > 12 || day < 1) return false;

    static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int maxDay = daysInMonth[month - 1];

    if (month == 2 && isLeapYear(year)) {
        maxDay = 29;
    }

    return day <= maxDay;
}

// Constructors
Date::Date() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_c);

    day = now_tm.tm_mday;
    month = now_tm.tm_mon + 1;
    year = now_tm.tm_year + 1900;
}

Date::Date(int d, int m, int y) {
    if (!isValidDate(d, m, y)) {
        throw std::string("Invalid date");
    }
    day = d;
    month = m;
    year = y;
}

// Getters
int Date::getDay() const {
    return day;
}

int Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

// Setters
void Date::setDay(int d) {
    if (!isValidDate(d, month, year)) {
        throw std::invalid_argument("Invalid day");
    }
    day = d;
}

void Date::setMonth(int m) {
    if (!isValidDate(day, m, year)) {
        throw std::invalid_argument("Invalid month");
    }
    month = m;
}

void Date::setYear(int y) {
    if (!isValidDate(day, month, y)) {
        throw std::invalid_argument("Invalid year");
    }
    year = y;
}

// Operators
bool Date::operator==(const Date& other) const {
    return day == other.day &&
        month == other.month &&
        year == other.year;
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

// Friend Functions
std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.day << "/" << date.month << "/" << date.year;
    return os;
}
