#include <string>
#include <iostream>
#include "Handler.h"
#include <ctime>

int main()
{
	for (int i = 0; i < 1;i++)
	{
		//start state
		std::vector<std::string> startObjects1 = std::vector<std::string>();
		startObjects1.push_back("D");
		startObjects1.push_back("C");
		startObjects1.push_back("B");
		startObjects1.push_back("A");
		StackBlocks startStack1 = StackBlocks(startObjects1);
		std::vector<StackBlocks> startState = std::vector<StackBlocks>();
		startState.push_back(startStack1);

		//goal state
		std::vector<std::string> goalObjects1 = std::vector<std::string>();
		goalObjects1.push_back("A");
		goalObjects1.push_back("B");
		StackBlocks goalsStack1 = StackBlocks(goalObjects1);
		std::vector<std::string> goalObjects2 = std::vector<std::string>();
		goalObjects2.push_back("C");
		goalObjects2.push_back("D");
		StackBlocks goalsStack2 = StackBlocks(goalObjects2);
		std::vector<StackBlocks> goalState = std::vector<StackBlocks>();
		goalState.push_back(goalsStack1);
		goalState.push_back(goalsStack2);

		//init game and solution finder
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