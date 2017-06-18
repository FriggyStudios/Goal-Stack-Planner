#pragma once
#include "Operator.h"
class PutDown :
	public Operator
{
public:
	PutDown();
	~PutDown();
	virtual bool ValidOperator(const Object& block1, const Object& block2, bool &physical) override;
	virtual void Operate(Object& block1, Object& block2, bool test) override;
};

