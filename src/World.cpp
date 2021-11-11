#include "../include/World.hpp"
#include "../include/MainMenu.hpp"
#include "../include/Level.hpp"
#include "../include/LevelMenu.hpp"
#include <iostream>

World::World(sf::RenderWindow& window)
	: window_(window),
	modeType_(Type::MainMenu),
	gameBounds_(0.f, 0.f, window.getSize().x, window.getSize().y),
	mode_(std::make_unique<MainMenu>(window))
{
}

void World::operate()
{
	// Picks the current mode from the modes array
	window_.draw(*mode_);
}

void World::changeMode(Type newMode)
{
	// Should never happen
	if (modeType_ == newMode)
	{
		throw std::runtime_error("World::changeMode: newMode is the same as currentMode");
	}

	modeType_ = newMode;

	switch (newMode)
	{
		case Type::Level:
			mode_.reset(new Level(window_));
			break;
		case Type::MainMenu:
			mode_.reset(new MainMenu(window_));
			break;
		case Type::LevelMenu:
			mode_.reset(new LevelMenu(window_));
			break;
	}
}

void World::handleUserInput(sf::Vector2i mousePos)
{
	ModeState newMode = mode_->handleInput(mousePos);

	if (newMode.modeChange)
	{
		changeMode(newMode.type);
	}
}
