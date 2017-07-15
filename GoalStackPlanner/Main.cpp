//Executes handler on randomly generated Game game state of number of blocks blocksNum
//Outputs each game initial and goal state
//Outputs solution to game
//Outputs time to solve each game and average time for blocksNum

#include <string>
#include <iostream>
#include "Handler.h"
#include <ctime>

//Returns a random game state of number of blocks blocksNum
std::vector<StackBlocks> RandomState(unsigned int blocksNum);

int main()
{
	srand((unsigned)time(0));
	float totalTime = 0;
	unsigned int blocksNum = 3;
	unsigned int numIterations = 10;
	//Multiple block worlds
	for (unsigned int i = 0; i < numIterations;i++)
	{
		std::vector<StackBlocks> startState;
		std::vector<StackBlocks> goalState;
		bool statesSame = true;
		while (statesSame)
		{
			//init game and solution finder
			std::cout << "Start State" << '\n';
			startState = RandomState(blocksNum);
			std::cout << "Goal State" << '\n';
			goalState = RandomState(blocksNum);
			if (startState.size() != goalState.size())
			{
				statesSame = false;
			}
			else
			{
				for (int i = 0; i < startState.size(); i++)
				{
					if (!(startState[i] == goalState[i]))
					{
						statesSame = false;
						break;
					}
				}
			}
			if (statesSame)
			{
				std::cout << "Same states made, redoing states\n\n";
			}
		}

		Game game = Game(startState, goalState);
		Handler handle = Handler(game);

		//measure solution time
		float begin = (float)clock();
		//find solution
		while (!handle.Satisfy());
		float time = clock() - begin;
		totalTime += time / CLOCKS_PER_SEC;
		//print time
		std::cout << "\nTook " << time / CLOCKS_PER_SEC << "s\n\n";
	}
	//print time
	std::cout << "\nAverage time took " << totalTime / numIterations << "s\n\n";
	int x;
	std::cin >> x;
	return 0;
}

std::vector<StackBlocks> RandomState(unsigned int blocksNum)
{
	int blockName = 1;
	//start state
	unsigned int blocksLeftNum = blocksNum;
	std::vector<StackBlocks> state = std::vector<StackBlocks>();
	while (blocksLeftNum > 0)
	{
		std::vector<std::string> stateObjects = std::vector<std::string>();
		StackBlocks stack;
		unsigned int stackBlocksNum = (rand() % blocksLeftNum) + 1;
		blocksLeftNum -= stackBlocksNum;
		for (unsigned int k = 0; k < stackBlocksNum; k++)
		{
			std::cout << blockName << '\n';
			stateObjects.push_back(std::to_string(blockName++));
		}
		std::cout << '\n';
		stack = StackBlocks(stateObjects);
		state.push_back(stack);
	}
	std::cout << '\n';
	return state;
}