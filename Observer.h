#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Observer
{
public:
	Observer(const string& firstName, const string& lastName) : firstName(firstName), lastName(lastName) {}
	virtual void notify(string specializationName) const = 0;
	virtual Observer* clone() const = 0;
	const string& getOBFirstName() const { return firstName; }
	const string& getOBLastName() const { return lastName; }
protected:
	string firstName;
	string lastName;
}; 
