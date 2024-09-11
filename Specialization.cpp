#include <cstring>
#include "Specialization.h"
#include "Doctor.h"

// Constructor
Specialization::Specialization(const string& nameOfSpecialization)
    : nameOfSpecialization(nameOfSpecialization) {}

// Accessors
int Specialization::getNumOfDoctors() const {
    return (int)listOfDoctorWithSpecial.size();
}

string Specialization::getNameOfSpecialization() const {
    return nameOfSpecialization;
}

void Specialization::setNameOfSpecialization(const string& nameOfSpecialization) {
    this->nameOfSpecialization = nameOfSpecialization;
}

list<Doctor*> Specialization::getListOfDoctorWithSpecial() const {
    return listOfDoctorWithSpecial;
}

// Mutators
void Specialization::addDoctor(Doctor* newDoctor) {
    if (newDoctor && find(listOfDoctorWithSpecial.begin(), listOfDoctorWithSpecial.end(), newDoctor) == listOfDoctorWithSpecial.end()) {
        listOfDoctorWithSpecial.push_back(newDoctor);
        newDoctor->addSpecialization(this);
    }
}

bool Specialization::removeDoctorWithSpecial(const Doctor* doctor) {
    if (doctor) {
        auto it = find(listOfDoctorWithSpecial.begin(), listOfDoctorWithSpecial.end(), doctor);
        if (it != listOfDoctorWithSpecial.end()) {
            listOfDoctorWithSpecial.erase(it);
            return true;
        }
    }
    return false;
}

// Friend function for output
ostream& operator<<(ostream& os, const Specialization& specialization) {
    os << "Specialization: " << specialization.getNameOfSpecialization() << "\n";
    os << "Number of Doctors: " << specialization.getNumOfDoctors() << "\n";
    os << "Doctors with this specialization:\n";
    for (const auto& doctor : specialization.getListOfDoctorWithSpecial()) {
        os << doctor->getFirstName() << " " << doctor->getLastName() << "\n"; // Assuming Doctor class has operator<< defined
    }
    return os;
}
