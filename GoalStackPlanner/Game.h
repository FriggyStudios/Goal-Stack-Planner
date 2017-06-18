#pragma once
#include "Hand.h"
#include "Block.h"
#include "Object.h"
#include "PickUp.h"
#include "PutDown.h"
#include "Table.h"
#include <vector>
class Game
{public:
	std::vector<Object> objects;
	std::vector<Operator> operators;
public:
	Game();
	Game(Game &game);
	~Game();
	std::vector<bool> conditionchecker();
	bool satisfied();
private:
	bool condition1();
	bool condition2();
	bool condition3();
};

