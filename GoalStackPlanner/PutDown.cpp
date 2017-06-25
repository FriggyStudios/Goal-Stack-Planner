#include "PutDown.h"
#include <iostream>



PutDown::PutDown()
{
}


PutDown::~PutDown()
{
}


bool PutDown::ValidOperator(const Object* block1, const Object* block2, bool &physical)
{
	physical = true;
	if (block1->hand == true ||
		block2->hand == true ||
		block1->table == true)
	{
		physical = false;
		return false;
	}
	if (block1->inHand != NULL &&
		block2->above == NULL)
	{
		return true;
	}
	else
		return false;
}

void PutDown::Operate(Object* block1, Object* block2,bool test=false)
{
	bool physical;
	if (test || ValidOperator(block1, block2,physical))
	{
		if(block1->inHand)
			block1->inHand->inHand = NULL;
		block1->inHand = NULL;
		if (block2->table == false)
		{
			block2->above = block1;
			block1->below = block2;
		}
		else
		{
			block1->below = NULL;
		}
		if (!test)
			std::cout << "Put down " << block1->name << " onto " << block2->name << '\n';
	}
	else
		std::cerr << "PutDown Error";
}
