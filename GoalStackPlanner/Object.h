#pragma once
class Object
{
public:
	Object* above;
	Object* below;
	Object* inHand;
	bool hand;
	bool table;
public:
	Object();
	~Object();
};

