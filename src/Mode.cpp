#include "../include/Mode.hpp"


Mode::Mode(sf::RenderWindow& window)
	: window_(window),
	windowBounds_(0.f, 0.f, window.getSize().x, window.getSize().y),
	layers_(),
	nodeTree_()
{
}


void Mode::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(nodeTree_, states);
}
