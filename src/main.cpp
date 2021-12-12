#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/game.hpp"


int main()
{
	try
	{
		Game game;
		game.run();
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

};
