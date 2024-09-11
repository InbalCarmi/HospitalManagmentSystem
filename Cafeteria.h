#pragma once

#include <list>
#include <string>
#include "Building.h"
#include "CafeteriaWorker.h"

using namespace std;

class Cafeteria : public Building
{
private:
    list<CafeteriaWorker*> cafeteriaWorkers;

public:
    // Constructors
    Cafeteria(const string& address, const string& nameOfBuilding);

    // Methods for managing workers
    bool addWorker(CafeteriaWorker& worker);
    bool fireWorker(CafeteriaWorker& worker);
    // Setters and getters
    void setNameOfCafeteria(const string& nameOfCafeteria);
    string getNameOfCafeteria() const;
    list<CafeteriaWorker*> getCafeteriaWorkers() const;
    int getNumOfCafeteriaWorkers() const;

    // Override the toOs method from the Building class
    virtual void toOs(ostream& os) const override;

    // Destructor
    virtual ~Cafeteria() = default;
};
