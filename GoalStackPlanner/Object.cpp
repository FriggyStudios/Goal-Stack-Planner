#include "Object.h"


Object::Object()
{
	above = NULL;
	below = NULL;
	inHand = NULL;
}
Object::Object(std::string name) : Object()
{
	this->name = name;
}

Object::~Object()
{
}
