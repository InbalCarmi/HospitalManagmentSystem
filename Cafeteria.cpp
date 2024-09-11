#include "Cafeteria.h"

// Constructor
Cafeteria::Cafeteria(const string& address, const string& nameOfBuilding) 
    : Building(nameOfBuilding, address)
{
}

// Setters and getters
void Cafeteria::setNameOfCafeteria(const string& nameOfCafeteria)
{
    setBuildingName(nameOfCafeteria);
}

string Cafeteria::getNameOfCafeteria() const
{
    return getBuildingName();
}

list<CafeteriaWorker*> Cafeteria::getCafeteriaWorkers() const
{
    return cafeteriaWorkers;
}

int Cafeteria::getNumOfCafeteriaWorkers() const
{
    return (int)cafeteriaWorkers.size();
}

// Methods for managing workers
bool Cafeteria::addWorker(CafeteriaWorker& worker)
{
    // Ensure the worker isn't already working for this cafeteria
    if (worker.getCafeteria() == this)
        return false;

    // Add the worker to this cafeteria
    cafeteriaWorkers.push_back(&worker);

    // Update the worker's cafeteria
    worker.setCafeteria(this);

    return true;
}

bool Cafeteria::fireWorker(CafeteriaWorker& worker)
{
    // Ensure the worker is associated with this cafeteria
    if (worker.getCafeteria() != this)
        return false;

    // Remove the worker from the list
    cafeteriaWorkers.remove(&worker);

    // Optionally delete the worker if necessary
    delete &worker; // This should be reconsidered to avoid deleting a stack object

    return true;
}

// Override the toOs method from the Building class
void Cafeteria::toOs(ostream& os) const
{
    os << "Number of Cafeteria Workers: " << cafeteriaWorkers.size();

    // Output list of workers
    if (!cafeteriaWorkers.empty())
    {
        os << "\nCafeteria Workers: ";
        for (auto it = cafeteriaWorkers.begin(); it != cafeteriaWorkers.end(); ++it)
        {
            os << (*it)->getFirstName() << " " << (*it)->getLastName();
            if (std::next(it) != cafeteriaWorkers.end())
            {
                os << ", ";
            }
        }
    }
    os << std::endl;
}
