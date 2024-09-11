#include "HospitalManager.h"
#include <iostream>
#include <cstring>
#include <string>
#include "Article.h"
#include "IncomeVisitor.h"
#include "holidayGift.h"

using namespace std;

enum eWorkerType { eDoctor, eNurse, eResearcher, eDepartmentManager,eCafeteriaWorker, eNofOptions };

const char* workerTypeStr[eNofOptions] = { "Doctor", "Nurse", "Researcher", "Department Manager" ,"Cafeteria Worker"};

const enum eWorkerTypeHours { eDoctorH = 12, eNurseH = 8, eResearcherH = 10, eCafeteriaWorkerH = 8, eDepartmentManagerH = 24};

Date* HospitalManager::createPerson(string& firstName, string& lastName)
{
    int day, month, year;
    cout << "Enter first name: \n";
    getline(cin, firstName);
    cout << "Enter last name: \n";
    getline(cin, lastName);
    Date* dob = nullptr;
    bool isValidDate = false;
    while (!isValidDate)
    {
        cout << "Enter day of birth: \n";
        cin >> day;
        cout << "Enter mounth of birth: \n";
        cin >> month;
        cout << "Enter year of birth: \n";
        cin >> year;

        try {
            dob = new Date(day, month, year);
            isValidDate = true;

        }
        catch (const string& msg) {
            cout << msg << endl;
        }

        if (!isValidDate)
        {
            cout << "\n----Enter The Date Again----\n";
        }
    }

    return dob;
}

HospitalManager::HospitalManager(const string& name) {
    hospital = Hospital::getInstance();
    hospital->setNameOfHospital(name);
}

Worker* HospitalManager::createWorker()
{
    int seniority, salary;
    double numOfHours;
    bool isOnShift;
    string firstName, lastName;
    Date* dob = createPerson(firstName, lastName);
    //cout << "Enter worker's ID: "; // change
    //cin >> id;
    cout << "Enter worker's seniority: \n";
    cin >> seniority;
    cout << "Enter worker's salary: \n";
    cin >> salary;
    cout << "Enter worker's number of hours: \n";
    cin >> numOfHours;
    cout << "Is the worker on shift (1 for yes, 0 for no): \n";
    cin >> isOnShift;
  
    Worker* w= new Worker(firstName,lastName,*dob, seniority, salary, numOfHours, isOnShift);
    return w;
}

int HospitalManager::chooseBuilding()
{
    int buildingIndex;
    do {
        cout << "Select Building number:\n";
        int i = 1;
        for (auto& building : hospital->getAllBuildings()) {
            cout << i++ << ". " << building->getBuildingName() << " Type: " << typeid(*building).name() << endl;
        }
        cin >> buildingIndex;
        buildingIndex--;
    } while (buildingIndex < 0 || buildingIndex >= hospital->getNumOfBuildings());
    return buildingIndex;
}

CafeteriaWorker* HospitalManager::chooseCafeteriaWorker()
{
    int index;
    Node<CafeteriaWorker*>* selectedNode;
    do {
        hospital->getAllCafeteriaWorkers().display();

        std::cout << "Enter the index of the cafeteria worler you want to choose:";
        std::cin >> index;

        selectedNode = hospital->getAllCafeteriaWorkers().getNode(index);
   
        if(selectedNode == nullptr)
            std::cout << "Invalid index. Please try again." << std::endl;
    } while (selectedNode == nullptr);
    return selectedNode->data;
}



void HospitalManager::addWorker() {
    if (hospital->getNumOfBuildings() == 0) {
        cout << "No Buildings\n";
        return;
    }

    Worker* w;
    int buildingIndex = chooseBuilding();

    Building* selectedBuilding = hospital->getAllBuildings().front();  // Placeholder to get the correct building
    auto it = hospital->getAllBuildings().begin();
    advance(it, buildingIndex);
    selectedBuilding = *it;

    if (typeid(*selectedBuilding) == typeid(InpatientDepartment)) {
        if (hospital->getNumOfDepartmentManagers() == 0) {
            cout << "No Departments\n";
            return;
        }
        cleanBuffer();
        w = createWorker();
        InpatientDepartment* inpatientDep = dynamic_cast<InpatientDepartment*>(selectedBuilding);

        cout << "Select Department to add worker to:\n";
        int i = 1;
        for (auto& department : inpatientDep->getDepartments()) {
            cout << i++ << ". " << department->getNameOfDepartment() << endl;
        }

        int depIndex;
        do {
            cout << "Enter Index:\n";
            cin >> depIndex;
            depIndex--;
        } while (depIndex < 0 || static_cast<size_t>(depIndex) >= inpatientDep->getNumOfDepartments());

        int option;
        bool stop = false;
        option = menu(workerTypeStr, eNofOptions - 2);
        do {
            switch (option) {
            case eDoctor: {
                Doctor* doc = hospital->addDoctor(Doctor(*w));
                auto depIt = inpatientDep->getDepartments().begin();
                advance(depIt, depIndex);
                (*depIt)->addWorkerToDepartment(*doc);
                stop = true;
                break;
            }
            case eNurse: {
                Nurse* nur = hospital->addNurse(Nurse(*w));
                auto depIt = inpatientDep->getDepartments().begin();
                advance(depIt, depIndex);
                (*depIt)->addWorkerToDepartment(*nur);
                stop = true;
                break;
            }
            case eResearcher: {
                Researcher* res = hospital->addResearcher(Researcher(*w));
                auto depIt = inpatientDep->getDepartments().begin();
                advance(depIt, depIndex);
                (*depIt)->addWorkerToDepartment(*res);
                stop = true;
                break;
            }
            default: {
                cout << "Wrong option\n";
                break;
            }
            }
        } while (!stop);
    }
    else {
        Cafeteria* cafeteria = dynamic_cast<Cafeteria*>(selectedBuilding);
        cleanBuffer();
        w = createWorker();
        CafeteriaWorker* cw = hospital->addCafeteriaWorker(CafeteriaWorker(*w));
        cafeteria->addWorker(*cw);
    }

    delete w;
}

