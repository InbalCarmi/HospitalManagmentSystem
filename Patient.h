#pragma once

#include <iostream>
#include <string>
#include "Person.h"
#include "Date.h"
#include "Doctor.h"
#include "Department.h"

class Nurse;

class Patient : public Person
{
private:
    std::string diagnosis;
    Date hospitalizationDate;
    Date* dischargeDate;
    Doctor* doctor;
    Department* department;

public:
    // Constructors and Destructor
    Patient(const std::string& firstName, const std::string& lastName, Date dob, Doctor* doc, Department* dept);

    // Setters and Getters
    bool setDoctor(Doctor* doctor);
    const Doctor* getDoctor() const { return doctor; }

    bool setDepartment(Department* department);
    const Department* getDepartment() const { return department; }

    void setDiagnosis(const std::string& diagnosis);
    const std::string getDiagnosis() const { return diagnosis; }

    Nurse* callNurse();

    const Date getHospitalizationDate() const { return hospitalizationDate; }
    bool setDischargeDate(Date& newDischargeDate);
    const Date* getDischargeDate() const { return dischargeDate; }

    // Friend Functions
    friend std::ostream& operator<<(std::ostream& os, const Patient& patient);
};
