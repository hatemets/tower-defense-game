#include "../include/World.hpp"
#include "../include/MainMenu.hpp"

World::World(sf::RenderWindow& window)
	: window_(window),
	currentMode_(Modes::Type::Menu),
	gameBounds_(0.f, 0.f, window.getSize().x, window.getSize().y),
	modes_()
{
	auto mainMenu = std::make_unique<MainMenu>(MainMenu{window});
	modes_.push_back(std::move(mainMenu));
}

void World::operate()
{
	// TODO: remove hardcoded index
	window_.draw(*modes_[0].get());
}

void World::changeMode(Modes::Type newType)
{
	// TODO:
	// Instantiate the new mode

	currentMode_ = newType;
}
