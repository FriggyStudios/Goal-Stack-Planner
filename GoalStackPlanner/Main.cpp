#include <string>
#include <iostream>
#include "Handler.h"

int main()
{
	Game game = Game();
	Handler handle = Handler(game);

	while (!handle.Satisfy());
	std::cout << "Finished";
	int x;
	std::cin >> x;

	return 0;
}