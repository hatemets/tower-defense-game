#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include "Node.hpp"

class BackgroundTile : public Node
{
	public:
		BackgroundTile(const sf::Texture& texture, const sf::IntRect& bounds);

	private:
		virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::Sprite tile_;
};

#endif
