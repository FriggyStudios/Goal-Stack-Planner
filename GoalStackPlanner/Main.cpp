#include <string>
#include <iostream>
#include "Handler.h"
#include <ctime>

int main()
{
	Game game = Game();
	Handler handle = Handler(game);

	float begin = clock();
	while (!handle.Satisfy());
	float time = clock() - begin;
	std::cout << "\nTook " << time/ CLOCKS_PER_SEC << "s";
	int x;
	std::cin >> x;

	return 0;
}