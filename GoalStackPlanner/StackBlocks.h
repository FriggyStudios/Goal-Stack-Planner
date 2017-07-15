//Stores vector of strings
//Represents the names of objects on a stack in a game state

#pragma once
#include <vector>
#include "Object.h"
class StackBlocks
{
public:
	std::vector<std::string> objects;
	StackBlocks(std::vector<std::string> objects);
	StackBlocks();
	~StackBlocks();
	bool operator==(const StackBlocks& other);
};

