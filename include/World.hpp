#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <memory>
#include "Mode.hpp"
#include "MainMenu.hpp"
#include "auxiliary/ModeIdentifiers.hpp"
#include "StateChange.hpp"

using namespace Modes;

class World
{
	public:
		World(sf::RenderWindow& window);

		void operate();
		void changeMode(Type newType);
		void handleUserInput(sf::Vector2i mousePos);

		Type getMode() const { return modeType_; }

	private:
		sf::RenderWindow& window_;
		Type modeType_;
		sf::FloatRect gameBounds_;

		// The current mode of the game
		std::unique_ptr<Mode> mode_;
};

#endif
