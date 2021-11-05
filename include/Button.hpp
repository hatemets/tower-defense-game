#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Button
{
	public:
		Button(sf::Vector2f size, sf::Vector2i padding, sf::Color color, const std::string& text, const sf::Font& font, ResourceHolder<Resources::ID, sf::Shape>);

	private:
		sf::Vector2f size_;
		sf::Vector2i padding_;
		sf::Color color_;
		std::string text_;
		sf::RectangleShape button_;
};

#endif
