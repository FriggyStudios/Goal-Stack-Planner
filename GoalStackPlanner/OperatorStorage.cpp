#include "OperatorStorage.h"



OperatorStorage::OperatorStorage(Operator *op, int iterator1, int iterator2)
{
	this->op = op;
	this->iterator1 = iterator1;
	this->iterator2 = iterator2;
}


OperatorStorage::~OperatorStorage()
{
}

bool OperatorStorage::operator==(const OperatorStorage& rhs)
{
	if (op == rhs.op &&
		iterator1 == rhs.iterator1 &&
		iterator2 == rhs.iterator2)
	{
		return true;
	}
	return false;
}