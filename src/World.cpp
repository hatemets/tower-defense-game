#include "../include/World.hpp"
#include "../include/auxiliary/constants.hpp"
#include "../include/MainMenu.hpp"

World::World(sf::RenderWindow& window)
	: window_(window),
	currentMode_(Modes::Type::Menu),
	// TODO: Remove the constants
	gameBounds_(0.f, 0.f, WindowWidth, WindowHeight),
	modes_()
{
	auto mainMenu = std::make_unique<MainMenu>(MainMenu{window});
	modes_.push_back(std::move(mainMenu));
}

void World::operate()
{
	window_.draw(*modes_[0]);
}

void World::changeMode(Modes::Type newType)
{
	// TODO:
	// Instantiate the new mode

	currentMode_ = newType;
}
