#include "../include/Button.hpp"
#include "../include/auxiliary/constants.hpp"
#include <array>

// First value is the button background, the second is the text itself
std::pair<std::array<int, 3>, std::array<int, 3>> getColor(Buttons::ID id)
{
	using namespace Resources;

	switch (id)
	{
		// TODO: Add more colors
		case Buttons::ID::StartButton:
		case Buttons::ID::CheatModeButton:
		case Buttons::ID::Level1Button:
		case Buttons::ID::Level2Button:
		case Buttons::ID::Level3Button:
		case Buttons::ID::Level4Button:
		case Buttons::ID::Level5Button:
		case Buttons::ID::Level6Button:
		case Buttons::ID::Level7Button:
		case Buttons::ID::Level8Button:
		case Buttons::ID::Level9Button:
		case Buttons::ID::BuyGunTurretButton:
		case Buttons::ID::BuyDoubleGunTurretButton:
		case Buttons::ID::BuyTripleGunTurretButton:
		case Buttons::ID::BuyBombTurretButton:
		case Buttons::ID::BuyMissileTurretButton:
		case Buttons::ID::CloseBuyMenuButton:
		case Buttons::ID::SellTurretButton:
		case Buttons::ID::CloseSellMenuButton:
		case Buttons::ID::QuitButton:
		case Buttons::ID::PauseButton:
		case Buttons::ID::HomeButton:
		case Buttons::ID::LevelMenuButton:
			{
				return std::make_pair(PrimaryColor, SecondaryColor);
			}
		default: throw std::runtime_error("Unknown button id");
	}
}


Button::Button(const std::string& text, ResourceHolder<sf::Font, Fonts::ID>& fonts, Fonts::ID fontID, ButtonHolder<Buttons::ID>& resources, Buttons::ID buttonID, float scalar)
	: button_(resources.get(buttonID)),
	type_(buttonID)
{
	text_.setFont(fonts.get(fontID));
	text_.setString(text);


	// Set the scale of the text
	// This effectively sets the size of the button as well
	text_.setScale(scalar, scalar);
	text_.setStyle(sf::Text::Bold);

	auto textBounds = text_.getLocalBounds();

	text_.setOrigin((textBounds.width + textBounds.left) / 2.f, (textBounds.height + textBounds.left) / 2.f);

	button_.setSize(sf::Vector2f(textBounds.width + textBounds.left + ButtonPaddingX, textBounds.height + textBounds.top + ButtonPaddingY));
	button_.setOrigin((textBounds.width - textBounds.left + ButtonPaddingX) / 2.f, (textBounds.height - textBounds.top + ButtonPaddingY) / 2.f);

	auto colorPair = getColor(type_);

	auto primaryVals = colorPair.first;
	auto secondaryVals = colorPair.second;

	button_.setFillColor(sf::Color(primaryVals[0], primaryVals[1], primaryVals[2]));
	text_.setFillColor(sf::Color(secondaryVals[0], secondaryVals[1], secondaryVals[2]));
}


void Button::setPosition(float x, float y)
{
	text_.setPosition(x, y);
	button_.setPosition(text_.getPosition());
}


void Button::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(button_, states);
	target.draw(text_, states);
}
