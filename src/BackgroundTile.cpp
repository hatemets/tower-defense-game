#include "../include/BackgroundTile.hpp"

BackgroundTile::BackgroundTile(const sf::Texture& texture, const sf::IntRect& bounds)
	: tile_(texture, bounds)
{
}

void BackgroundTile::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(tile_, states);
}
