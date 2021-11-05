#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <memory>
#include "Mode.hpp"
#include "MainMenu.hpp"

class World
{
	public:
		enum class Type
		{
			MainMenu,
			Level,
			TotalTypes
		};

	public:
		World(sf::RenderWindow& window);

		void operate();
		void changeMode(Type newType);
		void handleUserInput();

		Type getMode() const { return modeType_; }

	private:
		sf::RenderWindow& window_;
		Type modeType_;
		sf::FloatRect gameBounds_;

		// The current mode of the game
		std::unique_ptr<Mode> mode_;
};

#endif
