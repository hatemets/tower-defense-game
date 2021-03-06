#include "../include/World.hpp"
#include "../include/MainMenu.hpp"
#include "../include/Level.hpp"
#include "../include/LevelMenu.hpp"
#include <iostream>


bool isLevel(Type type)
{
    switch (type)
    {
        case Type::Level1:
        case Type::Level2:
        case Type::Level3:
        case Type::Level4:
        case Type::Level5:
        case Type::Level6:
            return true;
        default:
            return false;
    }
}


World::World(sf::RenderWindow& window)
	: window_(window),
	modeType_(Type::MainMenu),
	gameBounds_(0.f, 0.f, window.getSize().x, window.getSize().y),
	mode_(std::make_unique<MainMenu>(window, std::make_shared<GameData>())),
	gameData_(std::make_shared<GameData>()),
    running(true),
    message_(std::make_unique<Message>("This level is locked")),
    backgroundMusic_()
{
    playMusic();
}


void World::playMusic()
{
    backgroundMusic_.openFromFile("./include/audio/Miami_Sky.wav");
    backgroundMusic_.setLoop(true);
    startMusic();
}


void World::stopMusic()
{
    backgroundMusic_.stop();
}


void World::startMusic()
{
    backgroundMusic_.play();
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
			mode_.reset(new Level(window_, gameData_));
			break;
		case Type::CheatMode:
			mode_.reset(new Level(window_, gameData_));
			break;
		case Type::Level1:
		case Type::Level2:
		case Type::Level3:
		case Type::Level4:
		case Type::Level5:
		case Type::Level6:
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

    if (isLevel(newMode))
    {
        backgroundMusic_.stop();
    }
    else if (backgroundMusic_.getStatus() == sf::Music::Status::Stopped)
    {
        playMusic();
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
            message_->setActive(true);
            break;
    }

    if (newMode.action != Action::ShowMessage)
    {
        message_->setActive(false);

        if (gameData_->isGameOver())
        {
            // Redirect the user to main menu
            changeMode(Modes::Type::MainMenu);
            gameData_->setGameOver(false);
        }
    }
}


void World::activateCheatMode()
{
    mode_->activateCheatMode();
}
