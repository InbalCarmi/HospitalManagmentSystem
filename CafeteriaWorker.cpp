#include "CafeteriaWorker.h"
#include "Cafeteria.h"

// Constructors
CafeteriaWorker::CafeteriaWorker(const Worker& base, Cafeteria& cafeteriaHeWork)
    : Worker(base), cafeteriaHeWork(&cafeteriaHeWork) {}

CafeteriaWorker::CafeteriaWorker(const Worker& base)
    : Worker(base), cafeteriaHeWork(nullptr) {}

// get and setters
bool CafeteriaWorker::setCafeteria(Cafeteria* newCafeteriaHeWork)
{
    if (cafeteriaHeWork != newCafeteriaHeWork)
    {
        if (cafeteriaHeWork != nullptr)
            cafeteriaHeWork->fireWorker(*this);

        cafeteriaHeWork = newCafeteriaHeWork;

        if (cafeteriaHeWork != nullptr)
            cafeteriaHeWork->addWorker(*this);
    }
    return true;
}

const Cafeteria* CafeteriaWorker::getCafeteria() const
{
    return cafeteriaHeWork;
}

// Operators
bool CafeteriaWorker::operator==(const CafeteriaWorker& other) const
{
    // Check if the base Worker attributes are equal and if they work in the same cafeteria
    return static_cast<const Worker&>(*this) == static_cast<const Worker&>(other) && cafeteriaHeWork == other.cafeteriaHeWork;
}

bool CafeteriaWorker::operator!=(const CafeteriaWorker& other) const
{
    return !(*this == other);
}

// Methods
void CafeteriaWorker::toOs(std::ostream& os) const
{
    Worker::toOs(os);
    os << "Cafeteria He Works For: " << (cafeteriaHeWork ? cafeteriaHeWork->getBuildingName() : "None");
    os << std::endl;
}
