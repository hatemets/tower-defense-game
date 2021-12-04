#include "../include/BackgroundSprite.hpp"

BackgroundSprite::BackgroundSprite(const sf::Texture& texture, const sf::IntRect& bounds)
	: tile_(texture, bounds)
{
}


void BackgroundSprite::setColor(sf::Color color) 
{
	tile_.setColor(color);
}


void BackgroundSprite::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(tile_, states);
}
