#include "../include/Mode.hpp"
#include "../include/auxiliary/constants.hpp"

#include <iostream>

Mode::Mode(sf::RenderWindow& window, std::shared_ptr<GameData> gameData)
	: window_(window),
	layers_(),
	nodeTree_(),
	windowBounds_(0.f, 0.f, WindowWidth, WindowHeight),
	fonts_(),
	buttons_(),
	buttonShapes_(),
    gameData_(gameData)
{
	// TODO: Create a universal filepath
	fonts_.load(Fonts::ID::SourceCodePro, "./include/fonts/SourceCodePro.ttf");
}


void Mode::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(nodeTree_, states);
}

void Mode::initializePointers(std::size_t layerCount)
{
	for (std::size_t i = 0; i < layerCount; ++i)
	{
		auto layerNode = std::make_unique<Node>();

		layers_.push_back(layerNode.get());

		nodeTree_.addChild(std::move(layerNode));
	}
}

ModeState Mode::handleInput(sf::Vector2i mousePos)
{
	auto found = std::find_if(buttons_.begin(), buttons_.end(), [&](const Button* button)
			{
			return button->getButton().getGlobalBounds().contains(window_.mapPixelToCoords(mousePos));
			});

	if (found != buttons_.end())
	{
		const Button* button = *found;

		using namespace Resources;

		switch (button->getType())
		{
			case Buttons::ID::Start:
				return ModeState(Type::NewGame);
			case Buttons::ID::CheatMode:
				return ModeState(Type::CheatMode);
			case Buttons::ID::Level1:
                // std::cout << gameData_->getMaxOpenLevel() << std::endl;
                if (gameData_->getMaxOpenLevel() < 1) return ModeState(Action::ShowMessage);
				return ModeState(Type::Level1);
			case Buttons::ID::Level2:
                if (gameData_->getMaxOpenLevel() < 2) return ModeState(Action::ShowMessage);
				return ModeState(Type::Level2);
			case Buttons::ID::Level3:
                if (gameData_->getMaxOpenLevel() < 3) return ModeState(Action::ShowMessage);
				return ModeState(Type::Level3);
			case Buttons::ID::Level4:
                if (gameData_->getMaxOpenLevel() < 4) return ModeState(Action::ShowMessage);
				return ModeState(Type::Level4);
			case Buttons::ID::Level5:
                if (gameData_->getMaxOpenLevel() < 5) return ModeState(Action::ShowMessage);
				return ModeState(Type::Level5);
			case Buttons::ID::Level6:
                if (gameData_->getMaxOpenLevel() < 6) return ModeState(Action::ShowMessage);
				return ModeState(Type::Level6);
			case Buttons::ID::Home:
				return ModeState(Type::MainMenu);
			case Buttons::ID::LevelMenu:
				return ModeState(Type::LevelMenu);
			case Buttons::ID::Quit:
				return ModeState(Type::Quit);
			default:
				return ModeState();
		}
	}
	else
	// No button was clicked
	{
		return ModeState();
	}
}
