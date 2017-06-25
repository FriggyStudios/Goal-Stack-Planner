#pragma once
#include "Object.h"
#include "Hand.h"
#include <string>
class Block :
	public Object
{
public:
	std::string name;
public:
	Block(std::string name);
	~Block();
};

