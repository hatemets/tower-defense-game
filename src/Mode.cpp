#include "../include/Mode.hpp"


Mode::Mode(sf::RenderWindow& window)
	: window_(window),
	layers_(),
	nodeTree_(),
	windowBounds_(0.f, 0.f, window_.getSize().x, window_.getSize().y),
	fonts_(),
	buttons_(),
	buttonShapes_()
{
	// TODO: Create a universal filepath
	fonts_.load(Resources::ID::SourceCodePro, "./include/fonts/SourceCodePro.ttf");
}


void Mode::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(nodeTree_, states);
}
