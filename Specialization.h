#pragma once

#include <iostream>
#include <list>
using namespace std;

class Doctor;

class Specialization
{
private:
    string nameOfSpecialization;
    list<Doctor*> listOfDoctorWithSpecial;

public:
    // Constructors
    Specialization(const string& nameOfSpecialization);

    // Accessors
    int getNumOfDoctors() const;
    string getNameOfSpecialization() const;
    void setNameOfSpecialization(const string& nameOfSpecialization);
    list<Doctor*> getListOfDoctorWithSpecial() const;

    // Mutators
    void addDoctor(Doctor* newDoctor);
    bool removeDoctorWithSpecial(const Doctor* doctor);

    // Friend function for output
    friend ostream& operator<<(ostream& os, const Specialization& specialization);
};
