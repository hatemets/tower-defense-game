#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <memory>
#include "Mode.hpp"
#include "MainMenu.hpp"
#include "GameData.hpp"
#include "Message.hpp"
#include "auxiliary/ModeIdentifiers.hpp"

using namespace Modes;

class World
{
	public:
		World(sf::RenderWindow& window);

		void update(sf::Time deltaTime);
		void changeMode(Type newType);
		void operate();
		void handleUserInput(sf::Vector2i mousePos);
        bool isRunning() { return running; }
		Type getMode() const { return modeType_; }
        void playMusic();
        void stopMusic();
        void startMusic();

        // TODO: Remove for production
        void activateCheatMode();

	private:
		sf::RenderWindow& window_;
		Type modeType_;
		sf::FloatRect gameBounds_;

		// The current mode of the game
		std::unique_ptr<Mode> mode_;

		std::shared_ptr<GameData> gameData_;

        // Whether the game is still running
        bool running;

        std::unique_ptr<Message> message_;

        sf::Music backgroundMusic_;
};

#endif
