#pragma once

#include <iostream>
#include <string>

using namespace std;

class Building
{
protected:
    string address;
    string nameOfBuilding;

    // Protected constructor
    Building(const string& name, const string& address);

public:
    // Public member functions
    void setBuildingName(const string& name);
    string getBuildingName() const;
    string getAddress() const;
    void setAddress(const string& add);

    // Virtual function for output
    virtual void toOs(ostream& os) const {}

    // Friend function for output
    friend ostream& operator<<(ostream& os, const Building& building);
};
