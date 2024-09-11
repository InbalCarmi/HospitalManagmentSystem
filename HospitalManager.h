#pragma once

#include "Hospital.h"
#include "generalFunctions.h"

class HospitalManager {
private:
    Hospital* hospital;

public:
    // Constructor and Destructor
    HospitalManager(const std::string& name);

    // Worker management
    Worker* createWorker();
    void addWorker();
    void removeWorker();
    void changeWorkerSalary();
    void WorkerChangeShift(Worker* worker, int numOfHours, int numOnShift);
    void removeDoctor(Doctor& doctorToRemove, Department* department);

    // Patient management
    void addPatient();
    void removePatient();


    // Department management
    DepartmentManager* createDepartmentManager();
    void addDepartmentManager();
    void removeDepartmentManager();
    void changeDepartmentManager();
    bool addInpatientDepartment(const std::string& name, const std::string& address);
    bool addCafeteria(const std::string& name, const std::string& address);
    void createDepartment();
    void addBuilding();

    // Specialization management
    bool addSpecialization();
    void addSpecializationToWorker();

    // Article management
    void addArticleToResearcherAndDepMan();
    void addArticleToResearcher(Researcher& researcher);

    // Display methods
    void displayWorkerOnShift() const;
    void displayDoctorsOnShift() const;
    void displayNursesOnShift() const;
    void displayResearchersOnShift() const;
    void displayDepartmentManagersOnShift() const;
    void displayCafeteriaWorkersOnShift() const;
    int displayDoctors() const;
    int displayNurses() const;
    void displayCafeteriaWorkers() const;
    int displayResearchers() const;
    void displayDepartmentManagers() const;
    void displaySpecializations() const;
    void displayHospital() const;
    void displayPatients() const;
    void displayBuildings() const;

    // Helper methods
    Department* chooseDepartment();
    Doctor* chooseDoctor(Department* department);
    CafeteriaWorker* chooseCafeteriaWorker();
    int chooseBuilding();
    Date* createPerson(std::string& firstName, std::string& lastName);

    // Clock in/out and shift management
    void ClockInOut();

    // Miscellaneous
    void patientCallNurse() const;
    void giveRaise();
    void giveHoliday();

    // Accessor
    Hospital* getHospital() { return hospital; }
};
