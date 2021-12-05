#include "../include/Button.hpp"
#include "../include/auxiliary/constants.hpp"
#include <array>


Button::Button(const std::string& text, ResourceHolder<sf::Font, Fonts::ID>& fonts, Fonts::ID fontID, ButtonHolder<Buttons::ID>& resources, Buttons::ID buttonID)
	: button_(resources.get(buttonID)),
	type_(buttonID)
{
	text_.setFont(fonts.get(fontID));
	text_.setString(text);


    const float ButtonPaddingX = 40.f;
    const float ButtonPaddingY = 30.f;

	// Set the scale of the text
	// This effectively sets the size of the button as well
	text_.setScale(ButtonScalar, ButtonScalar);
	text_.setStyle(sf::Text::Bold);

	auto textBounds = text_.getLocalBounds();

	text_.setOrigin((textBounds.width + textBounds.left) / 2.f, (textBounds.height + textBounds.left) / 2.f);

	button_.setSize(sf::Vector2f(textBounds.width + textBounds.left + ButtonPaddingX, textBounds.height + textBounds.top + ButtonPaddingY));
	button_.setOrigin((textBounds.width - textBounds.left + ButtonPaddingX) / 2.f, (textBounds.height - textBounds.top + ButtonPaddingY) / 2.f);

	button_.setFillColor(sf::Color(PrimaryColor[0], PrimaryColor[1], PrimaryColor[2]));
	text_.setFillColor(sf::Color(SecondaryColor[0], SecondaryColor[1], SecondaryColor[2]));
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
