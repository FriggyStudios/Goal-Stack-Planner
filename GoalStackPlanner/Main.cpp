#include <string>
#include <iostream>
#include "Handler.h"
#include <ctime>

std::vector<StackBlocks> RandomState(unsigned int blocksNum);

int main()
{
	srand((unsigned)time(0));
	unsigned int blocksNum = 3;
	//Multiple block worlds
	for (int i = 0; i < 10;i++)
	{
		//init game and solution finder
		std::cout << "Start State" << '\n';
		std::vector<StackBlocks> startState = RandomState(blocksNum);
		std::cout << "Goal State" << '\n';
		std::vector<StackBlocks> goalState = RandomState(blocksNum);

		Game game = Game(startState, goalState);
		Handler handle = Handler(game);

		//measure solution time
		float begin = clock();
		//find solution
		while (!handle.Satisfy());
		float time = clock() - begin;
		//print time
		std::cout << "\nTook " << time / CLOCKS_PER_SEC << "s\n\n";
	}

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
		for (int k = 0; k < stackBlocksNum; k++)
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