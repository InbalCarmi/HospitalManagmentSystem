#pragma once

#include <ostream>
#include <list>
#include <string>

using namespace std;

#include "Person.h"
#include "DepartmentManager.h"
#include "Worker.h"

// Forward declarations
class Nurse;
class Patient;


class Department
{
private:
    string nameOfDepartment;
    DepartmentManager* departmentManager;
    list<Patient*> patientsOfDepartment;
    list<Worker*> staffOfDepartment;

public:
    // Constructors
    Department(string& nameOfDepartment, DepartmentManager& departmentManager);

    // Setters and Getters
    void setNameOfDepartment(const string& nameOfDepartment);
    string getNameOfDepartment() const;

    void setDepartmentManager(DepartmentManager* departmentManager);
    DepartmentManager* getDepartmentManager() const;

    // Methods to manage workers and patients
    bool addWorkerToDepartment(Worker& worker);
    bool removeWorkerFromDepartment(Worker& worker);

    bool addPatient(Patient& patient);
    bool removePatient(Patient& patient);

    list<Worker*> getAllstaffOfDepartment() const;
    list<Worker*>& getAllstaffOfDepartment();

    list<Patient*> getAllpatientsOfDepartment() const;

    int getNumOfPatientsOfDepartment() const;
    int getNumOfStaffOfDepartment() const;

    Nurse* callNurse(Patient& patient);

    // Visitor pattern
    void accept(Visitor* visitor);

    // Friend functions
    friend ostream& operator<<(ostream& os, const Department& dept);
};
