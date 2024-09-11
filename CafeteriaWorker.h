#pragma once
#include "Worker.h"

class Cafeteria;

class CafeteriaWorker : public Worker
{
private:
    Cafeteria* cafeteriaHeWork;

public:
    // Constructors
    CafeteriaWorker(const Worker& base);
    CafeteriaWorker(const Worker& base, Cafeteria& cafeteriaHeWork);

    // Setters and Getters
    bool setCafeteria(Cafeteria* cafeteriaHeWork);
    const Cafeteria* getCafeteria() const;

    // Operators
    bool operator==(const CafeteriaWorker& other) const;
    bool operator!=(const CafeteriaWorker& other) const;

    // Methods
    void toOs(std::ostream& os) const;
};
