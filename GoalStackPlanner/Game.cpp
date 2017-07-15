#include "Game.h"
#include <iostream>

Game::Game()
{
	goalState = std::vector<StackBlocks>();
	objects = std::vector<Object*>();
}

Game::Game(std::vector<StackBlocks> startState, std::vector<StackBlocks> goalState)
{
	this->goalState = goalState;
	objects = std::vector<Object*>();
	for (StackBlocks blocks : startState)
	{
		std::vector<Object*> objectsLocal = std::vector<Object*>();
		for (std::string name : blocks.objects)
		{
			objectsLocal.push_back(new Block(name));
		}
		for (int i = 0; i < objectsLocal.size(); i++)
		{
			if (i != blocks.objects.size() - 1)
			{
				objectsLocal[i]->below = objectsLocal[i + 1];
			}
			if (i != 0)
			{
				objectsLocal[i]->above = objectsLocal[i - 1];
			}

			objects.push_back(objectsLocal[i]);
		}
	}
	objects.push_back(new Hand());
	objects.push_back(new Table());
	operators = std::vector<Operator*>();
	operators.push_back(new PickUp());
	operators.push_back(new PutDown());
}

Game::Game(const Game &game)
{
	goalState = game.goalState;
	operators = std::vector<Operator*>();
	operators.push_back(new PickUp());
	operators.push_back(new PutDown());

	objects = std::vector<Object*>();
	for (unsigned int i = 0; i < game.objects.size() - 2; i++)
	{
		objects.push_back(new Block(game.objects[i]->name));
	}
	objects.push_back(new Hand());
	objects.push_back(new Table());
	for (unsigned int i = 0; i < game.objects.size(); i++)
	{
		for (unsigned int j = 0; j < game.objects.size(); j++)
		{
			if (game.objects[i]->above != nullptr)
			{
				if (game.objects[i]->above == game.objects[j])
				{
					objects[i]->above = objects[j];
				}
			}
			if (game.objects[i]->below != nullptr)
			{
				if (game.objects[i]->below == game.objects[j])
				{
					objects[i]->below = objects[j];
				}
			}
			if (game.objects[i]->inHand != nullptr)
			{
				if (game.objects[i]->inHand == game.objects[j])
				{
					objects[i]->inHand = objects[j];
				}
			}
		}
	}
}

Game::~Game()
{
	for (Object* obj : objects)
	{
		delete obj;
	}
	for (Operator* obj : operators)
	{
		delete obj;
	}
}

Game& Game::operator=(const Game& game)
{
	if (this == &game)
		return (*this); // Taking care for self-assignment

	for (Object* obj : objects)
	{
		delete obj;
	}
	for (Operator* op : operators)
	{
		delete op;
	}

	goalState = game.goalState;
	operators = std::vector<Operator*>();
	operators.push_back(new PickUp());
	operators.push_back(new PutDown());

	objects = std::vector<Object*>();
	for (unsigned i = 0; i < game.objects.size() - 2; i++)
	{
		objects.push_back(new Block(game.objects[i]->name));
	}
	objects.push_back(new Hand());
	objects.push_back(new Table());
	for (unsigned i = 0; i < game.objects.size() - 2; i++)
	{
		for (unsigned j = 0; j < game.objects.size(); j++)
		{
			if (game.objects[i]->above != nullptr)
			{
				if (game.objects[i]->above == game.objects[j])
				{
					objects[i]->above = objects[j];
				}
			}
			if (game.objects[i]->below != nullptr)
			{
				if (game.objects[i]->below == game.objects[j])
				{
					objects[i]->below = objects[j];
				}
			}
			if (game.objects[i]->inHand != nullptr)
			{
				if (game.objects[i]->inHand == game.objects[j])
				{
					objects[i]->inHand = objects[j];
				}
			}
		}
	}
	return (*this);
}

bool Game::operator==(const Game& game)
{
	if (objects.size() != game.objects.size())
	{
		return false;
	}
	for (unsigned i = 0; i < game.objects.size() - 2; i++)
	{
		for (unsigned j = 0; j < game.objects.size(); j++)
		{
			if (game.objects[i]->above != nullptr)
			{
				if (game.objects[i]->above == game.objects[j])
				{
					if (objects[i]->above != objects[j])
					{
						return false;
					}
				}
			}
			else if (objects[i]->above != nullptr)
			{
				return false;
			}
			if (game.objects[i]->below != nullptr)
			{
				if (game.objects[i]->below == game.objects[j])
				{
					if (objects[i]->below != objects[j])
					{
						return false;
					}
				}
			}
			else if (objects[i]->below != nullptr)
			{
				return false;
			}
			if (game.objects[i]->inHand != nullptr)
			{
				if (game.objects[i]->inHand == game.objects[j])
				{
					if (objects[i]->inHand != objects[j])
					{
						return false;
					}
				}
			}
			else if (objects[i]->inHand != nullptr)
			{
				return false;
			}
		}
	}
	return true;
}

std::vector<bool> Game::conditionchecker()
{
	std::vector<bool> conditionsSatisfied = std::vector<bool>();

	for (int i = 0; i < goalState.size(); i++)
	{
		for (int j = 0; j < goalState[i].objects.size(); j++)
		{
			std::string blockName = goalState[i].objects[j];
			std::string blockNameBelow;
			std::string blockNameAbove;
			Object* block;
			Object* blockBelow;
			Object* blockAbove;
			for (Object* object : objects)
			{
				if (object->name == blockName)
				{
					block = object;
					break;
				}
			}
			if (block == NULL)
			{
				std::cerr << "Game Erorr: no matching block name";
			}
			if (j != goalState[i].objects.size() - 1)
			{
				blockNameBelow = goalState[i].objects[j + 1];
				for (Object* object : objects)
				{
					if (object->name == blockNameBelow)
					{
						blockBelow = object;
						break;
					}
				}
				if (blockBelow == NULL)
				{
					std::cerr << "Game Erorr: no matching block name";
				}
				if (block->below != blockBelow)
				{
					conditionsSatisfied.push_back(false);
				}
				else
				{
					conditionsSatisfied.push_back(true);
				}
			}
			else
			{
				if (block->below != NULL)
				{
					conditionsSatisfied.push_back(false);
				}
				else
				{
					conditionsSatisfied.push_back(true);
				}
			}
			if (j != 0)
			{
				blockNameAbove = goalState[i].objects[j - 1];
				for (Object* object : objects)
				{
					if (object->name == blockNameAbove)
					{
						blockAbove = object;
						break;
					}
				}
				if (blockAbove == NULL)
				{
					std::cerr << "Game Erorr: no matching block name";
				}
				if (block->above != blockAbove)
				{
					conditionsSatisfied.push_back(false);
				}
				else
				{
					conditionsSatisfied.push_back(true);
				}
			}
			else
			{
				if (block->above != NULL)
				{
					conditionsSatisfied.push_back(false);
				}
				else
				{
					conditionsSatisfied.push_back(true);
				}
			}
			if (block->inHand != NULL)
			{
				conditionsSatisfied.push_back(false);
			}
			else
			{
				conditionsSatisfied.push_back(true);
			}
		}
	}
	return conditionsSatisfied;
}

bool Game::satisfied()
{
	std::vector<bool> conditionsSatisfied = conditionchecker();

	for (bool conditionSatisfied : conditionsSatisfied)
	{
		if (!conditionSatisfied)
		{
			return false;
		}
	}
	return true;
}

bool Game::EqualGame(const std::vector<Game>& gameStates)
{
	for (Game gameState : gameStates)
	{
		if ((*this) == gameState)
		{
			return true;
		}
	}
	return false;
}