void HospitalManager::removeWorker() {
    if (hospital->getNumOfBuildings() == 0) {
        cout << "No Buildings\n";
        return;
    }

    int buildingIndex = chooseBuilding();
    Building* selectedBuilding = hospital->getAllBuildings().front();  // Placeholder to get the correct building
    auto it = hospital->getAllBuildings().begin();
    advance(it, buildingIndex);
    selectedBuilding = *it;

    if (typeid(*selectedBuilding) == typeid(InpatientDepartment)) {
        if (hospital->getNumOfDepartmentManagers() == 0) {
            cout << "No Departments\n";
            return;
        }

        InpatientDepartment* inpatientDep = dynamic_cast<InpatientDepartment*>(selectedBuilding);

        cout << "Select Department to remove worker from:\n";
        int i = 1;
        for (auto& department : inpatientDep->getDepartments()) {
            cout << i++ << ". " << department->getNameOfDepartment() << endl;
        }

        int depIndex;
        do {
            cout << "Enter Index\n";
            cin >> depIndex;
            depIndex--;
        } while (depIndex < 0 || static_cast<size_t>(depIndex) >= inpatientDep->getNumOfDepartments());

        Department* dep = *(next(inpatientDep->getDepartments().begin(), depIndex));

        if (dep->getAllstaffOfDepartment().empty())
        {
            cout << "No worker to remove here!\n";
            return;
        }

        cout << "Select Worker to remove from Department:\n";
        int workerIndex;
        i = 1;
        for (auto& worker : dep->getAllstaffOfDepartment()) {
            cout << i++ << ". " << typeid(*worker).name() << " " << worker->getFirstName() << " " << worker->getLastName() << endl;
        }

        do {
            cout << "Enter Index\n";
            cin >> workerIndex;
            workerIndex--;
        } while (workerIndex < 0 || static_cast<size_t>(workerIndex) >= dep->getNumOfStaffOfDepartment());

        Worker* workerToRemove = *(next(dep->getAllstaffOfDepartment().begin(), workerIndex));

        dep->removeWorkerFromDepartment(*workerToRemove);

        if (typeid(*workerToRemove) == typeid(Doctor)) {
            Doctor* doctorToRemove = dynamic_cast<Doctor*>(workerToRemove);
            removeDoctor(*doctorToRemove, dep);
            //hospital->removeDoctor(*doctorToRemove);
        }
        else if (typeid(*workerToRemove) == typeid(Nurse)) {
            Nurse* nurseToRemove = dynamic_cast<Nurse*>(workerToRemove);
            hospital->removeNurse(*nurseToRemove);
        }
        else if (typeid(*workerToRemove) == typeid(Researcher)) {
            Researcher* researcherToRemove = dynamic_cast<Researcher*>(workerToRemove);
            hospital->removeResearcher(*researcherToRemove);
        }

    }
    else {
        Cafeteria* cafeteria = dynamic_cast<Cafeteria*>(selectedBuilding);

        if (cafeteria->getCafeteriaWorkers().empty())
        {
            cout << "No worker to remove here!\n";
            return;
        }
            

        cout << "Select Worker to remove from Cafeteria:\n";
        int workerIndex;
        int i = 1;
        for (auto& worker : cafeteria->getCafeteriaWorkers()) {
            cout << i++ << ". " << worker->getFirstName() << " " << worker->getLastName() << endl;
        }

        do {
            cout << "Enter Index\n";
            cin >> workerIndex;
            workerIndex--;
        } while (workerIndex < 0 || static_cast<size_t>(workerIndex) >= cafeteria->getNumOfCafeteriaWorkers());

        CafeteriaWorker* workerToRemove = *(next(cafeteria->getCafeteriaWorkers().begin(), workerIndex));

        cafeteria->fireWorker(*workerToRemove);
        hospital->removeCafeteriaWorker(*workerToRemove);
    }
}



void HospitalManager::addDepartmentManager()
{
    DepartmentManager* dm = createDepartmentManager();
    delete dm;
}

void HospitalManager::addPatient() {
    string diagnosis;
    string firstName, lastName;
    Date* dob = createPerson(firstName, lastName);

    Doctor* doctor = nullptr;
    Department* department = nullptr;

    department = chooseDepartment();
    if (department == nullptr)
        return;

    doctor = chooseDoctor(department);

    if (doctor == nullptr)
    {
        cout << "No Doctor On Shift, You can't Be Hospitalized\n";
        return;
    }

    cout << "\nEnter patient's diagnosis:\n";
    cin.ignore(); // Ignore any leftover newline character from previous input
    getline(cin, diagnosis);

    Patient* patient = new Patient(firstName, lastName, *dob, doctor, department);
    doctor->putDiagnosis(patient, diagnosis);
    department->addPatient(*patient);
    hospital->hospitalizePatient(*patient);

    // Clean up
    delete dob;
}

