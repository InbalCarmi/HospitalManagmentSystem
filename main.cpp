#include <iostream>
#include "HospitalManager.h"

using namespace std;

enum eMainMenu { eAddBuilding, eCreateDepartment, eAddWorker, eAddDepartmentManager, eAddPatient, eClockInClockOut, eChangeWorkerSalary, eAddSpecialization, eAddSpecializationToWorker, eAddArticleToResearcher, eChangeDepartmentManager, ePatientCallNurse, eRemovePatient, eRemoveWorker, eGiveRaise, eGiveGift,eDisplayFunctions, eMainMenuNofOptions };

const char* mainMenuStr[eMainMenuNofOptions] = { "Add Building","Create Department","Add Worker", "Add Department Manager","Add Patient", "Clock In/Out Worker","Change Worker Salary", "Add Specialization", "Add Specialization To Worker", "Add Article to Researcher", "Change Department Manager", "Patient Call Nurse", "Remove Patient","Remove Worker", "Give Raise to Department staff", "Give Holiday Gift to Department staff", "Display Functions"};

enum eDisplayMenu { eDisplayHospital, eDisplayDoctors, eDisplayNurses, eDisplayCafeteriaWorkers, eDisplayResearchers, eDisplayDepartmentManager, eDisplayPatients, eDisplayBuildings, eDisplaySpecialization, eDisplayWorkerOnShift, eDisplayMenuNofOptions };

const char* displayMenuStr[eDisplayMenuNofOptions] = { "Display Hospital", "Display Doctors", "Display Nurses", "Display Cafeteria Workers", "Display Researchers","Display Department Managers", "Display Patients", "Display Buildings", "Display Specializations","Display Worker On Shift" };


int Display(HospitalManager& manager)
{
    int option;
    int stop = 0;
    do
    {
        option = menu(displayMenuStr, eDisplayMenuNofOptions);
        switch (option)
        {
        case eDisplayHospital:
            manager.displayHospital();
            break;

        case eDisplayDoctors:
            manager.displayDoctors();
            break;

        case eDisplayNurses:
            manager.displayNurses();
            break;

        case eDisplayCafeteriaWorkers:
            manager.displayCafeteriaWorkers();
            break;

        case eDisplayResearchers:
            manager.displayResearchers();
            break;

        case eDisplayDepartmentManager:
            manager.displayDepartmentManagers();
            break;

        case eDisplayPatients:
            manager.displayPatients();
            break;

        case eDisplayBuildings:
            manager.displayBuildings();
            break;
        
        case eDisplaySpecialization:
            manager.displaySpecializations();
            break;

        case eDisplayWorkerOnShift:
            manager.displayWorkerOnShift();
            break;

        case -1: // EXIT
            stop = 1;
            break;

        default:
            cout << "Wrong option\n";
            break;
        }
    } while (!stop);

    return 1;
}

int main() {
    
    char name[MAX_STR_LEN];
    cout << "Enter Hospital name: \n";
    cin >> name;

    HospitalManager* manager = new HospitalManager(name);
  
    int option;
    int stop = 0;
    do
    {
        option = menu(mainMenuStr, eMainMenuNofOptions);
        switch (option)
        {
        case eAddBuilding:
            manager->addBuilding();
            break;

        case eCreateDepartment:
            manager->createDepartment();
            break;

        case eAddWorker:
            manager->addWorker();
            break;

        case eAddDepartmentManager:
            manager->addDepartmentManager();
            break;

        case eAddPatient:
            manager->addPatient();
            break;

        case eClockInClockOut :
            manager->ClockInOut();
            break;

        case eChangeWorkerSalary:
            manager->changeWorkerSalary();
            break;

        case eAddSpecialization:
            if(!manager->addSpecialization())
                cout << "Failed\n";
            break;

        case eAddSpecializationToWorker:
            manager->addSpecializationToWorker();
            break;

        case eAddArticleToResearcher:
            manager->addArticleToResearcherAndDepMan();
            break;

        case eChangeDepartmentManager:
            manager->changeDepartmentManager();
            break;

        case ePatientCallNurse:
            manager->patientCallNurse();
            break;
            
        case eRemovePatient:
            manager->removePatient();
            break;

        case eRemoveWorker:
            manager->removeWorker();
            break;

        case eGiveRaise:
            manager->giveRaise();
            cout << "Your hard work has not gone unnoticed, and as a result, you're getting a raise!\n";
            break;

        case eGiveGift:
            manager->giveHoliday();
            cout << "Happy Holidays! To show our appreciation, we're giving you a holiday gift!\n";
            break;

        case eDisplayFunctions:
            Display(*manager);
            break;

        case EXIT:
            stop = 1;
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (!stop);

    return 1;

}






