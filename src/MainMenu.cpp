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
	textures_.load(Textures::ID::GrassArea, "./include/images/MainMenuBackground.png");

	buttonShapes_.load(Buttons::ID::LevelMenu);
	buttonShapes_.load(Buttons::ID::Quit);
}


void MainMenu::createScene()
{
	initializePointers(static_cast<std::size_t>(Layers::TotalCount));
	addBackground();
	addButtons();
}


void MainMenu::addBackground()
{
	// Set the background for the menu
	sf::Texture& backgroundTexture = textures_.get(Textures::ID::GrassArea);
	backgroundTexture.setRepeated(true);

	sf::IntRect bounds(windowBounds_);

	auto background = std::make_unique<BackgroundSprite>(BackgroundSprite{backgroundTexture, bounds});
	background->setPosition(0.f, 0.f);
	layers_[static_cast<std::size_t>(Layers::Background)]->addChild(std::move(background));
}

void MainMenu::addButtons()
{
	// Start button
	auto startButton = std::make_unique<Button>("Play", fonts_, Fonts::ID::SourceCodePro, buttonShapes_, Buttons::ID::LevelMenu);
    sf::Vector2f startBtnPos(WindowWidth / 2.f, WindowHeight / 2.f + 80.f);
	startButton->setPosition(startBtnPos.x, startBtnPos.y);
	buttons_.push_back(startButton.get());
	layers_[static_cast<std::size_t>(Layers::Buttons)]->addChild(std::move(startButton));

	auto quitButton = std::make_unique<Button>("Exit", fonts_, Fonts::ID::SourceCodePro, buttonShapes_, Buttons::ID::Quit);
	quitButton->setPosition(startBtnPos.x, startBtnPos.y + quitButton->getButton().getSize().y + ButtonMargin);
	buttons_.push_back(quitButton.get());
	layers_[static_cast<std::size_t>(Layers::Buttons)]->addChild(std::move(quitButton));
}


void MainMenu::update(sf::Time deltaTime)
{
}
