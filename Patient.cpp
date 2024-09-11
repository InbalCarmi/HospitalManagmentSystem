#include <utility>
#include "Patient.h"
#include "Nurse.h"

// Constructor
Patient::Patient(const std::string& firstName, const std::string& lastName, Date dob, Doctor* doc, Department* dept)
    : Person(firstName, lastName, dob), department(dept), dischargeDate(nullptr)
{
    setDoctor(doc);
    hospitalizationDate = Date();
}

// Setters and Getters
bool Patient::setDoctor(Doctor* newDoctor) {
    if (doctor != newDoctor) {
        if (doctor != nullptr) {
            if (!doctor->removePatient(*this))
                return false;
        }

        doctor = newDoctor;
        if (doctor != nullptr)
            doctor->addPatient(*this);
    }
    return true;
}

bool Patient::setDepartment(Department* newDepartment) {
    department = newDepartment;
    return true;
}

void Patient::setDiagnosis(const std::string& newDiagnosis) {
    diagnosis = newDiagnosis;
}

bool Patient::setDischargeDate(Date& newDischargeDate) {
    dischargeDate = &newDischargeDate;
    return true;
}

Nurse* Patient::callNurse() {
    return department->callNurse(*this);
}

// Friend Function
std::ostream& operator<<(std::ostream& os, const Patient& patient) {
    os << static_cast<const Person&>(patient) << std::endl;
    os << "Diagnosis: " << patient.diagnosis << std::endl;
    os << "Hospitalization Date: " << patient.hospitalizationDate << std::endl;
    if (patient.dischargeDate != nullptr)
        os << "Discharge Date: " << *patient.dischargeDate << std::endl;
    if (patient.doctor != nullptr)
        os << "Doctor: " << patient.doctor->getFirstName() << " " << patient.doctor->getLastName() << std::endl;
    if (patient.department != nullptr)
        os << "Department: " << patient.department->getNameOfDepartment() << std::endl;
    return os;
}