void HospitalManager::displayPatients() const {
    cout << "Number of Patients: " << hospital->getNumOfPatients() << endl;

    int index = 1;
    for (auto it = hospital->getAllPatients().begin(); it != hospital->getAllPatients().end(); ++it, ++index) {
        cout << "Patient " << index << ":" << endl;
        cout << **it << endl; // Dereference iterator to get Patient*
    }
}


void HospitalManager::displayBuildings() const {
    cout << "Number of Buildings: " << hospital->getNumOfBuildings() << endl;

    int index = 1;
    for (auto it = hospital->getAllBuildings().begin(); it != hospital->getAllBuildings().end(); ++it, ++index) {
        cout << "Building " << index << ":" << endl;

        if (typeid(**it) == typeid(InpatientDepartment)) {
            cout << *dynamic_cast<InpatientDepartment*>(*it) << endl;
        }
        else if (typeid(**it) == typeid(Cafeteria)) {
            cout << *dynamic_cast<Cafeteria*>(*it) << endl;
        }
    }
}

void HospitalManager::WorkerChangeShift(Worker* worker, int numOfHours, int numOnShift)
{
    if (worker->getIsOnShift())
    {
        if (numOnShift == 1)
        {
            cout << "You Are The Only Worker On Shift Not Possible To Get Off!";
        }
        else {
            worker->setOnShift(false);
            double hours = worker->getNumOfHours() + numOfHours;
            worker->setNumOfHours(hours);
        } 
    }else
        worker->setOnShift(true);
}

void HospitalManager::ClockInOut() {
    int option;
    int index;
    int stop = 0;

    option = menu(workerTypeStr, eNofOptions);

    switch (option) {
    case eDoctor: {
        int numOnShift = displayDoctors();
        list<Doctor*> doctors = hospital->getAllDoctors();
        int i = 0;

        do {
            cout << "Select Doctor number:\n";
            cin >> index;
            index--;
        } while (index < 0 || index >= hospital->getNumOfDoctors());

        auto it = doctors.begin();
        advance(it, index); // Move iterator to the selected index
        Doctor* selectedDoctor = *it;

        WorkerChangeShift(selectedDoctor, eDoctorH, numOnShift);
        break;
    }
    case eNurse: {
        int numOnShift = displayNurses();
        list<Nurse*> nurses = hospital->getAllNurses();
        int i = 0;

        do {
            cout << "Select Nurse number:\n";
            cin >> index;
            index--;
        } while (index < 0 || index >= hospital->getNumOfNurses());

        auto it = nurses.begin();
        advance(it, index); // Move iterator to the selected index
        Nurse* selectedNurse = *it;

        WorkerChangeShift(selectedNurse, eNurseH, numOnShift);
        break;
    }
    case eResearcher: {
        int numOnShift = displayResearchers();
        list<Researcher*> researchers = hospital->getAllResearchers();
        int i = 0;

        do {
            cout << "Select Researcher number:\n";
            cin >> index;
            index--;
        } while (index < 0 || index >= hospital->getNumOfResearchers());

        auto it = researchers.begin();
        advance(it, index); // Move iterator to the selected index
        Researcher* selectedResearcher = *it;

        WorkerChangeShift(selectedResearcher, eResearcherH, numOnShift);
        break;
    }
    case eDepartmentManager: {
        list<DepartmentManager*> managers = hospital->getDepartmentManagers();
        int numManagers = hospital->getNumOfDepartmentManagers();

        displayDepartmentManagers();
        do {
            cout << "Select Department Manager number:\n";
            cin >> index;
            index--;
        } while (index < 0 || index >= numManagers);

        auto it = managers.begin();
        advance(it, index); // Move iterator to the selected index
        DepartmentManager* selectedManager = *it;

        WorkerChangeShift(selectedManager, eDepartmentManagerH, 2);
        break;
    }
    case eCafeteriaWorker: {
        CafeteriaWorker* c = chooseCafeteriaWorker();
        WorkerChangeShift(c, eCafeteriaWorkerH, 0);
        break;
    }
    case -1: {
        stop = 1;
        break;
    }
    default: {
        cout << "Wrong option\n";
        break;
    }
    }
}

Department* HospitalManager::chooseDepartment()
{
    Department* department = nullptr;
    int numInpatientDepartments;
    list<InpatientDepartment*> inpatientDepartments = hospital->findAllInpatientDepartments();
    numInpatientDepartments = (int)inpatientDepartments.size();
    if (inpatientDepartments.empty()) {
        cout << "No departments available. Add a department first." << endl;
        return nullptr;
    }

    cout << "Select Inpatient Department:\n";
    int index = 1;
    for (InpatientDepartment* dept : inpatientDepartments) {
        cout << index++ << ". " << dept->getBuildingName() << endl;
    }

    int inpatientDepartmentIndex;
    do {
        cout << "Enter Index number:\n";
        cin >> inpatientDepartmentIndex;
        inpatientDepartmentIndex--;
    } while (inpatientDepartmentIndex < 0 || inpatientDepartmentIndex >= numInpatientDepartments);

    auto selectedInpatientDeptIt = std::next(inpatientDepartments.begin(), inpatientDepartmentIndex);
    InpatientDepartment* selectedInpatientDepartment = *selectedInpatientDeptIt;

    if (selectedInpatientDepartment->getDepartments().empty())
    {
        cout << "No departments available. Add a department first." << endl;
        return nullptr;
    }


    cout << "Select Department:\n";
    index = 1;
    for (auto& dept : selectedInpatientDepartment->getDepartments()) {
        cout << index++ << ". " << dept->getNameOfDepartment() << endl;
    }

    int departmentIndex;
    do {
        cout << "Enter Index number:\n";
        cin >> departmentIndex;
        departmentIndex--;
    } while (departmentIndex < 0 || departmentIndex >= selectedInpatientDepartment->getNumOfDepartments());

    auto deptIt = std::next(selectedInpatientDepartment->getDepartments().begin(), departmentIndex);
    department = *deptIt;

    return department;
}

