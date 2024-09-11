#pragma once

#include <list>
#include "Building.h"
#include "Department.h"

// The InpatientDepartment class represents an inpatient department in a hospital
class InpatientDepartment : public Building {
private:
    std::list<Department*> allDepartments;

public:
    // Constructors and Destructor
    InpatientDepartment(const std::string& name, const std::string& addr);

    // Member Functions
    void addDepartment(const Department& department);
    std::list<Department*>& getDepartments();
    int getNumOfDepartments() const;
    virtual void toOs(std::ostream& os) const override;
};
