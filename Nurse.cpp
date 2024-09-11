#include "Nurse.h"

// Constructor from Worker base
Nurse::Nurse(const Worker& base)
    : Worker(base) { }

// Constructor with additional patient list
Nurse::Nurse(const Worker& base, const std::list<Patient*>& patients)
    : Worker(base), patientsGotCare(patients) { }

// Add patient to the list
bool Nurse::addPatient(Patient& patient) {
    // Check if the patient already exists in the list
    if (std::find(patientsGotCare.begin(), patientsGotCare.end(), &patient) == patientsGotCare.end()) {
        patientsGotCare.push_back(&patient);
        return true;
    }
    return false; // Patient already exists
}

// Remove patient from the list
bool Nurse::removePatient(Patient& patient) {
    auto it = std::find(patientsGotCare.begin(), patientsGotCare.end(), &patient);
    if (it != patientsGotCare.end()) {
        patientsGotCare.erase(it);
        return true;
    }
    return false; // Patient not found
}

// Check if doctor is on shift
bool Nurse::callDoctor(const Doctor* doctor) const {
    return doctor->getIsOnShift();
}

// Output Nurse details to stream
void Nurse::toOs(std::ostream& os) const {
    Worker::toOs(os); // Output base class information
    os << "Number of Patients: " << patientsGotCare.size(); // Output number of patients

    // Output list of patients
    if (!patientsGotCare.empty()) {
        os << "\nPatients: ";
        for (auto it = patientsGotCare.begin(); it != patientsGotCare.end(); ++it) {
            os << (*it)->getFirstName() << " " << (*it)->getLastName();
            if (std::next(it) != patientsGotCare.end()) {
                os << ", "; // Add comma between patients
            }
        }
    }
    os << std::endl;
}
