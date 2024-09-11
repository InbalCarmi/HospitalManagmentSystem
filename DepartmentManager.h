#pragma once

#include "Doctor.h"
#include "Researcher.h"

class DepartmentManager : public Researcher, public Doctor {
private:
    int bonus;

public:
    // Constructors
    DepartmentManager(const Researcher& r, const Doctor& d, int bonus);

    // Setters and Getters
    void setBonus(int bonus);
    int getBonus() const;

    // Methods
    void toOs(ostream& os) const;

    // Operators
    bool operator==(const DepartmentManager& other) const;
};
