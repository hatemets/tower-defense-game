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
		roadTiles_.push_back(std::make_pair(col, 10));
	}
	for (int row = 11; row < 21; row++) {
		roadTiles_.push_back(std::make_pair(9, row));
	}
	for (int col = 10; col < 40; col++) {
		roadTiles_.push_back(std::make_pair(col, 20));
	}

	// for testing this simulates loading the turret places from a file
	while (turretPlaceTiles_.size() < 30) {
		int col = rand() % 40;
		int row = rand() % 30;
		auto tile = std::make_pair(row, col);
		if ((std::find(roadTiles_.begin(), roadTiles_.end(), tile) == roadTiles_.end()) && 
		    (std::find(turretPlaceTiles_.begin(), turretPlaceTiles_.end(), tile) == turretPlaceTiles_.end())) {
				turretPlaceTiles_.push_back(tile);
		}
	}
	
	// the graphical presentation of the road
	for (auto roadTile : roadTiles_) {
		int col = roadTile.first;
		int row = roadTile.second;
		std::shared_ptr<sf::RectangleShape> road(new sf::RectangleShape);
		road->setSize(sf::Vector2f(TileSize, TileSize));
		road->setPosition(col * TileSize, row * TileSize);
    	road->setFillColor(sf::Color::Yellow);
		roadPictures_.push_back(road);
	}

	// the graphical presentation of the available turret places
	for (auto turretPlaceTile : turretPlaceTiles_) {
		int col = turretPlaceTile.first;
		int row = turretPlaceTile.second;
		std::shared_ptr<sf::CircleShape> place(new sf::CircleShape);
		place->setRadius(TileSize / 2);
		place->setPosition(col * TileSize, row * TileSize);
    	place->setFillColor(sf::Color::Red);
		turretPlacePictures_.push_back(place);
	}
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

	for (auto road : roadPictures_) {
		window_.draw(*road);
	}
	for (auto place : turretPlacePictures_) {
		window_.draw(*place);
	}

	// draw objects

	
}
