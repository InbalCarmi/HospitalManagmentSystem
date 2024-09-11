#include "Building.h"
#include <cstring> // Include <cstring> instead of <string.h> for C++ compatibility
#include <iostream>

// Constructor
Building::Building(const std::string& name, const std::string& address)
    : nameOfBuilding(name), address(address) {}

// Setters and Getters
void Building::setBuildingName(const std::string& name) {
    this->nameOfBuilding = name;
}

std::string Building::getBuildingName() const {
    return nameOfBuilding;
}

std::string Building::getAddress() const {
    return address;
}

void Building::setAddress(const std::string& add) {
    this->address = add;
}

// Move Constructor (commented out)
// Building::Building(Building&& other) noexcept
//     : address(other.address), nameOfBuilding(other.nameOfBuilding)
// {
//     other.address = nullptr;
//     other.nameOfBuilding = nullptr;
// }

// Output Stream Operator
std::ostream& operator<<(std::ostream& os, const Building& building) {
    os << "Building Address: " << building.address << "\n";
    os << "Building Name: " << building.nameOfBuilding << "\n";
    building.toOs(os); // Assuming toOs is a method in Building
    return os;
}
