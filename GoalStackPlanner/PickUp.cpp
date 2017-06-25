#include "PickUp.h"
#include <iostream>

PickUp::PickUp()
{
}


PickUp::~PickUp()
{
}

bool PickUp::ValidOperator(const Object* block1, const Object* block2, bool &physical)
{
	physical = true;
	if (
		block1->hand == true ||
		block2->hand == false ||
		block1->table == true ||
		block2->table == true)
	{
		physical = false;
		return false;
	}
	if (block1->above == NULL &&
		block2->inHand == NULL)
	{
		return true;
	}
	else
		return false;
}

void PickUp::Operate(Object* block1, Object* block2, bool test)
{
	bool physical;
	if (test || ValidOperator(block1, block2, physical))
	{
		if (block1->below != NULL)
		{
			block1->below->above = NULL;
			block1->below = NULL;
		}
		block1->inHand = block2;
		block2->inHand = block1;

		if (!test)
			std::cout << "Pick up " << block1->name << '\n';
	}
	else
		std::cerr << "PickUp Error";
}
