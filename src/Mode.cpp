#include "../include/Mode.hpp"


Mode::Mode(sf::RenderWindow& window)
	: window_(window),
	layers_(),
	nodeTree_(),
	windowBounds_(0.f, 0.f, window_.getSize().x, window_.getSize().y),
	fonts_(),
	buttons_(),
	buttonShapes_()
{
	// TODO: Create a universal filepath
	fonts_.load(Fonts::ID::SourceCodePro, "./include/fonts/SourceCodePro.ttf");
}


void Mode::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(nodeTree_, states);
}

ModeState Mode::handleInput(sf::Vector2i mousePos)
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
			case Buttons::ID::StartButton:
				return ModeState(Type::Level);
			case Buttons::ID::HomeButton:
				return ModeState(Type::MainMenu);
			case Buttons::ID::LevelMenuButton:
				return ModeState(Type::LevelMenu);
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
