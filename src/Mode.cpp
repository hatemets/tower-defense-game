#include "../include/Mode.hpp"
#include "../include/auxiliary/constants.hpp"


Mode::Mode(sf::RenderWindow& window)
	: window_(window),
	layers_(),
	nodeTree_(),
	windowBounds_(0.f, 0.f, WindowWidth, WindowHeight),
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
			case Buttons::ID::StartButton:
				return ModeState(Type::NewGame);
			case Buttons::ID::CheatModeButton:
				return ModeState(Type::CheatMode);
			case Buttons::ID::Level1Button:
				return ModeState(Type::Level1);
			case Buttons::ID::Level2Button:
				return ModeState(Type::Level2);
			case Buttons::ID::Level3Button:
				return ModeState(Type::Level3);
			case Buttons::ID::Level4Button:
				return ModeState(Type::Level4);
			case Buttons::ID::Level5Button:
				return ModeState(Type::Level5);
			case Buttons::ID::Level6Button:
				return ModeState(Type::Level6);
			case Buttons::ID::Level7Button:
				return ModeState(Type::Level7);
			case Buttons::ID::Level8Button:
				return ModeState(Type::Level8);
			case Buttons::ID::Level9Button:
				return ModeState(Type::Level9);
			case Buttons::ID::HomeButton:
				return ModeState(Type::MainMenu);
			case Buttons::ID::LevelMenuButton:
				return ModeState(Type::LevelMenu);
			case Buttons::ID::QuitButton:
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
