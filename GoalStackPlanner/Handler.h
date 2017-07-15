#pragma once
#include "Game.h"
#include "OperatorStorage.h"
#include <vector>
#include <mutex>
class Handler
{
private:
	Game game;
	std::vector<OperatorStorage> legalOperators;
	std::vector<OperatorStorage> illegalOperators;
	std::vector<Game> gameStates;
	Handler& operator=(const Handler& other);
	bool threadSolved;
public:
	Handler(Game game);
	~Handler();
	bool Satisfy();
	int maxOperationsIteration = 8;
private:
	bool AddGoalOperators(int iterations, std::vector<OperatorStorage>& toOperate, bool& illegal);
	void ThreadSolveGoal(int satisfy);
};

