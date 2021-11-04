#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <memory>
#include "auxiliary/ModeIdentifiers.hpp"
#include "Mode.hpp"

class World
{
	public:
		World(sf::RenderWindow& window);
		void operate();
		void changeMode(Modes::Type newType);

	private:
		sf::RenderWindow& window_;
		Modes::Type currentMode_;
		sf::FloatRect gameBounds_;

		// A vector containing all the possible modes in the game
		// NOTE: The container type is subject to change. Array is preferred
		// for its static size
		std::vector<std::unique_ptr<Mode>> modes_;
};

#endif