Doctor* HospitalManager::chooseDoctor(Department* department)
{
    bool flag = false;
    int index = 0;
    Doctor* doctor = nullptr;

    for (auto& staff : department->getAllstaffOfDepartment()) {
        index++;
        if (typeid(*staff) == typeid(Doctor) && staff->getIsOnShift()) {
            cout << "Doctor Index: " << index << ". " << staff->getFirstName() << " " << staff->getLastName() << endl;
            flag = true;
        }
    }

    if (flag) {
        int doctorIndex;
        do {
            cout << "Enter Index number:\n";
            cin >> doctorIndex;
            doctorIndex--;
        } while (doctorIndex < 0 || doctorIndex >= department->getNumOfStaffOfDepartment() || typeid(*department->getAllstaffOfDepartment().front()) != typeid(Doctor));

        auto docIt = std::next(department->getAllstaffOfDepartment().begin(), doctorIndex);
        doctor = dynamic_cast<Doctor*>(*docIt);
    }
    else if (department->getDepartmentManager()->getIsOnShift()) {
        doctor = department->getDepartmentManager();
        cout << "No other Doctor is On Shift so you are lucky and getting the Department Manager!!\n";
    }

    return doctor;
}

void HospitalManager::giveRaise()
{
    int money = 0;
    Department* department = chooseDepartment();
    if (department == nullptr)
        return;

    cout << "how much money do you want to add to the salary?";
    cin >> money;

    department->accept(new IncomeVisitor(money));
}

void HospitalManager::giveHoliday()
{
    int money = 0;
    Department* department = chooseDepartment();

    cout << "how much money do you want to add to the salary?";
    cin >> money;

    department->accept(new IncomeVisitor(money));
}


int HospitalManager::displayDoctors() const {
    int numOnShift = 0;
    int index = 1; // Counter for displaying doctor numbers

    cout << "\nNumber of Doctors: " << hospital->getNumOfDoctors() << endl;

    for (auto it = hospital->getAllDoctors().begin(); it != hospital->getAllDoctors().end(); ++it, ++index) {
        Doctor* doctor = *it;
        if (doctor->getIsOnShift()) {
            numOnShift++;
        }
        cout << "\nDoctor " << index << ":" << endl;
        cout << *doctor;
    }

    return numOnShift;
}


int HospitalManager::displayNurses() const {
    int numOnShift = 0;
    int index = 1; // Counter for displaying nurse numbers

    cout << "Number of Nurses: " << hospital->getNumOfNurses() << endl;

    for (auto it = hospital->getAllNurses().begin(); it != hospital->getAllNurses().end(); ++it, ++index) {
        Nurse* nurse = *it;
        if (nurse->getIsOnShift()) {
            numOnShift++;
        }
        cout << "Nurse " << index << ":" << endl;
        cout << *nurse << endl;
    }

    return numOnShift;
}

void HospitalManager::displayCafeteriaWorkers() const
{
    cout << hospital->getAllCafeteriaWorkers();
}

int HospitalManager::displayResearchers() const {
    int numOnShift = 0;
    int index = 1; // Counter for displaying researcher numbers

    cout << "Number of Researchers: " << hospital->getNumOfResearchers() << endl;

    for (auto it = hospital->getAllResearchers().begin(); it != hospital->getAllResearchers().end(); ++it, ++index) {
        Researcher* researcher = *it;
        if (researcher->getIsOnShift()) {
            numOnShift++;
        }
        cout << "Researcher " << index << ":" << endl;
        cout << *researcher << endl;
    }

    return numOnShift;
}

void HospitalManager::displayDepartmentManagers() const {
    int index = 1; // Counter for displaying manager numbers

    cout << "Number of Department Managers: " << hospital->getNumOfDepartmentManagers() << endl;

    for (auto it = hospital->getDepartmentManagers().begin(); it != hospital->getDepartmentManagers().end(); ++it, ++index) {
        DepartmentManager* manager = *it;
        cout << "Department Manager " << index << ":" << endl;
        cout << *manager << endl;
    }
}

void HospitalManager::displaySpecializations() const {
    int index = 1; // Counter for displaying specialization numbers

    cout << "Number of Specializations: " << hospital->getNumOfSpecializations() << endl;

    for (auto it = hospital->getAllSpecializations().begin(); it != hospital->getAllSpecializations().end(); ++it, ++index) {
        Specialization* specialization = *it;
        cout << "Specialization " << index << ":" << endl;
        cout << *specialization << endl;
    }
}

