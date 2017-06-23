#pragma once
#include "Block.h"
#include "Hand.h"
#include "Object.h"
class Operator
{
private:

public:
	virtual bool ValidOperator(const Object* block1, const Object* block2, bool &physical)
	{
		physical = false;
		return false;
	};
	virtual void Operate(Object* block1, Object* block2, bool test = false) {};
	Operator();
	Operator(Operator &op);
	~Operator();
};

