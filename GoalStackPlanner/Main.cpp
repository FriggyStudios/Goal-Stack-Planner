#include <string>
#include <iostream>
#include "Handler.h"

int main()
{
	Game game = Game();
	Handler handle = Handler(game);

	while (!handle.Satisfy());

	return 0;
}