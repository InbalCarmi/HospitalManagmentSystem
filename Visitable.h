#pragma once
#include "Visitor.h"

class Visitable
{
public:
	virtual void accept(Visitor* visitor) = 0;
};