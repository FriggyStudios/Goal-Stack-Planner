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
	bool toOperateAdded = false;
	while (!toOperateAdded)
	{
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
			opStorage.op->Operate(gameTest.objects[opStorage.iterator1], gameTest.objects[opStorage.iterator2], true);
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
			opStorage.op->Operate(gameTest.objects[opStorage.iterator1], gameTest.objects[opStorage.iterator2], true);
			std::vector<bool> conditionsSatisfiedTest = gameTest.conditionchecker();
			if (conditionsSatisfiedTest[toSatisfy] == true)
			{
				toOperate.push_back(opStorage);
				toOperateAdded = true;
				break;
			}
		}
	}
	while (true)
	{
		//Set function to be satisfied that operator legal, repeat (2)
		//Check if legal operator satisfies unsatisfied goal state and apply operator (2)
		for (OperatorStorage opStorage : legalOperators)
		{
			gameTest = Game(game);
			opStorage.op->Operate(gameTest.objects[opStorage.iterator1], gameTest.objects[opStorage.iterator2],true);
			bool physical;
			if (toOperate.back().op->ValidOperator(gameTest.objects[toOperate.back().iterator1], gameTest.objects[toOperate.back().iterator2], physical))
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
		for(int i = 3;i <= maxOperationsIteration;i++)
		{
			bool illegal;
			//Else Find illegal operator to satisfy unsatisfied goal state
			if (AddGoalOperators(i, illegal))
			{
				return game.satisfied();
			}
			if (illegal)
			{
				i = 2;
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

bool Handler::AddGoalOperators(int iterations, bool& illegal)
{
	illegal = false;
	//std::cout << "AddGoal " << iterations << '\n';
	for (int legalfirst = -1; legalfirst < 1; legalfirst++)
	{
		std::vector<int> locations = std::vector<int>();
		std::vector<OperatorStorage> toOperateLocal;
		/*if (iterations = 1)
		{
			toOperateLocal = illegalOperators;
		}
		else*/
		if (legalfirst == -1)
		{
			for (int i = 0; i < iterations + legalfirst; i++)
			{
				locations.push_back(0);
			}
			std::vector<OperatorStorage> operators;
			operators.insert(operators.end(), legalOperators.begin(), legalOperators.end());
			operators.insert(operators.end(), illegalOperators.begin(), illegalOperators.end());
			int max = pow(operators.size(), iterations + legalfirst);
			for (OperatorStorage op : legalOperators)
			{
				toOperateLocal.push_back(op);
				for (int k = 0; k < max; k++)
				{
					for (int i = 0; i < iterations + legalfirst; i++)
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
		}
		else
		{
			locations.clear();
			for (int i = 0; i < iterations; i++)
			{
				locations.push_back(0);
			}
			std::vector<OperatorStorage> operators;
			operators.insert(operators.end(), legalOperators.begin(), legalOperators.end());
			operators.insert(operators.end(), illegalOperators.begin(), illegalOperators.end());
			int max = pow(operators.size(), iterations);
			for (int k = 0; k < max; k++)
			{
				for (int i = 0; i < iterations; i++)
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

		for (int i = 0; i < toOperateLocal.size() - 1; i += iterations)
		{
			bool legal = true;
			gameTest = Game(game);
			for (int j = 0; j < iterations; j++)
			{
				toOperateLocal[i + j].op->Operate(gameTest.objects[toOperateLocal[i + j].iterator1], gameTest.objects[toOperateLocal[i + j].iterator2], true);
				bool physical;
				if ((j + 1) < iterations)
				{ 
					if (!toOperateLocal[i + j + 1].op->ValidOperator(gameTest.objects[toOperateLocal[i + j + 1].iterator1], gameTest.objects[toOperateLocal[i + j + 1].iterator2], physical))
					{
						legal = false;
						break;
					}
				}
				else if (!toOperate.back().op->ValidOperator(gameTest.objects[toOperate.back().iterator1], gameTest.objects[toOperate.back().iterator2], physical))
				{
					legal = false;
				}
			}
			if (legal)
			{
				for (int i = toOperate.size() - 1; i >= 0; i--)
				{
					toOperate[i].op->Operate(gameTest.objects[toOperate[i].iterator1], gameTest.objects[toOperate[i].iterator2],true); 
					bool physical;
					if ((i - 1) >= 0)
					{
						if (!toOperate[i-1].op->ValidOperator(gameTest.objects[toOperate[i-1].iterator1], gameTest.objects[toOperate[i-1].iterator2],physical))
						{
							legal = false;
							break;
						}
					}
				}
				if (legal)
				{
					for (int j = iterations - 1; j >= 0; j--)
					{
						toOperate.push_back(toOperateLocal[i + j]);
					}
					if (std::find(legalOperators.begin(), legalOperators.end(), toOperate.back()) != legalOperators.end())
					{
						for (int i = toOperate.size() - 1; i >= 0; i--)
						{
							toOperate[i].op->Operate(game.objects[toOperate[i].iterator1], game.objects[toOperate[i].iterator2]);
						}
						toOperate.clear();
						return true;
					}
					else
					{
						illegal = true;
						return false;
					}
				}
			}
		}
	}
	illegal = false;
	return false;
}