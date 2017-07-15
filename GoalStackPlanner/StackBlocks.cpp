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

bool StackBlocks::operator==(const StackBlocks& other)
{
	if (objects.size() != other.objects.size())
	{
		return false;
	}
	for (int i = 0; i < objects.size(); i++)
	{
		if (!(objects[i] == other.objects[i]))
		{
			return false;
		}
	}
	return true;
}