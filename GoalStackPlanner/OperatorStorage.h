#pragma once
#include "Object.h"
#include "Operator.h"
#include <functional>
class OperatorStorage
{
public:
	Operator *op;
	int iterator1;
	int  iterator2;
public:
	OperatorStorage(Operator *op, int iterator1, int iterator2);
	~OperatorStorage();
	bool operator==(const OperatorStorage& rhs);
};

