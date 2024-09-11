#include "Hospital.h"
#include <cstring>
#include <algorithm>
#include <iostream>

Hospital Hospital::theHospital("Hospital");

// Parameterized Constructor
Hospital::Hospital(const std::string& nameOfHospital) {
    setNameOfHospital(nameOfHospital);
}

// Singleton pattern: Get the instance of Hospital
Hospital* Hospital::getInstance() {
    return &theHospital;
}

// Observer pattern methods
void Hospital::registerObserver(Observer* obs) {
    cout << "Registered " << obs->getOBFirstName() << " " << obs->getOBLastName()
        << " to get notifications from '" << nameOfHospital << "'\n";
    viewers.push_back(obs);
}

void Hospital::setSpecializationObserver(const std::string& specializationName) {
    cout << "New specialization was added: " << specializationName << "!!\n";
    notifyAllRegistered(specializationName);
}

void Hospital::notifyAllRegistered(const std::string& specializationName) const {
    for (auto itr = viewers.begin(); itr != viewers.end(); ++itr) {
        (*itr)->notify(specializationName);
    }
}

// Patient management
bool Hospital::hospitalizePatient(Patient& patient) {
    if (std::find(allPatients.begin(), allPatients.end(), &patient) == allPatients.end()) {
        allPatients.push_back(&patient);
        return true;
    }
    return false; // Patient already exists
}

bool Hospital::unhospitalizePatient(Patient& patient) {
    auto it = std::find(allPatients.begin(), allPatients.end(), &patient);
    if (it != allPatients.end()) {
        allPatients.erase(it);
        return true;
    }
    return false; // Patient not found
}

// Building management
bool Hospital::addInpatientDepartment(const InpatientDepartment& ID) {
    allBuildings.push_back(new InpatientDepartment(ID));
    return true;
}

bool Hospital::addCafeteria(const Cafeteria& C) {
    allBuildings.push_back(new Cafeteria(C));
    return true;
}

list<Cafeteria*> Hospital::findAllCafeterias(int& numCafeterias) const {
    list<Cafeteria*> cafeterias;
    for (Building* building : allBuildings) {
        if (auto cafeteria = dynamic_cast<Cafeteria*>(building)) {
            cafeterias.push_back(cafeteria);
        }
    }
    numCafeterias = (int)cafeterias.size();
    return cafeterias;
}

list<InpatientDepartment*> Hospital::findAllInpatientDepartments() const {
    list<InpatientDepartment*> inpatientDepartments;
    for (Building* building : allBuildings) {
        if (auto inpatientDepartment = dynamic_cast<InpatientDepartment*>(building)) {
            inpatientDepartments.push_back(inpatientDepartment);
        }
    }
    return inpatientDepartments;
}

// Specialization management
bool Hospital::addSpecialization(const Specialization& spec) {
    Specialization* newSpec = new Specialization(spec);
    allSpecializations.push_back(newSpec);
    setSpecializationObserver(newSpec->getNameOfSpecialization());
    return true;
}

// Doctor management
Doctor* Hospital::addDoctor(const Doctor& doctor) {
    Doctor* newDoctor = new Doctor(doctor);
    allDoctors.push_back(newDoctor);
    registerObserver(newDoctor);
    return newDoctor;
}

bool Hospital::removeDoctor(const Doctor& doctor) {
    auto it = std::find_if(allDoctors.begin(), allDoctors.end(),
        [&doctor](const Doctor* d) { return *d == doctor; });
    if (it != allDoctors.end()) {
        delete* it;
        allDoctors.erase(it);
        return true;
    }
    return false; // Doctor not found
}

// Researcher management
Researcher* Hospital::addResearcher(const Researcher& researcher) {
    Researcher* newResearcher = new Researcher(researcher);
    allResearchers.push_back(newResearcher);
    return newResearcher;
}

bool Hospital::removeResearcher(const Researcher& researcher) {
    auto it = std::find_if(allResearchers.begin(), allResearchers.end(),
        [&researcher](const Researcher* r) { return *r == researcher; });
    if (it != allResearchers.end()) {
        delete* it;
        allResearchers.erase(it);
        return true;
    }
    return false; // Researcher not found
}

// Nurse management
Nurse* Hospital::addNurse(const Nurse& nurse) {
    Nurse* newNurse = new Nurse(nurse);
    allNurses.push_back(newNurse);
    return newNurse;
}

bool Hospital::removeNurse(const Nurse& nurse) {
    auto it = std::find_if(allNurses.begin(), allNurses.end(),
        [&nurse](const Nurse* n) { return *n == nurse; });
    if (it != allNurses.end()) {
        delete* it;
        allNurses.erase(it);
        return true;
    }
    return false; // Nurse not found
}

// CafeteriaWorker management
CafeteriaWorker* Hospital::addCafeteriaWorker(const CafeteriaWorker& cafeWorker) {
    CafeteriaWorker* c = new CafeteriaWorker(cafeWorker);
    allCafeteriaWorker += c;
    return c;
}

void Hospital::removeCafeteriaWorker(CafeteriaWorker& cafeWorker) {
    allCafeteriaWorker.remove(&cafeWorker);
}

// DepartmentManager management
bool Hospital::addDepartmentManager(const DepartmentManager& dm) {
    DepartmentManager* newDM = new DepartmentManager(dm);
    allDepartmentManagers.push_back(newDM);
    registerObserver(newDM);
    return true;
}

bool Hospital::removeDepartmentManager(const DepartmentManager& dm) {
    auto it = std::find_if(allDepartmentManagers.begin(), allDepartmentManagers.end(),
        [&dm](const DepartmentManager* d) { return *d == dm; });
    if (it != allDepartmentManagers.end()) {
        delete* it;
        allDepartmentManagers.erase(it);
        return true;
    }
    return false; // Department Manager not found
}

// Output stream operator
std::ostream& operator<<(std::ostream& os, const Hospital& hospital) {
    os << "Hospital Name: " << hospital.getNameOfHospital() << "\n";
    os << "Number of Buildings: " << hospital.getNumOfBuildings() << "\n";
    os << "Number of Doctors: " << hospital.getNumOfDoctors() << "\n";
    os << "Number of Nurses: " << hospital.getNumOfNurses() << "\n";
    os << "Number of Researchers: " << hospital.getNumOfResearchers() << "\n";
    os << "Number of Patients: " << hospital.getNumOfPatients() << "\n";
    os << "Number of Department Managers: " << hospital.getNumOfDepartmentManagers() << "\n";
    os << "Number of Specializations: " << hospital.getNumOfSpecializations() << "\n";

    // Additional information
    os << "All Doctors: \n";
    for (auto doctor : hospital.getAllDoctors()) {
        os << *doctor << "\n";
    }
    os << "All Nurses: \n";
    for (auto nurse : hospital.getAllNurses()) {
        os << *nurse << "\n";
    }
    os << "All Researchers: \n";
    for (auto researcher : hospital.getAllResearchers()) {
        os << *researcher << "\n";
    }
    os << "All Patients: \n";
    for (auto patient : hospital.getAllPatients()) {
        os << *patient << "\n";
    }
    os << "Cafeteria Workers: " << std::endl;
    os << hospital.allCafeteriaWorker << std::endl;
    os << "All Department Managers: \n";
    for (auto dm : hospital.getDepartmentManagers()) {
        os << *dm << "\n";
    }
    os << "All Specializations: \n";
    for (auto spec : hospital.getAllSpecializations()) {
        os << *spec << "\n";
    }
    return os;
}
