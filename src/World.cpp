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
    message_(nullptr)
{
    // Necessary for message to function properly
    mode_->getButtonShapes().load(Buttons::ID::CloseMessage);
    message_ = std::make_unique<Message>("This level is locked", mode_->getFonts(), mode_->getButtonShapes());
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
        window_.draw(*message_);
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

    if (newMode.modeChange)
    {
        changeMode(newMode.type);
    }
    /* else if (newMode.message.length() > 0) */
    /* { */
    /*     message_->changeMessage(newMode.message); */

    /*     if (!message_->isActive()) */
    /*     { */
    /*         message_->toggleActivation(); */
    /*     } */
    /* } */
    /* else if (newMode.closeCall && message_->isActive()) */
    /* { */
    /*     message_->toggleActivation(); */
    /* } */
}
