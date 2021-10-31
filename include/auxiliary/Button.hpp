#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

struct Button
{
	Button(sf::Vector2f size, sf::Color color, const std::string& text) :
		size(size),
		color(color),
		text(text)
	{
	}

	sf::Vector2f size;
	sf::Color color;
	std::string text;
};

#endif
