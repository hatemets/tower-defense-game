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
			elapsedTime -= clock.restart();
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
	// TODO: add an event listener for mouseclicks
	while (window_.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				window_.close();
				break;
				// NOTE: For testing purposes only
			case sf::Event::KeyPressed:
				{
					if (world_.getMode() == World::Type::Level)
					{
						world_.changeMode(World::Type::MainMenu);
					}
					else
					{
						world_.changeMode(World::Type::Level);
					}
					break;
				}
		}
	}
}

// Update game with fixed timesteps
void Game::update(sf::Time deltaTime)
{
}

void Game::render()
{
	window_.clear();

	world_.operate();

	window_.display();
}