void HospitalManager::changeWorkerSalary() {
    int option;
    int index;
    int stop = 0;
    int newSalary;

    option = menu(workerTypeStr, eNofOptions);

    switch (option) {
    case eDoctor: {
        if (hospital->getNumOfDoctors() == 0) {
            cout << "No Doctors\n";
            return;
        }

        displayDoctors();
        list<Doctor*> doctors = hospital->getAllDoctors();

        do {
            cout << "Select Doctor number:\n";
            cin >> index;
            index--;
        } while (index < 0 || index >= hospital->getNumOfDoctors());

        auto it = doctors.begin();
        advance(it, index); // Move iterator to the selected index
        Doctor* selectedDoctor = *it;

        cout << "Enter the new salary for the worker: \n";
        cin >> newSalary;
        selectedDoctor->setSalary(newSalary);
        cout << "Salary updated successfully.\n";
        break;
    }

    case eNurse: {
        if (hospital->getNumOfNurses() == 0) {
            cout << "No Nurses\n";
            return;
        }

        displayNurses();
        list<Nurse*> nurses = hospital->getAllNurses();

        do {
            cout << "Select Nurse number:\n";
            cin >> index;
            index--;
        } while (index < 0 || index >= hospital->getNumOfNurses());

        auto it = nurses.begin();
        advance(it, index); // Move iterator to the selected index
        Nurse* selectedNurse = *it;

        cout << "Enter the new salary for the worker: \n";
        cin >> newSalary;
        selectedNurse->setSalary(newSalary);
        cout << "Salary updated successfully.\n";
        break;
    }

    case eResearcher: {
        if (hospital->getNumOfResearchers() == 0) {
            cout << "No Researchers\n";
            return;
        }

        displayResearchers();
        list<Researcher*> researchers = hospital->getAllResearchers();

        do {
            cout << "Select Researcher number:\n";
            cin >> index;
            index--;
        } while (index < 0 || index >= hospital->getNumOfResearchers());

        auto it = researchers.begin();
        advance(it, index); // Move iterator to the selected index
        Researcher* selectedResearcher = *it;

        cout << "Enter the new salary for the worker: \n";
        cin >> newSalary;
        selectedResearcher->setSalary(newSalary);
        cout << "Salary updated successfully.\n";
        break;
    }

    case eDepartmentManager: {
        if (hospital->getNumOfDepartmentManagers() == 0) {
            cout << "No Department Managers\n";
            return;
        }

        list<DepartmentManager*> managers = hospital->getDepartmentManagers();

        displayDepartmentManagers();

        do {
            cout << "Select Department Manager number:\n";
            cin >> index;
            index--;
        } while (index < 0 || index >= hospital->getNumOfDepartmentManagers());

        auto it = managers.begin();
        advance(it, index); // Move iterator to the selected index
        DepartmentManager* selectedManager = *it;

        cout << "Enter the new salary for the worker: \n";
        cin >> newSalary;
        selectedManager->setSalary(newSalary);
        cout << "Salary updated successfully.\n";
        break;
    }

    case eCafeteriaWorker: {
        if (hospital->getAllCafeteriaWorkers().getHead() == nullptr) {
            cout << "No Cafeteria Workers\n";
            return;
        }

        CafeteriaWorker* c = chooseCafeteriaWorker();

        cout << "Enter the new salary for the worker: \n";
        cin >> newSalary;
        c->setSalary(newSalary);
        cout << "Salary updated successfully.\n";
        break;
    }

    case -1: {
        stop = 1;
        break;
    }

    default: {
        cout << "Wrong option\n";
        break;
    }
    }
}

void HospitalManager::createDepartment()
{
    if (hospital->getNumOfDepartmentManagers() == 0)
    {
        cout << "Add Department Managers First!\n";
        return;
    }

    int numInpatientDepartments, inpatientDepIndex, DepManagerIndex;
    list<InpatientDepartment*> inpatientDepartments = hospital->findAllInpatientDepartments();
    numInpatientDepartments = (int)inpatientDepartments.size();
    if (inpatientDepartments.empty())
    {
        cout << "Please Create an Inpatient Department Before Adding a Department\n";
        return;
    }

    cout << "Choose an Inpatient Department to Add a Department to" << endl;
    int i = 1;
    for (InpatientDepartment* dept : inpatientDepartments)
    {
        cout << i++ << ". " << dept->getBuildingName() << endl;
    }

    do {
        cout << "Enter Inpatient Department index: ";
        cin >> inpatientDepIndex;
        inpatientDepIndex--;
    } while (inpatientDepIndex < 0 || inpatientDepIndex >= numInpatientDepartments);

    string name;
    cout << "\nEnter Department name: \n";
    cin.ignore(); // Ignore any leftover newline character from previous input
    getline(cin, name);

    cout << "Choose a Department Manager For the Department" << endl;
    list<DepartmentManager*> departmentManagers = hospital->getDepartmentManagers();
    int managerIndex = 1;
    for (DepartmentManager* manager : departmentManagers)
    {
        cout << managerIndex++ << ". " << manager->getFirstName() << " " << manager->getLastName() << endl;
    }

    do {
        cout << "Enter Department Manager index: ";
        cin >> DepManagerIndex;
        DepManagerIndex--;
    } while (DepManagerIndex < 0 || DepManagerIndex >= departmentManagers.size());

    auto managerIt = next(departmentManagers.begin(), DepManagerIndex);
    Department* d = new Department(name, **managerIt);

    // Find the selected inpatient department and add the new department to it
    auto deptIt = next(inpatientDepartments.begin(), inpatientDepIndex);
    (*deptIt)->addDepartment(*d);

    delete d;
}

