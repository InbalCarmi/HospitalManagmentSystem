#include "Doctor.h"
#include "Patient.h"
#include "Specialization.h"
#include <algorithm>
#include <iostream>

// Parameterized constructor
Doctor::Doctor(const Worker& base)
    : Worker(base), Observer(base.getFirstName(), base.getLastName()) {}

// Parameterized constructor with lists
Doctor::Doctor(const Worker& base, const std::list<Patient*>& patientsOfDoctor, const std::list<Specialization*>& specialization)
    : Worker(base), Observer(base.getFirstName(), base.getLastName()),
    patientsOfDoctor(patientsOfDoctor), specialization(specialization) {}

// Set diagnosis for a patient
void Doctor::putDiagnosis(Patient* patient, const std::string& diagnosis) {
    patient->setDiagnosis(diagnosis);
}

// Add a patient to the doctor's list
bool Doctor::addPatient(Patient& patient) {
    if (std::find(patientsOfDoctor.begin(), patientsOfDoctor.end(), &patient) != patientsOfDoctor.end()) {
        return false; // Patient already in the list
    }

    patientsOfDoctor.push_back(&patient);
    patient.setDoctor(this);
    return true;
}

// Remove a patient from the doctor's list
bool Doctor::removePatient(Patient& patient) {
    auto it = std::find(patientsOfDoctor.begin(), patientsOfDoctor.end(), &patient);
    if (it != patientsOfDoctor.end()) {
        patientsOfDoctor.erase(it);
        return true;
    }
    return false;
}

// Add a specialization to the doctor's list
void Doctor::addSpecialization(Specialization* newSpecialization) {
    if (std::find(specialization.begin(), specialization.end(), newSpecialization) != specialization.end()) {
        return; // Specialization already in the list
    }
    specialization.push_back(newSpecialization);
    newSpecialization->addDoctor(this);
}

// Get list of patients
std::list<Patient*> Doctor::getPatients() const {
    return patientsOfDoctor;
}

// Get list of specializations
std::list<Specialization*> Doctor::getSpecializations() const {
    return specialization;
}

// Get the number of patients
int Doctor::getNumOfPatientsOfDoctor() const {
    return (int)patientsOfDoctor.size();
}

// Get the number of specializations
int Doctor::getNumOfSpecialization() const {
    return (int)specialization.size();
}

// Notify observer of a new specialization
void Doctor::notify(string specializationName) const
{
    cout << this->getFirstName() << " " << this->getLastName() << "! There is a new specialization: " << specializationName << "'\n";
}

// Equality operator
bool Doctor::operator==(const Doctor& other) const {
    if (this == &other) return true;

    if (!Worker::operator==(other)) return false;
    if (patientsOfDoctor.size() != other.patientsOfDoctor.size()) return false;
    if (specialization.size() != other.specialization.size()) return false;

    return std::equal(patientsOfDoctor.begin(), patientsOfDoctor.end(), other.patientsOfDoctor.begin()) &&
        std::equal(specialization.begin(), specialization.end(), other.specialization.begin());
}

// Output stream operator
void Doctor::toOs(std::ostream& os) const {
    Worker::toOs(os);
    os << "Number of Patients: " << getNumOfPatientsOfDoctor();

    if (!patientsOfDoctor.empty()) {
        os << "\nPatients: ";
        for (auto it = patientsOfDoctor.begin(); it != patientsOfDoctor.end(); ++it) {
            os << (*it)->getFirstName() << " " << (*it)->getLastName();
            if (std::next(it) != patientsOfDoctor.end()) {
                os << ", ";
            }
        }
    }

    os << "\nNumber of Specializations: " << getNumOfSpecialization();

    if (!specialization.empty()) {
        os << "\nSpecializations: ";
        for (auto it = specialization.begin(); it != specialization.end(); ++it) {
            os << (*it)->getNameOfSpecialization();
            if (std::next(it) != specialization.end()) {
                os << ", ";
            }
        }
    }

    os << std::endl;
}
