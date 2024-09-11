#include "DepartmentManager.h"
#include "Patient.h"

// Constructors
DepartmentManager::DepartmentManager(const Researcher& r, const Doctor& d, int bonus)
    : Worker(r.getFirstName(), r.getLastName(), r.getDateOfBirth(), r.getSeniority(), r.getSalary(), r.getNumOfHours(), r.getIsOnShift()),
    Researcher(r), Doctor(d), bonus(bonus) {}

// Setters and Getters
void DepartmentManager::setBonus(int bonus) {
    this->bonus = bonus;
}

int DepartmentManager::getBonus() const {
    return bonus;
}


// Output stream operator
void DepartmentManager::toOs(std::ostream& os) const {
    Worker::toOs(os);

    os << "Number of Patients: " << patientsOfDoctor.size();
    if (!patientsOfDoctor.empty()) {
        os << "\nPatients: ";
        for (auto it = patientsOfDoctor.begin(); it != patientsOfDoctor.end(); ++it) {
            os << (*it)->getFirstName() << " " << (*it)->getLastName();
            if (std::next(it) != patientsOfDoctor.end()) {
                os << ", ";
            }
        }
        os << std::endl;
    }

    os << "\nNumber of Specializations: " << specialization.size();
    if (!specialization.empty()) {
        os << "\nSpecializations: ";
        for (auto it = specialization.begin(); it != specialization.end(); ++it) {
            os << (*it)->getNameOfSpecialization();
            if (std::next(it) != specialization.end()) {
                os << ", ";
            }
        }
        os << std::endl;
    }

    os << "\nNumber of Articles: " << articlesOfResearcher.size();
    if (!articlesOfResearcher.empty()) {
        os << "\nArticles: ";
        for (auto it = articlesOfResearcher.begin(); it != articlesOfResearcher.end(); ++it) {
            os << (*it)->getNameOfArticle();
            if (std::next(it) != articlesOfResearcher.end()) {
                os << ", ";
            }
        }
        os << std::endl;
    }

    os << "\nBonus: " << bonus << std::endl;
}

// Operators
bool DepartmentManager::operator==(const DepartmentManager& other) const {
    return (Researcher::operator==(other) && Doctor::operator==(other) && bonus == other.bonus);
}
