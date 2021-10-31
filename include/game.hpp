#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "constants.hpp"

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
		// TODO:
		// Main menu
		// (Level Menu)
		// Levels
};

#endif
