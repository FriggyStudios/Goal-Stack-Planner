#include <string>
#include <iostream>
#include "Handler.h"
#include <ctime>

int main()
{
	for (int i = 0; i < 2;i++)
	{
		Game game = Game();
		Handler handle = Handler(game);

		float begin = clock();
		while (!handle.Satisfy());
		float time = clock() - begin;
		std::cout << "\nTook " << time / CLOCKS_PER_SEC << "s\n\n";
	}

	int x;
	std::cin >> x;
	return 0;
}