#include "StackBlocks.h"



StackBlocks::StackBlocks(std::vector<std::string> objects)
{
	this->objects = objects;
}

StackBlocks::StackBlocks()
{
	this->objects = std::vector<std::string>();
}

StackBlocks::~StackBlocks()
{
}