DepartmentManager* HospitalManager::createDepartmentManager()
{
    cout << "Creating Department Manager:\n";
    Worker* w = createWorker();
    int bonus;
    cout << "Enter Department Manager bonus: \n";
    cin >> bonus;
    DepartmentManager* dm = new DepartmentManager(Researcher(*w), Doctor(*w), bonus);
    hospital->addDepartmentManager(*dm);
    //hospital->addDoctor(*dm);
    delete w;
    return dm;
}

void HospitalManager::addArticleToResearcherAndDepMan()
{
    int option;
    do {
        cout << "Add Article to 1 - DepartmentManager, 2 - Researcher\n";
        cin >> option;
    } while (option < 1 || option > 2);

    if (option == 2)
    {
        list<Researcher*> allResearchers = hospital->getAllResearchers();
        if (allResearchers.empty()) {
            cout << "No researchers available.\n";
            return;
        }

        cout << "Researchers:\n";
        int index = 1;
        for (Researcher* researcher : allResearchers) {
            cout << index++ << ": " << researcher->getFirstName() << " " << researcher->getLastName() << "\n";
        }

        int selectedIndex;
        do {
            cout << "Enter the index of the researcher to add an article to: ";
            cin >> selectedIndex;
            selectedIndex--;
        } while (selectedIndex < 0 || selectedIndex >= allResearchers.size());

        auto it = std::next(allResearchers.begin(), selectedIndex);
        addArticleToResearcher(*(*it));
    }
    else if (option == 1)
    {
        list<DepartmentManager*> allDepartmentManagers = hospital->getDepartmentManagers();
        if (allDepartmentManagers.empty()) {
            cout << "No Department Managers available.\n";
            return;
        }

        cout << "Department Managers:\n";
        int index = 1;
        for (DepartmentManager* depMan : allDepartmentManagers) {
            cout << index++ << ": " << depMan->getFirstName() << " " << depMan->getLastName() << "\n";
        }

        int selectedIndex;
        do {
            cout << "Enter the index of the Department Manager to add an article to: ";
            cin >> selectedIndex;
            selectedIndex--;
        } while (selectedIndex < 0 || selectedIndex >= allDepartmentManagers.size());

        auto it = std::next(allDepartmentManagers.begin(), selectedIndex);
        addArticleToResearcher(*(*it));
    }
}


void HospitalManager::addArticleToResearcher(Researcher& r)
{
    cleanBuffer();
    string articleName;
    cout << "Enter the name of the article: ";
    getline(cin, articleName);

    Date* pDate = nullptr;
    bool isValidDate = false;
    int year, month, day;
    while (!isValidDate)
    {
        cout << "Enter the publish date (YYYY MM DD): ";
        cin >> year >> month >> day;
        try {
            pDate = new Date(day, month, year);
            isValidDate = true;
        }
        catch (string& msg) {
            cout << msg << endl;
        }
        if (!isValidDate)
        {
            cout << "\n----Enter The Date Again----\n";
        }
    }
    Article* newArticle = new Article(articleName, *pDate);

    if (r.addArticle(newArticle)) {
        cout << "Article added successfully to the researcher.\n";
    }
    else {
        cout << "Failed to add article to the researcher.\n";
    }

}

void HospitalManager::removePatient()
{
    list<Patient*> allPatients = hospital->getAllPatients();
    if (allPatients.empty()) {
        cout << "No patients available." << endl;
        return;
    }

    cout << "Select patient to remove:\n";
    int index = 1;
    for (Patient* patient : allPatients) {
        cout << index++ << ". " << patient->getFirstName() << " " << patient->getLastName() << endl;
    }

    int patientIndex;
    do {
        cout << "Enter Index:\n";
        cin >> patientIndex;
        patientIndex--;
    } while (patientIndex < 0 || patientIndex >= allPatients.size());

    auto it = std::next(allPatients.begin(), patientIndex);
    Patient* patientToRemove = *it;
    const Doctor* constDoctor = patientToRemove->getDoctor();

    // Cast away the const-ness of the pointer
    Doctor* doctor = const_cast<Doctor*>(constDoctor);

    if (doctor != nullptr) {
        doctor->removePatient(*patientToRemove);
    }

    const Department* constDepartment = patientToRemove->getDepartment();
    Department* department = const_cast<Department*>(constDepartment);
    department->removePatient(*patientToRemove);
    hospital->unhospitalizePatient(*patientToRemove);
    delete patientToRemove;
}

void HospitalManager::removeDoctor(Doctor& doctorToRemove, Department* department)
{
    // Remove the doctor from all specializations
    for (auto& specialization : doctorToRemove.getSpecializations()) {
        specialization->removeDoctorWithSpecial(&doctorToRemove);
    }

    // Remove the doctor from all patients
    list<Patient*> allPatients = hospital->getAllPatients();
    for (Patient* patient : allPatients) {
        if (*patient->getDoctor() == doctorToRemove) {
            patient->setDoctor(department->getDepartmentManager());
        }
    }

    hospital->removeDoctor(doctorToRemove);
}

