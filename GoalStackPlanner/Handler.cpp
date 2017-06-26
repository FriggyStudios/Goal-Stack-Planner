#include "Handler.h"
#include <ctime> 
#include <iostream>


Handler::Handler(Game game)
{
	this->game = Game(game);
	this->gameTest = this->game;
	this->illegalOperators = std::vector<OperatorStorage>();
	this->illegalOperators = std::vector<OperatorStorage>();
	this->toOperate = std::vector<OperatorStorage>();
}

Handler::~Handler()
{
}

Handler& Handler:: operator=(const Handler& other)
{
	if (this == &other)
		return (*this); // Taking care for self-assignment

	this->legalOperators = other.legalOperators;
	this->illegalOperators = other.illegalOperators;
	this->game = other.game;
	this->gameTest = other.gameTest;
	
	return (*this);
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
	for (Operator* op : game.operators)
	{
		for(unsigned i = 0; i < game.objects.size();i++)
		{
			for (unsigned j = 0; j < game.objects.size(); j++)
			{
				if (i != j)
				{
					bool physical;
					if (op->ValidOperator(game.objects[i], game.objects[j], physical))
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
		opStorage.op->Operate(gameTest.objects[opStorage.iterator1], gameTest.objects[opStorage.iterator2],true);
		std::vector<bool> conditionsSatisfiedTest = gameTest.conditionchecker();
		if (conditionsSatisfiedTest[toSatisfy] == true)
		{
			opStorage.op->Operate(game.objects[opStorage.iterator1], game.objects[opStorage.iterator2]);
			return game.satisfied();
		}
	}
	//Else Find illegal operator to satisfy unsatisfied goal state
	for (OperatorStorage opStorage : illegalOperators)
	{
		gameTest = Game(game);
		opStorage.op->Operate(gameTest.objects[opStorage.iterator1], gameTest.objects[opStorage.iterator2],true);
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
			opStorage.op->Operate(gameTest.objects[opStorage.iterator1], gameTest.objects[opStorage.iterator2]);
			bool physical;
			if (toOperate.back().op->ValidOperator(gameTest.objects[toOperate.back().iterator1], gameTest.objects[toOperate.back().iterator2], physical),true)
			{
				toOperate.push_back(opStorage);
				for (int i = toOperate.size() - 1; i >= 0; i--)
				{
					toOperate[i].op->Operate(game.objects[toOperate[i].iterator1], game.objects[toOperate[i].iterator2]);
				}
				toOperate.clear();
				return game.satisfied();
			}
		}
		for(int i = 2;i <= maxOperationsIteration;i++)
		{
			//Else Find illegal operator to satisfy unsatisfied goal state
			if (AddGoalOperators(i))
			{
				return game.satisfied();
			}
			if (i == maxOperationsIteration)
			{
				std::cerr << "AddGoalOperators called more than " << maxOperationsIteration << "times\n";
			}
		}

	}
	//If legal operators found to satisfy unsatisfied goal state, apply operators, repeat (1)

	return game.satisfied();
}

bool Handler::AddGoalOperators(int iterations)
{
	std::cout << iterations << '\n';
	std::vector<int> locations = std::vector<int>();
	std::vector<OperatorStorage> toOperateLocal;
	/*if (iterations = 1)
	{
		toOperateLocal = illegalOperators;
	}
	else*/
	for (int i = 0; i < iterations - 1; i++)
	{
		locations.push_back(0);
	}
	std::vector<OperatorStorage> operators;
	operators.insert(operators.end(), legalOperators.begin(), legalOperators.end());
	operators.insert(operators.end(), illegalOperators.begin(), illegalOperators.end());
	int max = pow(operators.size(), iterations - 1);
	for (OperatorStorage opStorage : legalOperators)
	{
		for (int k = 0; k < max; k++)
		{
			toOperateLocal.push_back(opStorage);
			for (int i = 0; i < iterations - 1; i++)
			{
				toOperateLocal.push_back(operators[locations[i]]);
			}
			for (int j = locations.size() - 1; j >= 0; j--)
			{
				if (locations[j] != operators.size() - 1)
				{
					locations[j]++;
					break;
				}
				else
				{
					locations[j] = 0;
				}
			}
		}
	}
	if (iterations == 2)
	{
		int x = 3;
	}
	for (int i = 0; i < toOperateLocal.size() - 1; i += iterations)
	{
		bool legal = true;
		gameTest = Game(game);
		for (int j = 0; j < iterations; j++)
		{
			toOperateLocal[i + j].op->Operate(gameTest.objects[toOperateLocal[i + j].iterator1], gameTest.objects[toOperateLocal[i + j].iterator2], false);
			bool physical;
			if ((j + 1) < iterations)
			{
				if (!toOperateLocal[i + j + 1].op->ValidOperator(gameTest.objects[toOperateLocal[i + j + 1].iterator1], gameTest.objects[toOperateLocal[i + j + 1].iterator2], physical))
				{
					legal = false;
					break;
				}
			}
			else if (!toOperate.back().op->ValidOperator(gameTest.objects[toOperate.back().iterator1], gameTest.objects[toOperate.back().iterator2],physical))
			{
				legal = false;
			}
		}
		if (legal)
		{
			for (int j = iterations-1; j >= 0; j--)
			{
				toOperate.push_back(toOperateLocal[i + j]);
			}
			for (int i = toOperate.size() - 1; i >= 0; i--)
			{
				toOperate[i].op->Operate(game.objects[toOperate[i].iterator1], game.objects[toOperate[i].iterator2]);
			}
			return true;
		}
	}
	return false;
}