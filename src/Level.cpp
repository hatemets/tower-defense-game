#include "../include/Level.hpp"
#include "../include/auxiliary/constants.hpp"


Level::Level(sf::RenderWindow& window, const std::string& levelName) :
	window_(window),
	levelName_(levelName),
	sceneTree_() //,
	//textures_()
{
	// load level

	// for testing this simulates loading the road from a file
	for (int col = 0; col < 10; col++) {
		roadTiles_.push_back(std::make_pair(10, col));
	}
	for (int row = 11; row < 21; row++) {
		roadTiles_.push_back(std::make_pair(row, 9));
	}
	for (int col = 10; col < 40; col++) {
		roadTiles_.push_back(std::make_pair(20, col));
	}
/*
	for (auto roadTile : roadTiles_) {
		int col = roadTile.first;
		int row = roadTile.second;
		std::shared_ptr<sf::RectangleShape> rec;
		rec->setSize(sf::Vector2f(TileSize, TileSize));
		rec->setPosition(col * TileSize, row * TileSize);
    	rec->setFillColor(sf::Color::Yellow);
		roadRectangles_.push_back(rec);
	}*/
}

void Level::loadTextures()
{
}

void Level::update(sf::Time deltaTime)
{
	// move objects
}

void Level::draw()
{
	// draw map

	// draw objects

	
}
