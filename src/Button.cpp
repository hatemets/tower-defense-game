#include "../include/Button.hpp"
#include "../include/auxiliary/constants.hpp"

// First value is the button background, the second is the text itself
std::pair<sf::Color, sf::Color> getColor(Buttons::ID id)
{
	using namespace Resources;

	switch (id)
	{
		case Buttons::ID::StartButton:
			{
				return std::make_pair(sf::Color::Green, sf::Color::Black);
			}
		case Buttons::ID::QuitButton:
			{
				return std::make_pair(sf::Color::Red, sf::Color::White);
			}
		case Buttons::ID::PauseButton:
			{
				return std::make_pair(sf::Color::Yellow, sf::Color::Black);
			}
		case Buttons::ID::HomeButton:
			{
				return std::make_pair(sf::Color::Yellow, sf::Color::Black);
			}
		case Buttons::ID::LevelMenuButton:
			{
				return std::make_pair(sf::Color::Magenta, sf::Color::White);
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


	// Set the scale of the text (default is 1)
	// This effectively sets the size of the button as well
	text_.setScale(scalar, scalar);

	auto textBounds = text_.getLocalBounds();

	text_.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);


	button_.setSize(sf::Vector2f(textBounds.width + textBounds.left + ButtonPaddingX, textBounds.height + textBounds.top + ButtonPaddingY));
	button_.setOrigin((textBounds.width - textBounds.left + ButtonPaddingX) / 2.f, (textBounds.height - textBounds.top + ButtonPaddingY) / 2.f);

	auto colorPair = getColor(type_);

	button_.setFillColor(colorPair.first);
	text_.setFillColor(colorPair.second);
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
