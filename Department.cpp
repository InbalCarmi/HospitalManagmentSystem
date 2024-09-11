#include <string.h>
#include "Patient.h"
#include "Department.h"
#include "Nurse.h"

// Constructors
Department::Department(string& nameOfDepartment, DepartmentManager& departmentManager)
    : departmentManager(&departmentManager)
{
    setNameOfDepartment(nameOfDepartment);
}

// Setters and Getters
void Department::setNameOfDepartment(const string& nameOfDepartment)
{
    this->nameOfDepartment = nameOfDepartment;
}

string Department::getNameOfDepartment() const
{
    return nameOfDepartment;
}

void Department::setDepartmentManager(DepartmentManager* departmentManager)
{
    this->departmentManager = departmentManager;
}

DepartmentManager* Department::getDepartmentManager() const
{
    return departmentManager;
}

// Methods to manage workers and patients
bool Department::addWorkerToDepartment(Worker& worker)
{
    staffOfDepartment.push_back(&worker);
    return true;
}

bool Department::removeWorkerFromDepartment(Worker& worker)
{
    auto it = std::find(staffOfDepartment.begin(), staffOfDepartment.end(), &worker);
    if (it != staffOfDepartment.end()) {
        staffOfDepartment.erase(it);
        return true;
    }
    return false;
}

bool Department::addPatient(Patient& patient)
{
    patientsOfDepartment.push_back(&patient);
    return true;
}

bool Department::removePatient(Patient& patient)
{
    auto it = std::find(patientsOfDepartment.begin(), patientsOfDepartment.end(), &patient);
    if (it != patientsOfDepartment.end()) {
        patientsOfDepartment.erase(it);

        // Remove patient from all nurses' lists
        for (auto staffIt = staffOfDepartment.begin(); staffIt != staffOfDepartment.end(); ++staffIt) {
            Nurse* nurse = dynamic_cast<Nurse*>(*staffIt);
            if (nurse) {
                nurse->removePatient(patient);
            }
        }
        return true;
    }
    return false;
}

list<Worker*> Department::getAllstaffOfDepartment() const
{
    return staffOfDepartment;
}

list<Worker*>& Department::getAllstaffOfDepartment()
{
    return staffOfDepartment;
}

list<Patient*> Department::getAllpatientsOfDepartment() const
{
    return patientsOfDepartment;
}

int Department::getNumOfPatientsOfDepartment() const
{
    return (int)patientsOfDepartment.size();
}

int Department::getNumOfStaffOfDepartment() const
{
    return (int)staffOfDepartment.size();
}

Nurse* Department::callNurse(Patient& patient)
{
    Nurse* assignedNurse = nullptr;

    for (auto it = staffOfDepartment.begin(); it != staffOfDepartment.end(); ++it) {
        Nurse* nurse = dynamic_cast<Nurse*>(*it);
        if (nurse && nurse->getIsOnShift()) {
            bool isCaringForPatient = false;
            for (Patient* caredPatient : nurse->getPatientsGotCare()) {
                if (*caredPatient == patient) {
                    isCaringForPatient = true;
                    break;
                }
            }
            if (isCaringForPatient) {
                return nurse;
            }
            assignedNurse = nurse;
        }
    }

    if (assignedNurse) {
        assignedNurse->addPatient(patient);
        return assignedNurse;
    }
    return nullptr;
}

// Visitor pattern
void Department::accept(Visitor* visitor)
{
    for (auto it = staffOfDepartment.begin(); it != staffOfDepartment.end(); ++it) {
        (*it)->accept(visitor);
    }
}

// Friend functions
ostream& operator<<(ostream& os, const Department& dept)
{
    os << "Department Name: " << dept.nameOfDepartment << endl;
    if (dept.departmentManager) {
        os << "Department Manager: " << dept.departmentManager->getFirstName() << " " << dept.departmentManager->getLastName() << endl;
    }
    else {
        os << "Department Manager: None" << endl;
    }
    os << "Number of Patients: " << dept.getNumOfPatientsOfDepartment() << endl;

    if (!dept.patientsOfDepartment.empty()) {
        os << "Patients: ";
        for (const Patient* patient : dept.patientsOfDepartment) {
            os << patient->getFirstName() << " " << patient->getLastName() << ", ";
        }
        os << endl;
    }

    os << "Number of Staff: " << dept.getNumOfStaffOfDepartment() << endl;
    for (const Worker* worker : dept.staffOfDepartment) {
        if (const Doctor* doctor = dynamic_cast<const Doctor*>(worker)) {
            os << "Doctor - " << doctor->getFirstName() << " " << doctor->getLastName() << endl;
        }
        else if (const Nurse* nurse = dynamic_cast<const Nurse*>(worker)) {
            os << "Nurse - " << nurse->getFirstName() << " " << nurse->getLastName() << endl;
        }
        else if (const Researcher* researcher = dynamic_cast<const Researcher*>(worker)) {
            os << "Researcher - " << researcher->getFirstName() << " " << researcher->getLastName() << endl;
        }
    }

    os << endl;
    return os;
}
