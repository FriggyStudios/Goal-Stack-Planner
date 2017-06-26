#pragma once
#include "Game.h"
#include "OperatorStorage.h"
#include <vector>
class Handler
{
private:
	Game game;
	Game gameTest;
	std::vector<OperatorStorage> legalOperators;
	std::vector<OperatorStorage> illegalOperators;
	std::vector<OperatorStorage> toOperate;
	Handler& operator=(const Handler& other);
public:
	Handler(Game game);
	~Handler();
	bool Satisfy();
	int maxOperationsIteration = 8;
private:
	bool AddGoalOperators(int iterations, bool& illegal);
};

