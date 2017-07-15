//Stores objects and the objects store their current state relative to other objects (eg. above or below objects)
//Stores operators to manipulate the objects in the game
//Stores goal state of the game which is to be satisfied by Handler

#pragma once
#include "Hand.h"
#include "Block.h"
#include "Object.h"
#include "PickUp.h"
#include "PutDown.h"
#include "Table.h"
#include "StackBlocks.h"
#include <vector>
class Game
{
public:
	std::vector<Object*> objects;
	std::vector<Operator*> operators;
	std::vector<StackBlocks> goalState;
public:
	Game();
	Game(std::vector<StackBlocks> Startstate, std::vector<StackBlocks> goalState);
	Game(const Game &game);
	~Game();
	Game& operator=(const Game& other);
	//Compares game states
	bool operator==(const Game& other);
	//Compares this game to other games in vector
	bool EqualGame(const std::vector<Game>& gameStates);
	//Returns vector of satisfy state of each goal
	std::vector<bool> conditionchecker();
	//Returns true if all goals are satisfied
	bool satisfied();
private:
};

