#include "PutDown.h"
#include <iostream>



PutDown::PutDown()
{
}


PutDown::~PutDown()
{
}


bool PutDown::ValidOperator(const Object& block1, const Object& block2, bool &physical)
{
	physical = true;
	if (block1.hand == true &&
		block2.hand == true &&
		block1.table == true)
	{
		physical = false;
		return false;
	}
	if (block1.inHand != nullptr &&
		block2.above == nullptr)
	{
		return true;
	}
	else
		return false;
}

void PutDown::Operate(Object& block1, Object& block2,bool test=false)
{
	bool physical;
	if (test || ValidOperator(block1, block2,physical))
	{
		block1.inHand->inHand = nullptr;
		block1.inHand = nullptr;
		if (block2.table == false)
		{
			block2.above = &block1;
			block1.below = &block2;
		}
		else
		{
			block1.below = nullptr;
		}
	}
	else
		std::cerr << "PutDown Error";
}
