#pragma once

#include "Worker.h"
#include "Observer.h"
#include "Specialization.h"
#include <list>
#include <string>

class Patient;

class Doctor : public virtual Worker, public Observer {
protected:
    std::list<Patient*> patientsOfDoctor;
    std::list<Specialization*> specialization;

public:
    // Constructors
    Doctor(const Worker& base);
    Doctor(const Worker& base, const std::list<Patient*>& patientsOfDoctor, const std::list<Specialization*>& specialization);

    // Functions
    void putDiagnosis(Patient* patient, const std::string& diagnosis);
    bool addPatient(Patient& patient);
    bool removePatient(Patient& patient); // Remove patient from the doctor's list to another doctor
    void addSpecialization(Specialization* newSpecialization);

    // Getters
    std::list<Patient*> getPatients() const;
    std::list<Specialization*> getSpecializations() const;
    int getNumOfPatientsOfDoctor() const;
    int getNumOfSpecialization() const;

    // Observer
    virtual void notify(string specializationName) const override;
   

    virtual Observer* clone() const override { return new Doctor(*this); }

    // Operators
    bool operator==(const Doctor& other) const;
    virtual void toOs(std::ostream& os) const override;
};
