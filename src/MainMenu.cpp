#include "../include/MainMenu.hpp"
#include "../include/BackgroundSprite.hpp"
#include "../include/auxiliary/constants.hpp"
#include <memory>
#include <iostream>

MainMenu::MainMenu(sf::RenderWindow& window)
	: Mode(window),
	textures_()
{
	loadResources();
	createScene();
}


void MainMenu::loadResources()
{
	textures_.load(Resources::ID::GrassArea, "./include/images/background1.jpg");
	buttonShapes_.load(Resources::ID::LevelMenuButton);
}


void MainMenu::createScene()
{
	for (std::size_t i = 0; i < static_cast<std::size_t>(Layers::TotalCount); ++i)
	{
		auto layerNode = std::make_unique<Node>();

		layers_.push_back(layerNode.get());

		nodeTree_.addChild(std::move(layerNode));
	}


	// Set the background for the menu
	sf::Texture& backgroundTexture = textures_.get(Resources::ID::GrassArea);
	backgroundTexture.setRepeated(true);

	sf::IntRect bounds(windowBounds_);

	auto background = std::make_unique<BackgroundSprite>(BackgroundSprite{backgroundTexture, bounds});
	background->setPosition(0.f, 0.f);
	layers_[static_cast<std::size_t>(Layers::Background)]->addChild(std::move(background));


	// Configure the buttons
	auto startButton = std::make_unique<Button>("Play", fonts_, Resources::ID::SourceCodePro, buttonShapes_, Resources::ID::LevelMenuButton);
	startButton->setPosition(WindowWidth / 2.f, WindowHeight / 2.f);
	buttons_.push_back(startButton.get());
	layers_[static_cast<std::size_t>(Layers::Buttons)]->addChild(std::move(startButton));
}

void MainMenu::update(sf::Time deltaTime)
{
}
