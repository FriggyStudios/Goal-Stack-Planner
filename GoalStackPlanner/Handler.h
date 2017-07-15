//Solves quickest to solve a goal of a Game
//Eventually solves all goals of a Game on repeated call of Satisfy

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
	int maxOperationsIteration = 8;
public:
	Handler(Game game);
	~Handler();
	//Starts multiple thread to satisfies one unsatisifed goal each
	bool Satisfy();
private:
	//Find series of operator so last operator in toOperate is legal
	//If first operator in series is legal, return true
	//Else return false
	bool AddGoalOperators(int iterations, std::vector<OperatorStorage>& toOperate);
	//Satisfies assigned unsatisfied goal
	//Break if other thread solves another goal first
	void ThreadSolveGoal(int satisfy);
};

