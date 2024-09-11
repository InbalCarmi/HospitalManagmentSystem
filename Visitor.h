#pragma once
class Visitable;

class Visitor
{
public:
	virtual void visit(Visitable* element) = 0;
};