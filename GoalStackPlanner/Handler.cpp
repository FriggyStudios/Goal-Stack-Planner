#include "Handler.h"
#include <ctime> 


Handler::Handler(Game game)
{
	this->game = game;
}

Handler::~Handler()
{
}

//Satisfies one unsatisifed goal
bool Handler::Satisfy()
{
	if (game.satisfied())
	{
		return true;
	}

	//Store illegal and legal operators in seperate lists (1)
	legalOperators = std::vector<OperatorStorage>();
	illegalOperators = std::vector<OperatorStorage>();
	for (Operator op : game.operators)
	{
		for(unsigned i = 0; i < game.objects.size();i++)
		{
			for (unsigned j = 0; j < game.objects.size(); j++)
			{
				if (i != j)
				{
					bool physical;
					if (op.ValidOperator(game.objects[i], game.objects[j], physical))
					{
						legalOperators.push_back(OperatorStorage(op, i, j));
					}
					else if(physical)
					{
						illegalOperators.push_back(OperatorStorage(op, i, j));
					}
				}
			}
		}
	}
	//Check if legal operator satisfies unsatisfied goal state and apply operator (2)
	std::vector<bool> conditionsSatisfied = game.conditionchecker();
	srand((unsigned)time(0));
	int toSatisfy;
	while (true)
	{
		toSatisfy = (rand() % conditionsSatisfied.size());
		if (conditionsSatisfied[toSatisfy] == false)
		{
			break;
		}
	}
	for (OperatorStorage opStorage : legalOperators)
	{
		gameTest = Game(game);
		opStorage.op.Operate(gameTest.objects[opStorage.iterator1], gameTest.objects[opStorage.iterator2]);
		std::vector<bool> conditionsSatisfiedTest = gameTest.conditionchecker();
		if (conditionsSatisfiedTest[toSatisfy] == true)
		{
			opStorage.op.Operate(game.objects[opStorage.iterator1], game.objects[opStorage.iterator2]);
			return game.satisfied();
		}
	}
	//Else Find illegal operator to satisfy unsatisfied goal state
	for (OperatorStorage opStorage : illegalOperators)
	{
		gameTest = Game(game);
		opStorage.op.Operate(gameTest.objects[opStorage.iterator1], gameTest.objects[opStorage.iterator2],true);
		std::vector<bool> conditionsSatisfiedTest = gameTest.conditionchecker();
		if (conditionsSatisfiedTest[toSatisfy] == true)
		{
			toOperate.push_back(opStorage);
		}
	}
	while (true)
	{
		//Set function to be satisfied that operator legal, repeat (2)
		//Check if legal operator satisfies unsatisfied goal state and apply operator (2)
		for (OperatorStorage opStorage : legalOperators)
		{
			gameTest = Game(game);
			opStorage.op.Operate(gameTest.objects[opStorage.iterator1], gameTest.objects[opStorage.iterator2]);
			bool physical;
			if (toOperate.back().op.ValidOperator(gameTest.objects[opStorage.iterator1], gameTest.objects[opStorage.iterator2], physical))
			{
				opStorage.op.Operate(game.objects[opStorage.iterator1], game.objects[opStorage.iterator2]);
				for (int i = toOperate.size() - 1; i >= 0; i--)
				{
					toOperate[i].op.Operate(game.objects[toOperate[i].iterator1], game.objects[toOperate[i].iterator2]);
				}
				return game.satisfied();
			}
		}
		//Else Find illegal operator to satisfy unsatisfied goal state
		for (OperatorStorage opStorage : illegalOperators)
		{
			gameTest = Game(game);
			opStorage.op.Operate(gameTest.objects[opStorage.iterator1], gameTest.objects[opStorage.iterator2], true);
			std::vector<bool> conditionsSatisfiedTest = gameTest.conditionchecker();
			if (conditionsSatisfiedTest[toSatisfy] == true)
			{
				toOperate.push_back(opStorage);
			}
		}

	}
	//If legal operators found to satisfy unsatisfied goal state, apply operators, repeat (1)

	return game.satisfied();
}

//figure out way to check for satisfied conditions in one algorithm