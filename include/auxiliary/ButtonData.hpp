#ifndef BUTTON_DATA_HPP
#define BUTTON_DATA_HPP

#include <string>
#include <SFML/Graphics.hpp>

struct ButtonData
{
	enum class Shape
	{
		Circle,
		Rectangle
	};

		ButtonData(sf::Vector2i dimensions, int padding, sf::Color color, const std::string& text)
			: dimensions(dimensions),
			padding(padding),
			color(color),
			text(text)
	{
	}

		sf::Vector2i dimensions;
		int padding;
		sf::Color color;
		std::string text; 
};

struct CircleData
{

};

struct RectangleData
{

};

#endif
