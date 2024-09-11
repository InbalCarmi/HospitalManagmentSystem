#pragma once

#include <list>
#include <vector>
#include "Patient.h"
#include "Worker.h"
#include "DepartmentManager.h"
#include "Cafeteria.h"
#include "InpatientDepartment.h"
#include "Nurse.h"
#include "Article.h"
#include "LinkedList.h"
#include "Observer.h"

using namespace std;

// Define the Hospital class
class Hospital {
public:
    // Singleton pattern: Get the instance of Hospital
    static Hospital* getInstance();
    ~Hospital() = default;

    // Member Functions
    bool hospitalizePatient(Patient& patient);
    bool unhospitalizePatient(Patient& patient);
    bool addInpatientDepartment(const InpatientDepartment& ID);
    bool addCafeteria(const Cafeteria& C);
    Doctor* addDoctor(const Doctor& doctor);
    Researcher* addResearcher(const Researcher& researcher);
    Nurse* addNurse(const Nurse& nurse);
    CafeteriaWorker* addCafeteriaWorker(const CafeteriaWorker& cafeWorker);
    bool addDepartmentManager(const DepartmentManager& dm);
    bool removeDoctor(const Doctor& doctor);
    bool removeResearcher(const Researcher& researcher);
    bool removeNurse(const Nurse& nurse);
    void removeCafeteriaWorker(CafeteriaWorker& cafeWorker);
    bool removeDepartmentManager(const DepartmentManager& dm);
    bool addSpecialization(const Specialization& spec);
    list<Cafeteria*> findAllCafeterias(int& numCafeterias) const;
    list<InpatientDepartment*> findAllInpatientDepartments() const;
    friend ostream& operator<<(ostream& os, const Hospital& hospital);

    // Observer pattern methods
    void registerObserver(Observer* obs);
    void setSpecializationObserver(const string& specializationName);

    // Getter methods
    const string& getNameOfHospital() const { return nameOfHospital; }
    list<Building*>& getAllBuildings() { return allBuildings; }
    const list<Building*>& getAllBuildings() const { return allBuildings; }
    list<Doctor*>& getAllDoctors() { return allDoctors; }
    const list<Doctor*>& getAllDoctors() const { return allDoctors; }
    list<Nurse*>& getAllNurses() { return allNurses; }
    const list<Nurse*>& getAllNurses() const { return allNurses; }
    list<Researcher*>& getAllResearchers() { return allResearchers; }
    const list<Researcher*>& getAllResearchers() const { return allResearchers; }
    list<Patient*>& getAllPatients() { return allPatients; }
    const list<Patient*>& getAllPatients() const { return allPatients; }
    LinkedList<CafeteriaWorker*>& getAllCafeteriaWorkers() { return allCafeteriaWorker; }
    const LinkedList<CafeteriaWorker*>& getAllCafeteriaWorkers() const { return allCafeteriaWorker; }
    list<Specialization*>& getAllSpecializations() { return allSpecializations; }
    const list<Specialization*>& getAllSpecializations() const { return allSpecializations; }
    list<DepartmentManager*>& getDepartmentManagers() { return allDepartmentManagers; }
    const list<DepartmentManager*>& getDepartmentManagers() const { return allDepartmentManagers; }

    int getNumOfDoctors() const { return (int)allDoctors.size(); }
    int getNumOfNurses() const { return (int)allNurses.size(); }
    int getNumOfResearchers() const { return (int)allResearchers.size(); }
    int getNumOfPatients() const { return (int)allPatients.size(); }
    int getNumOfDepartmentManagers() const { return (int)allDepartmentManagers.size(); }
    int getNumOfBuildings() const { return (int)allBuildings.size(); }
    int getNumOfSpecializations() const { return (int)allSpecializations.size(); }

    // Setter methods
    void setNameOfHospital(const string& newName) { nameOfHospital = newName; }

private:
    // Constructors
    Hospital(const string& nameOfHospital);
    Hospital(Hospital&& other) noexcept = delete;      // Move Constructor
    Hospital& operator=(Hospital& other) noexcept = default;
    Hospital& operator=(Hospital&& other) noexcept = default;

    static Hospital theHospital;

    string nameOfHospital;
    list<Building*> allBuildings;
    list<Patient*> allPatients;
    list<Doctor*> allDoctors;
    list<Nurse*> allNurses;
    list<Researcher*> allResearchers;
    LinkedList<CafeteriaWorker*> allCafeteriaWorker;
    list<DepartmentManager*> allDepartmentManagers;
    list<Specialization*> allSpecializations;
    vector<Observer*> viewers;

    void notifyAllRegistered(const string& specializationName) const;
};
