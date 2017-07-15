//Operator parent class
//Operators manipulate state of objects in a game

#pragma once
#include "Block.h"
#include "Hand.h"
#include "Object.h"
class Operator
{
private:

public:
	//Return true if the class operate is a legal operate on these objects
	virtual bool ValidOperator(const Object* block1, const Object* block2, bool &physical)
	{
		physical = false;
		return false;
	};
	//Operate class operate on these objects
	virtual void Operate(Object* block1, Object* block2, bool test = false) {};
	Operator();
	Operator(Operator &op);
	~Operator();
};

