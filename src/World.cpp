#include "../include/World.hpp"
#include "../include/MainMenu.hpp"
#include "../include/Level.hpp"
#include "../include/LevelMenu.hpp"
#include <iostream>

World::World(sf::RenderWindow& window)
	: window_(window),
	modeType_(Type::MainMenu),
	gameBounds_(0.f, 0.f, window.getSize().x, window.getSize().y),
	mode_(std::make_unique<MainMenu>(window, std::make_shared<GameData>())),
	gameData_(std::make_shared<GameData>()),
    running(true),
    message_(std::make_unique<Message>("This level is locked"))
{
}


void World::update(sf::Time deltaTime)
{
	mode_->update(deltaTime);
}


void World::operate()
{
	// Picks the current mode from the modes array
	window_.draw(*mode_);

    if (message_->isActive())
    {
        message_->drawSelf(window_, sf::RenderStates());
    }
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
		case Type::NewGame:
			/* gameData_ = std::make_shared<GameData>(); */
			mode_.reset(new Level(window_, gameData_));
			break;
		case Type::CheatMode:
			/* gameData_ = std::make_shared<GameData>(); */
			gameData_->addCredits(1000000 - gameData_->getCredits());
			mode_.reset(new Level(window_, gameData_));
			break;
		case Type::Level1:
		case Type::Level2:
		case Type::Level3:
		case Type::Level4:
		case Type::Level5:
		case Type::Level6:
		case Type::Level7:
		case Type::Level8:
		case Type::Level9:
			gameData_->setLevel(static_cast<int>(newMode) - static_cast<int>(Type::Level1) + 1);
			mode_.reset(new Level(window_, gameData_));
			break;
		case Type::MainMenu:
			mode_.reset(new MainMenu(window_, gameData_));
			break;
		case Type::LevelMenu:
			mode_.reset(new LevelMenu(window_, gameData_));
			break;
        case Type::Quit:
            running = false;
            break;
	}
}


void World::handleUserInput(sf::Vector2i mousePos)
{
    ModeState newMode = mode_->handleInput(mousePos);

    switch (newMode.action)
    {
        case Action::ModeChange:
            changeMode(newMode.type);
            break;
        case Action::Idle:
            break;
        case Action::ShowMessage:
            {
                std::cout << "1" << std::endl;
                message_->setActive(true);
                std::cout << "2" << std::endl;
                break;
            }
        case Action::CloseMessage:
            if (message_->isActive())
            {
                message_->setActive(false);
            }
            break;
    }

    std::cout << "3" << std::endl;
}
