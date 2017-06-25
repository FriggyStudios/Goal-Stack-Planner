#include "Block.h"

Block::Block(std::string name) : Object(name)
{
	hand = false;
	table = false;
}

Block::~Block()
{
}

