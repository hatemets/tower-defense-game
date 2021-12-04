#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceHolder.hpp"
#include "Node.hpp"

using namespace Resources;

class Button : public Node
{
	public:
		explicit Button(const std::string& text, ResourceHolder<sf::Font, Fonts::ID>& fonts, Fonts::ID fontID, ButtonHolder<Buttons::ID>& resources, Buttons::ID buttonID, float scalar = 1.f);
		virtual void drawSelf(sf::RenderTarget &target, sf::RenderStates states) const final;

		// TODO: create an abstract base class for entities that move
		void setPosition(float x, float y);
		const sf::RectangleShape& getButton() const { return button_; }
		Buttons::ID getType() const { return type_; }

	private:
		sf::Text text_;
		sf::RectangleShape button_;
		Buttons::ID type_;
};

#endif
