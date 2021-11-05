#include "../include/Button.hpp"


Button::Button(sf::Vector2f size, sf::Vector2i padding, sf::Color color, const std::string& text, const sf::Font& font, const sf::Shape& buttonShape) :
	size_(size),
	padding_(padding),
	color_(color),
	text_(text)
{
}
