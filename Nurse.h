#pragma once

#include <list>
#include "Worker.h"
#include "Patient.h"
#include "Doctor.h"

class Nurse : public Worker {
private:
    std::list<Patient*> patientsGotCare;

public:
    // Constructors
    Nurse(const Worker& base);
    Nurse(const Worker& base, const std::list<Patient*>& patients);

    // Member functions
    bool addPatient(Patient& patient);
    bool removePatient(Patient& patient);
    bool callDoctor(const Doctor* doctor) const; // Assuming it does not modify the object
    std::list<Patient*> getPatientsGotCare() const { return patientsGotCare; }
    int getNumOfPatientsGotCare() const { return (int)patientsGotCare.size(); }
    void toOs(std::ostream& os) const;
};