void HospitalManager::removeDepartmentManager()
{
    std::list<DepartmentManager*>& departmentManagers = hospital->getDepartmentManagers();

    if (departmentManagers.empty()) {
        cout << "No Department Managers available." << endl;
        return;
    }

    // Display the list of Department Managers
    cout << "Select Department Manager to remove:\n";
    int index = 1;
    for (auto& dm : departmentManagers) {
        cout << index++ << ". " << dm->getFirstName() << " " << dm->getLastName() << endl;
    }

    int departmentManagerIndex;
    cin >> departmentManagerIndex;

    if (departmentManagerIndex < 1 || departmentManagerIndex > departmentManagers.size()) {
        cout << "Invalid Department Manager index." << endl;
        return;
    }
    // Find the Department Manager to remove
    auto it = departmentManagers.begin();
    std::advance(it, departmentManagerIndex - 1);
    DepartmentManager* departmentManagerToRemove = *it;
    // Remove the doctor from all patients
    for (Patient* patient : hospital->getAllPatients()) {
        if (patient->getDoctor() == departmentManagerToRemove) {
            patient->setDoctor(nullptr);
        }
    }
    // Remove the Department Manager from the list
    departmentManagers.erase(it);
    // Clean up
    delete departmentManagerToRemove;
}



void HospitalManager::changeDepartmentManager()
{
    int index;
    Department* department = nullptr;

    department = chooseDepartment();

    // Get department managers
    std::list<DepartmentManager*> departmentManagers = hospital->getDepartmentManagers();
    int managerIndex;

    if (departmentManagers.empty()) {
        cout << "No Department Managers available." << endl;
        return;
    }

    // Display department managers
    cout << "Select new manager for the department:\n";
    index = 1;
    for (auto& manager : departmentManagers) {
        cout << index++ << ". " << manager->getFirstName() << " " << manager->getLastName() << endl;
    }
    do {
        cout << "Enter Index:\n";
        cin >> managerIndex;
        managerIndex--;
    } while (managerIndex < 0 || managerIndex >= departmentManagers.size());

    // Access selected department manager
    auto managerIt = departmentManagers.begin();
    std::advance(managerIt, managerIndex);
    DepartmentManager* newManager = *managerIt;


    // Change department manager if different
    if (department->getDepartmentManager() != newManager)
    {
        // Remove the doctor from all patients
        list<Patient*> allPatients = hospital->getAllPatients();
        for (Patient* patient : allPatients) {
            if (*patient->getDoctor() == *department->getDepartmentManager()) {
                patient->setDoctor(newManager);
            }
        }
        department->setDepartmentManager(newManager);
    }
}


void HospitalManager::displayWorkerOnShift() const
{
    cout << "\nWorkers on shift:\n";
    cout << "\n----------\n";
    //Doctors
    displayDoctorsOnShift();
    cout << "\n----------\n";
    //Nurses
    displayNursesOnShift();
    cout << "\n----------\n";
    //Researchers
    displayResearchersOnShift();
    cout << "\n----------\n";
    //DepartmentManagers
    displayDepartmentManagersOnShift();
    cout << "\n----------\n";
    //CafeteriaWorkers
    displayCafeteriaWorkersOnShift();


}

void HospitalManager::displayDoctorsOnShift() const
{
    cout << "Doctors on shift:\n";
    // Retrieve doctors list
    std::list<Doctor*> doctors = hospital->getAllDoctors();
    for (auto& doctor : doctors)
    {
        if (doctor->getIsOnShift())
        {
            cout << *doctor << endl;
        }
    }
}

void HospitalManager::displayNursesOnShift() const
{
    cout << "Nurses on shift:\n";
    // Retrieve nurses list
    std::list<Nurse*> nurses = hospital->getAllNurses();
    for (auto& nurse : nurses)
    {
        if (nurse->getIsOnShift())
        {
            cout << *nurse << endl;
        }
    }
}

void HospitalManager::displayResearchersOnShift() const
{
    cout << "Researchers on shift:\n";
    // Retrieve researchers list
    std::list<Researcher*> researchers = hospital->getAllResearchers();
    for (auto& researcher : researchers)
    {
        if (researcher->getIsOnShift())
        {
            cout << *researcher << endl;
        }
    }
}

void HospitalManager::displayDepartmentManagersOnShift() const
{
    cout << "Department Managers on shift:\n";
    // Retrieve department managers list
    std::list<DepartmentManager*> departmentManagers = hospital->getDepartmentManagers();
    for (auto& manager : departmentManagers)
    {
        if (manager->getIsOnShift())
        {
            cout << *manager << endl;
        }
    }
}

void HospitalManager::displayCafeteriaWorkersOnShift() const
{
    cout << "Cafeteria Workers on shift:\n";
    Node<CafeteriaWorker*>* temp = hospital->getAllCafeteriaWorkers().getHead();
    int index = 1;
    while (temp != nullptr) {
        if (temp->data->getIsOnShift())
        {
            cout << index << ": " << *temp->data;
            index++;
        }
        temp = temp->next;
    }
}

bool HospitalManager::addInpatientDepartment(const string& name, const string& address)
{
    InpatientDepartment* inpatientDepartment = new InpatientDepartment(name, address);
    hospital->addInpatientDepartment(*inpatientDepartment);
    return true;
}

bool HospitalManager::addCafeteria(const string& name, const string& address)
{
    Cafeteria* cafeteria = new Cafeteria(address, name);
    hospital->addCafeteria(*cafeteria);
    return true;
}

