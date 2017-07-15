//Opertaor to pick up an object into the hand

#pragma once
#include "Operator.h"
class PickUp :
	public Operator
{
public:
	PickUp();
	~PickUp();
	virtual bool ValidOperator(const Object* block1, const Object* block2, bool &physical) override;
	virtual void Operate(Object* block1, Object* block2, bool test) override;

};

