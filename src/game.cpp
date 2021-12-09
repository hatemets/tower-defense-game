#include "../include/game.hpp"
#include <SFML/System/Time.hpp>


Game::Game()
	: window_(sf::VideoMode(WindowWidth, WindowHeight), "Tower Defense Game"),
	world_(window_)
{
}

void Game::run()
{
	// Counts time between frames
	sf::Clock clock;

	// Initialize time to zero
	sf::Time elapsedTime = sf::Time::Zero;

	while (window_.isOpen())
	{
		elapsedTime += clock.restart();

		// If elapsed time is larger, cut it down by the amount of time passed
		// so far (achieves a fixed timestep)
		while (elapsedTime > TimePerFrame)
		{
			elapsedTime -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}

		render();
	}
}

void Game::processEvents()
{
	sf::Event event;

	// Listen for events
	while (window_.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				window_.close();
				break;

            case sf::Event::MouseButtonReleased:
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        world_.handleUserInput(sf::Mouse::getPosition(window_));
                    }

                    // Listen for exit call
                    if (!world_.isRunning())
                    {
                        window_.close();
                    }

                    break;
                }
            case sf::Event::KeyPressed:
                {
                    // Enter cheat mode with Q
                    if (event.key.code == sf::Keyboard::Q)
                    {
                        // money hack
                        world_.activateCheatMode();
                    }
                }
        }
    }
}

// Update game with fixed timesteps
void Game::update(sf::Time deltaTime)
{
	world_.update(deltaTime);
}

void Game::render()
{
	window_.clear(sf::Color::Black);

	world_.operate();

	window_.display();
}
