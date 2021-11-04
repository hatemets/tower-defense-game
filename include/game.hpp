#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "auxiliary/constants.hpp"
#include "World.hpp"

class Game
{
	public:
		Game();
		void run();

		// Frames per second is equal to the inverese of TimePerFrame
		sf::Time TimePerFrame = sf::seconds(1.f / FramesPerSecond);

	private:
		void processEvents();
		void update(sf::Time deltaTime);
		void render();
		void handleUserInput();

	private:
		sf::RenderWindow window_;
		World world_;
};

#endif
