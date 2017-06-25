#include "Game.h"


Game::Game()
{
	Hand* hand = new Hand();
	Table* table = new Table();
	Block* A = new Block("A");
	Block* B = new Block("B");
	Block* C = new Block("C");
	Block* D = new Block("D");

	B->above = A;
	A->below = B;
	A->above = D;
	D->below = A;
	
	objects = std::vector<Object*>();
	objects.push_back(A);
	objects.push_back(B);
	objects.push_back(C);
	objects.push_back(D);
	objects.push_back(hand);
	objects.push_back(table);

	operators = std::vector<Operator*>();
	operators.push_back(new PickUp());
	operators.push_back(new PutDown());
}

Game::Game(Game &game)
{

	operators = std::vector<Operator*>();
	operators.push_back(new PickUp());
	operators.push_back(new PutDown());

	objects = std::vector<Object*>();
	for (unsigned i = 0; i < game.objects.size()-2; i++)
	{
		objects.push_back(new Block(game.objects[i]->name));
	}
	objects.push_back(new Hand());
	objects.push_back(new Table());
	for (unsigned i = 0; i < game.objects.size() - 2; i++)
	{
		if (game.objects[i]->above != nullptr)
		{
			for (unsigned j = 0; j < game.objects.size() - 2; j++)
			{
				if (game.objects[i]->above == game.objects[j])
				{
					objects[i]->above = objects[j];
					break;
				}
			}
		}
		if (game.objects[i]->below != nullptr)
		{
			for (unsigned j = 0; j < game.objects.size() - 2; j++)
			{
				if (game.objects[i]->below == game.objects[j])
				{
					objects[i]->below = objects[j];
					break;
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
		if (game.objects[i]->above != nullptr)
		{
			for (unsigned j = 0; j < game.objects.size() - 2; j++)
			{
				if (game.objects[i]->above == game.objects[j])
				{
					objects[i]->above = objects[j];
					break;
				}
			}
		}
		if (game.objects[i]->below != nullptr)
		{
			for (unsigned j = 0; j < game.objects.size() - 2; j++)
			{
				if (game.objects[i]->below == game.objects[j])
				{
					objects[i]->below = objects[j];
					break;
				}
			}
		}
	}

	return (*this);
}

std::vector<bool> Game::conditionchecker()
{
	std::vector<bool> conditionsSatisfied = std::vector<bool>();
	conditionsSatisfied.push_back(condition1());
	conditionsSatisfied.push_back(condition2());
	conditionsSatisfied.push_back(condition3());
	conditionsSatisfied.push_back(condition4());

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

bool Game::condition1()
{
	if (objects[1]->below == NULL &&
		objects[1]->above == objects[2] &&
		objects[1]->inHand == NULL)
	{
		return true;
	}
	return false;
}
bool Game::condition2()
{
	if (objects[2]->below == objects[1] &&
		objects[2]->above == NULL &&
		objects[2]->inHand == NULL)
	{
		return true;
	}
	return false;
}
bool Game::condition3()
{
	if (objects[0]->below == NULL &&
		objects[0]->above == NULL &&
		objects[0]->inHand == NULL)
	{
		return true;
	}
	return false;
}
bool Game::condition4()
{
	if (objects[3]->below == NULL &&
		objects[3]->above == NULL &&
		objects[3]->inHand == NULL)
	{
		return true;
	}
	return false;
}
