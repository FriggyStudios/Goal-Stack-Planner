#include "Game.h"


Game::Game()
{
	Hand hand = Hand();
	Table table = Table();
	Block A = Block();
	Block B = Block();
	Block C = Block();

	B.above = &A;
	A.below = &B;
	
	objects = std::vector<Object>();
	objects.push_back(A);
	objects.push_back(B);
	objects.push_back(C);
	objects.push_back(hand);
	objects.push_back(table);

	operators = std::vector<Operator>();
	operators.push_back(PickUp());
	operators.push_back(PutDown());
}

Game::Game(Game &game)
{
	operators = game.operators;

	objects = std::vector<Object>();
	for (unsigned i = 0; i < game.objects.size()-2; i++)
	{
		objects.push_back(Block());
	}
	objects.push_back(Hand());
	objects.push_back(Table());
	for (unsigned i = 0; i < game.objects.size() - 2; i++)
	{
		if (game.objects[i].above != nullptr)
		{
			for (unsigned j = 0; j < game.objects.size() - 2; j++)
			{
				if (game.objects[i].above == &game.objects[j])
				{
					objects[i].above = &objects[j];
					break;
				}
			}
		}
		if (game.objects[i].below != nullptr)
		{
			for (unsigned j = 0; j < game.objects.size() - 2; j++)
			{
				if (game.objects[i].below == &game.objects[j])
				{
					objects[i].below = &objects[j];
					break;
				}
			}
		}
	}

}

Game::~Game()
{
}

std::vector<bool> Game::conditionchecker()
{
	std::vector<bool> conditionsSatisfied = std::vector<bool>();
	conditionsSatisfied.push_back(condition1());
	conditionsSatisfied.push_back(condition2());
	conditionsSatisfied.push_back(condition3());

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
	if (objects[1].below == nullptr &&
		objects[1].above == &objects[2])
	{
		return true;
	}
	return false;
}
bool Game::condition2()
{
	if (objects[2].below == &objects[1] &&
		objects[2].above == nullptr)
	{
		return true;
	}
	return false;
}
bool Game::condition3()
{
	if (objects[0].below == nullptr &&
		objects[0].above == nullptr)
	{
		return true;
	}
	return false;
}
