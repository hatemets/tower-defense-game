#include "../include/Level.hpp"
#include "../include/BackgroundSprite.hpp"
#include "../include/auxiliary/constants.hpp"
#include <memory>

Level::Level(sf::RenderWindow& window)
	: Mode(window),
	textures_()
{
	loadResources();
	createScene();
}


void Level::loadResources()
{
	textures_.load(Resources::ID::GrassArea, "./include/images/levelBackground.png");
	buttonShapes_.load(Resources::ID::HomeButton);
}


void Level::createScene()
{
	for (std::size_t i = 0; i < static_cast<std::size_t>(Layers::totalCount); ++i)
	{
		auto layerNode = std::make_unique<Node>();

		layers_.push_back(layerNode.get());

		nodeTree_.addChild(std::move(layerNode));
	}


	sf::Texture& backgroundTexture = textures_.get(Resources::ID::GrassArea);
	backgroundTexture.setRepeated(true);

	sf::IntRect bounds(windowBounds_);

	auto background = std::make_unique<BackgroundSprite>(BackgroundSprite{backgroundTexture, bounds});
	background->setPosition(0.f, 0.f);
	layers_[static_cast<std::size_t>(Layers::Background)]->addChild(std::move(background));


	auto homeButton = std::make_unique<Button>("Back to Main Menu", fonts_, Resources::ID::SourceCodePro, buttonShapes_, Resources::ID::HomeButton);
	homeButton->setPosition(WindowWidth / 2.f, WindowHeight / 2.f);
	buttons_.push_back(homeButton.get());
	layers_[static_cast<std::size_t>(Layers::HUD)]->addChild(std::move(homeButton));
}

void Level::update(sf::Time deltaTime)
{
}

ModeState Level::handleInput(sf::Vector2i mousePos)
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
			/* case ID::StartButton: */
			/* 	return ModeState(Type::Level); */
			case ID::HomeButton:
				return ModeState(Type::MainMenu);
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
