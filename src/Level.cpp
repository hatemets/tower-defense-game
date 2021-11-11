#include "../include/Level.hpp"
#include "../include/auxiliary/constants.hpp"


Level::Level(sf::RenderWindow& window, const std::string& fileName) :
	window_(window),
	map_(window, fileName),
	sceneTree_() //,
	//textures_()
{
}

void Level::loadTextures()
{
}

void Level::update(sf::Time deltaTime)
{
	// move objects
	map_.update(deltaTime);
}

void Level::draw()
{
	map_.draw();

	// draw objects
	
}
