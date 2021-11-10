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
	buttonShapes_.load(Resources::ID::StartButton);
}


void MainMenu::createScene()
{
	for (std::size_t i = 0; i < static_cast<std::size_t>(Layers::totalCount); ++i)
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
	// NOTE: Start button is the one that leads the user to the first level (subject to change)
	auto startButton = std::make_unique<Button>("Start", fonts_, Resources::ID::SourceCodePro, buttonShapes_, Resources::ID::StartButton);
	startButton->setPosition(WindowWidth / 2.f, WindowHeight / 2.f);
	buttons_.push_back(startButton.get());
	layers_[static_cast<std::size_t>(Layers::Buttons)]->addChild(std::move(startButton));
}

ModeState MainMenu::handleInput(sf::Vector2i mousePos)
{
	auto found = std::find_if(buttons_.begin(), buttons_.end(), [&](const Button* button)
			{
			return button->getButton().getGlobalBounds().contains(sf::Vector2f(mousePos));
			});

	if (found != buttons_.end())
	{
		const Button* button = *found;

		using namespace Resources;

		switch (button->getType())
		{
			case ID::StartButton:
				return ModeState(Type::Level);
			default:
				{
					// NOTE: Internal tasks are implemented here (none for mainmenu)
					return ModeState();
				}
		}
	}
	else
	// No button was clicked
	{
		return ModeState();
	}
}

void MainMenu::update(sf::Time deltaTime)
{
}