void HospitalManager::addBuilding()
{
    string address, nameOfBuilding;
    int option;

    cout << "Enter which bulding do you want to add (1 - InpatientDepartment, 2 - Cafeteria)\n";
    cin >> option;

    cleanBuffer();
    cout << "Enter name of building\n";
    getline(cin, nameOfBuilding);
    //cleanBufferr();

    cout << "Enter address of building\n";
    getline(cin, address);
    //cleanBufferr();



    switch (option)
    {
    case 1:
        if (addInpatientDepartment(nameOfBuilding, address))
            cout << "InpatientDepartment added!";
        break;
    case 2:
        if (addCafeteria(nameOfBuilding, address))
            cout << "Cafeteria added!";
        break;
    default:
        break;
    }
}

bool HospitalManager::addSpecialization()
{
    string name;
    cout << "Enter Specialization name: \n";
    getline(cin, name);

    return hospital->addSpecialization(Specialization(name));
}

void HospitalManager::addSpecializationToWorker()
{
    if (hospital->getAllSpecializations().empty() ||
        (hospital->getAllDoctors().empty() && hospital->getDepartmentManagers().empty()))
    {
        cout << "Need to add Specialization/Doctor first!\n";
        return;
    }

    int specializationIndex, workerType, workerIndex;

    // Determine worker type (Doctor or DepartmentManager)
    do {
        if (hospital->getAllDoctors().empty())
            workerType = 0;
        else if (hospital->getDepartmentManagers().empty())
            workerType = 1;
        else {
            cout << "Add Specialization Enter: 1 for Doctor, 0 for DepartmentManager:\n";
            cin >> workerType;
        }
    } while (workerType < 0 || workerType > 1);

    // Choose Specialization
    do {
        cout << "Choose Specialization" << endl;
        int index = 1;
        for (const auto& specialization : hospital->getAllSpecializations())
        {
            cout << index++ << ". " << specialization->getNameOfSpecialization() << endl;
        }

        cin >> specializationIndex;
        specializationIndex--;
    } while (specializationIndex < 0 || specializationIndex >= hospital->getAllSpecializations().size());

    // Choose Worker (Doctor or Department Manager)
    if (workerType == 1)
    {
        cout << "Choose Doctor" << endl;
        int index = 1;
        for (const auto& doctor : hospital->getAllDoctors())
        {
            cout << index++ << ". " << *doctor << endl;
        }

        do {
            cout << "Enter Index:\n";
            cin >> workerIndex;
            workerIndex--;
        } while (workerIndex < 0 || workerIndex >= hospital->getAllDoctors().size());

        auto doctorIt = hospital->getAllDoctors().begin();
        std::advance(doctorIt, workerIndex);
        (*doctorIt)->addSpecialization(*std::next(hospital->getAllSpecializations().begin(), specializationIndex));
    }
    else
    {
        cout << "Choose Department Manager" << endl;
        int index = 1;
        for (const auto& manager : hospital->getDepartmentManagers())
        {
            cout << index++ << ". " << *manager << endl;
        }

        do {
            cout << "Enter Index:\n";
            cin >> workerIndex;
            workerIndex--;
        } while (workerIndex < 0 || workerIndex >= hospital->getDepartmentManagers().size());

        auto managerIt = hospital->getDepartmentManagers().begin();
        std::advance(managerIt, workerIndex);
        (*managerIt)->addSpecialization(*std::next(hospital->getAllSpecializations().begin(), specializationIndex));
    }
}

void HospitalManager::patientCallNurse() const
{
    if (hospital->getAllPatients().empty())
    {
        cout << "No Patients at the Hospital\n";
        return;
    }
    if (hospital->getAllNurses().empty())
    {
        cout << "No Nurses at the Hospital\n";
        return;
    }

    int patientIndex;
    cout << "Choose Patient" << endl;

    int index = 1;
    for (auto patient = hospital->getAllPatients().begin(); patient != hospital->getAllPatients().end(); ++patient, ++index) {
        cout << "Patient " << index << ":" << **patient << endl;
    }

    do {
        cout << "Enter Index:\n";
        cin >> patientIndex;
        patientIndex--;
    } while (patientIndex < 0 || patientIndex >= hospital->getAllPatients().size());

    cout << "\n**CALLING NURSE**\n";
    auto patientIt = hospital->getAllPatients().begin();
    std::advance(patientIt, patientIndex);
    Nurse* nurse = (*patientIt)->callNurse();

    if (nurse == nullptr)
    {
        cout << "No Available Nurses in your department." << endl;
        return;
    }
    else {
        int need;
        cout << *nurse << endl;
        cout << "Nurse, do you need a Doctor? (1 for yes, 0 for no)" << endl;
        cin >> need;
        if (need == 1)
        {
            cout << "\n**NURSE CALLING DOCTOR!**\n";
            if (nurse->callDoctor((*patientIt)->getDoctor()))
                cout << *(*patientIt)->getDoctor() << endl;
            else
                cout << "The Doctor Is Not On Shift" << endl;
        }
    }
}

void HospitalManager::displayHospital() const {
    cout << "Hospital Information:" << std::endl;
    cout << "=====================" << std::endl;
    cout << "\n----------Buildings----------\n";
    displayBuildings();
    cout << "\n----------Doctors----------\n";
    displayDoctors();
    cout << "\n----------Nurses----------\n";
    displayNurses();
    cout << "\n----------Cafeteria Workers----------\n";
    displayCafeteriaWorkers();
    cout << "\n----------Researchers----------\n";
    displayResearchers();
    cout << "\n----------Department Managers----------\n";
    displayDepartmentManagers();
    cout << "\n----------Patients----------\n";
    displayPatients();
    cout << "\n----------Specializations----------\n";
    displaySpecializations();
}



