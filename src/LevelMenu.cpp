#include "../include/LevelMenu.hpp"
#include "../include/BackgroundSprite.hpp"
#include "../include/auxiliary/constants.hpp"
#include <memory>
#include <iostream>
#include <sstream>

LevelMenu::LevelMenu(sf::RenderWindow& window, std::shared_ptr<GameData> gameData)
	: Mode(window),
	textures_(),
	gameData_(gameData)
{
	loadResources();
	createScene();
}


void LevelMenu::loadResources()
{
	textures_.load(Textures::ID::LevelMenuBackground, "./include/images/GreenTile.png");
	buttonShapes_.load(Buttons::ID::HomeButton);
	buttonShapes_.load(Buttons::ID::Level1Button);
	buttonShapes_.load(Buttons::ID::Level2Button);
	buttonShapes_.load(Buttons::ID::Level3Button);
	buttonShapes_.load(Buttons::ID::Level4Button);
	buttonShapes_.load(Buttons::ID::Level5Button);
	buttonShapes_.load(Buttons::ID::Level6Button);
	buttonShapes_.load(Buttons::ID::Level7Button);
	buttonShapes_.load(Buttons::ID::Level8Button);
	buttonShapes_.load(Buttons::ID::Level9Button);
	buttonShapes_.load(Buttons::ID::StartButton);
}


void LevelMenu::createScene()
{
	initializePointers(static_cast<std::size_t>(Layers::TotalCount));
	addBackground();
	addButtons();
}


void LevelMenu::addBackground()
{
	// Set the background for the menu
	sf::Texture& backgroundTexture = textures_.get(Textures::ID::LevelMenuBackground);
	backgroundTexture.setRepeated(true);

	sf::IntRect bounds(windowBounds_);

	auto background = std::make_unique<BackgroundSprite>(BackgroundSprite{backgroundTexture, bounds});
	background->setPosition(0.f, 0.f);
	layers_[static_cast<std::size_t>(Layers::Background)]->addChild(std::move(background));
}


void LevelMenu::addButtons()
{
	// Configure the buttons
	// NOTE: Start button is the one that leads the user to the first level (subject to change)
	auto startButton = std::make_unique<Button>("New Game", fonts_, Fonts::ID::SourceCodePro, buttonShapes_, Buttons::ID::StartButton);
	startButton->setPosition(WindowWidth / 2.f, WindowHeight / 6.f);
	buttons_.push_back(startButton.get());
	layers_[static_cast<std::size_t>(Layers::Buttons)]->addChild(std::move(startButton));

	for (int level = 1; level <= MaxLevel; level++)
	{
		std::stringstream ss;
		ss << "Level " << level;
		Buttons::ID levelButtonId = static_cast<Buttons::ID>(static_cast<int>(Buttons::ID::Level1Button) + level - 1);
		auto levelButton = std::make_unique<Button>(ss.str(), fonts_, Fonts::ID::SourceCodePro, buttonShapes_, levelButtonId);
		auto pos = buttons_[buttons_.size() - 1]->getButton().getPosition();
		levelButton->setPosition(pos.x, pos.y + levelButton->getButton().getSize().y + 25.f);
		buttons_.push_back(levelButton.get());
		layers_[static_cast<std::size_t>(Layers::Buttons)]->addChild(std::move(levelButton));
	}

	auto homeButton = std::make_unique<Button>("Main Menu", fonts_, Fonts::ID::SourceCodePro, buttonShapes_, Buttons::ID::HomeButton);
	// NOTE: Position is based on the previous button
	auto pos = buttons_[buttons_.size() - 1]->getButton().getPosition();
	homeButton->setPosition(pos.x, pos.y + homeButton->getButton().getSize().y + 25.f);
	buttons_.push_back(homeButton.get());
	layers_[static_cast<std::size_t>(Layers::Buttons)]->addChild(std::move(homeButton));
}

void LevelMenu::update(sf::Time deltaTime)
{
}
