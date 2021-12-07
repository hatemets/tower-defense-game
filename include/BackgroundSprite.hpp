#ifndef BACKGROUND_SPRITE_HPP
#define BACKGROUND_SPRITE_HPP

#include <SFML/Graphics.hpp>
#include "Node.hpp"

class BackgroundSprite : public Node
{
	public:
		BackgroundSprite(const sf::Texture& texture, const sf::IntRect& bounds);
		BackgroundSprite(const sf::Texture& texture);
		void setColor(sf::Color color);

	private:
		virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::Sprite tile_;
};

#endif
