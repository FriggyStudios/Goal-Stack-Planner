//Object parent class
//Stores pointers to other objects to signify the object's state the other objects

#pragma once
#include <string>
class Object
{
public:
	Object* above;
	Object* below;
	Object* inHand;
	std::string name;
	bool hand;
	bool table;
public:
	Object();
	Object(std::string name);
	~Object();
};

