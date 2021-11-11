#include "../include/Map.hpp"
#include "../include/auxiliary/constants.hpp"
#include <math.h>


Map::Map(sf::RenderWindow& window, const std::string& fileName) :
	window_(window)
{
    loadFile(fileName);
	findPaths();
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


bool Map::isContact(float aX, float aY, float aRadius, float bX, float bY, float bRadius)
{
    float minDistance = aRadius + bRadius;
    float distance2 = calculateDistance2(aX, aY, bX, bY);
    return distance2 < (minDistance * minDistance);
}


void Map::update(sf::Time deltaTime)
{
	// move to Level?
}


void Map::loadFile(const std::string& fileName) 
{
    // for testing this simulates loading the road from a file
    
	for (int col = 0; col < 7; col++) {
		roadTiles_.push_back(std::make_pair(5, col));
	}
	for (int row = 6; row < 15; row++) {
		roadTiles_.push_back(std::make_pair(row, 6));
	}
	for (int col = 7; col < TileCols; col++) {
		roadTiles_.push_back(std::make_pair(14, col));
	} 

    // for testing this simulates loading the turret places from a file
	while (turretBaseTiles_.size() < 10) {
		int row = rand() % TileRows;
		int col = rand() % TileCols;
		if (!isRoad(row, col) && !isTurretBase(row, col)) {
			turretBaseTiles_.push_back(std::make_pair(row, col));
		}
	}
}


bool Map::isMember(int row, int col, const std::vector<std::pair<int, int>>& container)
{
	return std::find(container.cbegin(), container.cend(), std::make_pair(row, col)) != container.cend();
}


bool Map::isRoad(int row, int col) const
{
	return isMember(row, col, roadTiles_);
}


bool Map::isTurretBase(int row, int col) const
{
	return isMember(row, col, turretBaseTiles_);
}


void Map::findPaths()
{
	std::vector<std::pair<int, int>> path;

	//find spawning tile = the first tile in the path
	for (int row = 0; row < TileRows && path.size() == 0; row++) {
		for (int col = 0; col < TileCols; col++) {
			if (isRoad(row, col)) {
				int neighbours = 0;
				if (isRoad(row + 1, col)) {
					neighbours++;
				}
				if (isRoad(row - 1, col)) {
					neighbours++;
				}
				if (isRoad(row, col + 1)) {
					neighbours++;
				}
				if (isRoad(row, col - 1)) {
					neighbours++;
				}
				if (neighbours == 1) {
					path.push_back(std::make_pair(row, col));
					break;
				}
			}	
		}
	}
	if (path.size() == 0) {
		path.push_back(std::make_pair(0, 0));
	}

	//find the rest of the path (doesn't support multiple paths yet)
	bool baseFound = false;
	do {
		int row = path.rbegin()->first;
		int col = path.rbegin()->second;

		std::vector<std::pair<int, int>> nextTiles;
		if (!isMember(row + 1, col, path) && isRoad(row + 1, col)) {
			nextTiles.push_back(std::make_pair(row + 1, col));
		}
		if (!isMember(row - 1, col, path) && isRoad(row - 1, col)) {
			nextTiles.push_back(std::make_pair(row - 1, col));
		}
		if (!isMember(row, col + 1, path) && isRoad(row, col + 1)) {
			nextTiles.push_back(std::make_pair(row, col + 1));
		}
		if (!isMember(row, col - 1, path) && isRoad(row, col - 1)) {
			nextTiles.push_back(std::make_pair(row, col - 1));
		}

		if (nextTiles.size() == 0) {
			baseFound = true;
		} else {
			path.push_back(nextTiles[0]);  // here we should follow all next tiles recursively if size > 1
		}

	} while (!baseFound);

	paths_.push_back(path);
}


void Map::loadTextures() 
{
	auto& firstPath = paths_[0];
	auto spawningTile = *firstPath.begin();
	auto baseTile = *firstPath.rbegin();

    // the graphical presentation of the road
	for (auto roadTile : roadTiles_) {
		int row = roadTile.first;
		int col = roadTile.second;
		std::shared_ptr<sf::RectangleShape> road(new sf::RectangleShape);
		road->setSize(sf::Vector2f(TileSize, TileSize));
		road->setPosition(col * TileSize, row * TileSize);
		if (spawningTile.first == row && spawningTile.second == col) {
			road->setFillColor(sf::Color::Green);
		} else if (baseTile.first == row && baseTile.second == col) {
			road->setFillColor(sf::Color::Red);
		} else {
			road->setFillColor(sf::Color::Yellow);
		}
		mapPictures_.push_back(road);
	}

    // the graphical presentation of the available turret places
	for (auto turretBaseTile : turretBaseTiles_) {
		int row = turretBaseTile.first;
		int col = turretBaseTile.second;
		std::shared_ptr<sf::CircleShape> place(new sf::CircleShape);
		place->setRadius(TileSize / 2);
		place->setPosition(col * TileSize, row * TileSize);
    	place->setFillColor(sf::Color::Blue);
		mapPictures_.push_back(place);
	}
}

