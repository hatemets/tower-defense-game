#include "../include/Map.hpp"
#include "../include/auxiliary/constants.hpp"
#include <math.h>


Map::Map(sf::RenderWindow& window, const std::string& fileName) :
	window_(window)
{
    loadFile(fileName);
    loadTextures();
}


void Map::draw()
{
	// draw map

	for (auto pic : mapPictures_) {
		window_.draw(*pic);
	}

	// draw objects (move to Level?)

	
}


float Map::calculateDistance2(float aX, float aY, float bX, float bY)
{
    float deltaX = aX - bX;
    float deltaY = aY - bY;
    return deltaX * deltaX + deltaY * deltaY;
}


float Map::calculateDistance(float aX, float aY, float bX, float bY) 
{
    float distance2 = calculateDistance2(aX, aY, bX, bY);
    return sqrtf(distance2);
}


float Map::calculatetAngle(float aX, float aY, float bX, float bY) 
{
    return atan2f(aY - bY, aX - bX) * RadiansToDegrees;
}


void Map::update(sf::Time deltaTime)
{
	// move to Level?
}


void Map::loadFile(const std::string& fileName) 
{
    // for testing this simulates loading the road from a file
    
	for (int col = 0; col < 7; col++) {
		roadTiles_.push_back(std::make_pair(col, 5));
	}
	for (int row = 6; row < 15; row++) {
		roadTiles_.push_back(std::make_pair(6, row));
	}
	for (int col = 7; col < TileCols; col++) {
		roadTiles_.push_back(std::make_pair(col, 14));
	} 

    // for testing this simulates loading the turret places from a file
	while (turretBaseTiles_.size() < 10) {
		int col = rand() % TileCols;
		int row = rand() % TileRows;
		auto tile = std::make_pair(row, col);
		if ((std::find(roadTiles_.begin(), roadTiles_.end(), tile) == roadTiles_.end()) && 
		    (std::find(turretBaseTiles_.begin(), turretBaseTiles_.end(), tile) == turretBaseTiles_.end())) {
				turretBaseTiles_.push_back(tile);
		}
	}
}


void Map::loadTextures() 
{
    // the graphical presentation of the road
	for (auto roadTile : roadTiles_) {
		int col = roadTile.first;
		int row = roadTile.second;
		std::shared_ptr<sf::RectangleShape> road(new sf::RectangleShape);
		road->setSize(sf::Vector2f(TileSize, TileSize));
		road->setPosition(col * TileSize, row * TileSize);
    	road->setFillColor(sf::Color::Yellow);
		mapPictures_.push_back(road);
	}

    // the graphical presentation of the available turret places
	for (auto turretBaseTile : turretBaseTiles_) {
		int col = turretBaseTile.first;
		int row = turretBaseTile.second;
		std::shared_ptr<sf::CircleShape> place(new sf::CircleShape);
		place->setRadius(TileSize / 2);
		place->setPosition(col * TileSize, row * TileSize);
    	place->setFillColor(sf::Color::Blue);
		mapPictures_.push_back(place);
	}
}


