#include "../include/LevelMenu.hpp"
#include "../include/BackgroundSprite.hpp"
#include "../include/auxiliary/constants.hpp"
#include <memory>
#include <iostream>

LevelMenu::LevelMenu(sf::RenderWindow& window)
	: Mode(window),
	textures_()
{
	loadResources();
	createScene();
}


void LevelMenu::loadResources()
{
	textures_.load(Textures::ID::LevelMenuBackground, "./include/images/GreenTile.png");
	buttonShapes_.load(Buttons::ID::HomeButton);
	buttonShapes_.load(Buttons::ID::StartButton);
}


void LevelMenu::createScene()
{
	for (std::size_t i = 0; i < static_cast<std::size_t>(Layers::TotalCount); ++i)
	{
		auto layerNode = std::make_unique<Node>();

		layers_.push_back(layerNode.get());

		nodeTree_.addChild(std::move(layerNode));
	}


	// Set the background for the menu
	sf::Texture& backgroundTexture = textures_.get(Textures::ID::LevelMenuBackground);
	backgroundTexture.setRepeated(true);

	sf::IntRect bounds(windowBounds_);

	auto background = std::make_unique<BackgroundSprite>(BackgroundSprite{backgroundTexture, bounds});
	background->setPosition(0.f, 0.f);
	layers_[static_cast<std::size_t>(Layers::Background)]->addChild(std::move(background));


	// Configure the buttons
	// NOTE: Start button is the one that leads the user to the first level (subject to change)
	auto startButton = std::make_unique<Button>("Level 1", fonts_, Fonts::ID::SourceCodePro, buttonShapes_, Buttons::ID::StartButton);
	startButton->setPosition(WindowWidth / 2.f, WindowHeight / 2.f);
	buttons_.push_back(startButton.get());
	layers_[static_cast<std::size_t>(Layers::Buttons)]->addChild(std::move(startButton));

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
