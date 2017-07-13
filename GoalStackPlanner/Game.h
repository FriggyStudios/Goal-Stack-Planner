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
{public:
	std::vector<Object*> objects;
	std::vector<Operator*> operators;
	std::vector<StackBlocks> goalState;
public:
	Game();
	Game(std::vector<StackBlocks> Startstate, std::vector<StackBlocks> goalState);
	Game(Game &game);
	~Game();
	Game& operator=(const Game& other);
	bool operator==(const Game& other);
	std::vector<bool> conditionchecker();
	bool satisfied();
private:
};

