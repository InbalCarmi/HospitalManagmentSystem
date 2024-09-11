#pragma once
#include "Visitor.h"
#include "Worker.h"

class IncomeVisitor : public Visitor
{
public:
	IncomeVisitor(int money) : money(money) {}

	virtual void visit(Visitable* element) override
	{
		Worker* emp = (Worker*)element;
		emp->giveRaise(money);
	}
private:
	int money;
};