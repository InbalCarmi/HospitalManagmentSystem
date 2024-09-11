#include "InpatientDepartment.h"

// Constructor
InpatientDepartment::InpatientDepartment(const std::string& name, const std::string& addr)
    : Building(name, addr) {
}

// Add a Department
void InpatientDepartment::addDepartment(const Department& department) {
    // Check if the department already exists in the list
    if (std::find(allDepartments.begin(), allDepartments.end(), &department) == allDepartments.end()) {
        allDepartments.push_back(new Department(department)); // Deep copy the department
    }
}

// Get Departments
std::list<Department*>& InpatientDepartment::getDepartments() {
    return allDepartments;
}


// Get Number of Departments
int InpatientDepartment::getNumOfDepartments() const {
    return (int)allDepartments.size();
}

// Output Stream Operator
void InpatientDepartment::toOs(std::ostream& os) const {
    os << "Number of Departments: " << getNumOfDepartments() << "\n";
    if (!allDepartments.empty()) {
        os << "Departments:\n";
        for (const auto& department : allDepartments) {
            os << *department << "\n";
        }
    }
    os << std::endl;
}
