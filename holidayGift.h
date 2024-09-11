#pragma once
#include "Visitor.h"
#include "Worker.h"

class HolidayGift : public Visitor
{
public:
	HolidayGift(int money) : money(money) {}

	virtual void visit(Visitable* element) override
	{
		Worker* emp = (Worker*)element;
		emp->giveRaise(money);
	}
private:
	int money;
};