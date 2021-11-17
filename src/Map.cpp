#include "../include/Map.hpp"
#include "../include/auxiliary/constants.hpp"
#include <math.h>
#include <fstream>
#include <sstream> 

Map::Map(const std::string &fileName)
{
	loadFile(fileName);
	findPaths();
	loadTextures();
}


void Map::drawSelf(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (auto pic : mapPictures_)
	{
		target.draw(*pic, states);
	}
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


float Map::calculateAngle(float aX, float aY, float bX, float bY)
{
	return atan2f(bY - aY, bX - aX) * RadiansToDegrees;
}


bool Map::isContact(float aX, float aY, float aRadius, float bX, float bY, float bRadius)
{
	float minDistance = aRadius + bRadius;
	float distance2 = calculateDistance2(aX, aY, bX, bY);
	return distance2 < (minDistance * minDistance);
}


std::pair<std::vector<std::pair<int, int>>::const_iterator, std::vector<std::pair<int, int>>::const_iterator> Map::getPath() const
{
	switch (paths_.size())
	{
		case 0:
			throw std::runtime_error("No paths available!");
			break;

		case 1:
			return std::make_pair(paths_[0].cbegin(), paths_[0].cend());
			break;

		default:
			int pathIndex = rand() % paths_.size();
			return std::make_pair(paths_[pathIndex].cbegin(), paths_[pathIndex].cend());
			break;
	}
}


const std::vector<std::pair<int, int>> &Map::getTurretBaseTiles() const
{
	return turretBaseTiles_;
}


void Map::loadFile(const std::string &fileName)
{
	std::ifstream istr(fileName);
	if (istr.rdstate() & (istr.failbit | istr.badbit))
	{
		std::stringstream ss;
		ss << "Failed to read map file " << fileName;
		throw std::runtime_error(ss.str());
	}
	else
	{
		int row = 0;
		while (!istr.eof())
		{
			std::string line;
			std::getline(istr, line);
			if (row < TileRows)
			{
				for (int col = 0; col < (int)line.length(); col++)
				{
					if (col < TileCols)
					{
						switch (line[col])
						{
						case 'S':
							spawnTiles_.push_back(std::make_pair(row, col));
							break;

						case '#':
							roadTiles_.push_back(std::make_pair(row, col));
							break;

						case 'B':
							baseTiles_.push_back(std::make_pair(row, col));
							break;

						case 'O':
							turretBaseTiles_.push_back(std::make_pair(row, col));
							break;

						default:
							break;
						}
					}
				}
			}

			row++;
		}
	}
}


bool Map::isMember(int row, int col, const std::vector<std::pair<int, int>> &container)
{
	return std::find(container.cbegin(), container.cend(), std::make_pair(row, col)) != container.cend();
}


bool Map::isSpawn(int row, int col) const
{
	return isMember(row, col, spawnTiles_);
}


bool Map::isRoad(int row, int col) const
{
	return isMember(row, col, roadTiles_);
}


bool Map::isBase(int row, int col) const
{
	return isMember(row, col, baseTiles_);
}


bool Map::isTurretBase(int row, int col) const
{
	return isMember(row, col, turretBaseTiles_);
}


void Map::findPaths()
{
	std::vector<std::pair<int, int>> path;

	//choose spawning tile 

	if (spawnTiles_.size() == 0)
	{
		// fix invalid map, add spawn
		if (roadTiles_.size() > 0)
		{
			spawnTiles_.push_back(*roadTiles_.begin());
		}
		else
		{
			spawnTiles_.push_back(std::make_pair(0, 0));
		}
	}
	path.push_back(*spawnTiles_.begin());

	//find the rest of the path (doesn't support multiple paths yet)

	do
	{
		int row = path.rbegin()->first;
		int col = path.rbegin()->second;

		std::vector<std::pair<int, int>> nextTiles;

		// check if we have a base as a neighbour
		if (isBase(row + 1, col))
		{
			path.push_back(std::make_pair(row + 1, col));
			break;
		}
		if (isBase(row - 1, col))
		{
			path.push_back(std::make_pair(row - 1, col));
			break;
		}
		if (isBase(row, col + 1))
		{
			path.push_back(std::make_pair(row, col + 1));
			break;
		}
		if (isBase(row, col - 1))
		{
			path.push_back(std::make_pair(row, col - 1));
			break;
		}

		// otherwise find next road
		if (!isMember(row + 1, col, path) && isRoad(row + 1, col))
		{
			nextTiles.push_back(std::make_pair(row + 1, col));
		}
		if (!isMember(row - 1, col, path) && isRoad(row - 1, col))
		{
			nextTiles.push_back(std::make_pair(row - 1, col));
		}
		if (!isMember(row, col + 1, path) && isRoad(row, col + 1))
		{
			nextTiles.push_back(std::make_pair(row, col + 1));
		}
		if (!isMember(row, col - 1, path) && isRoad(row, col - 1))
		{
			nextTiles.push_back(std::make_pair(row, col - 1));
		}

		if (nextTiles.size() == 0)
		{
			break; // cannot find base or road
		}
		else
		{
			path.push_back(nextTiles[0]); // here we should follow all next tiles recursively if size > 1
		}

	} while (true);

	if (!isBase(path.rbegin()->first, path.rbegin()->second))
	{
		// fix invalid map, add base
		baseTiles_.push_back(std::make_pair(path.rbegin()->first, path.rbegin()->second));
	}

	paths_.push_back(path);
}


void Map::loadTextures()
{
	// the graphical presentation of the road
	for (auto roadTile : roadTiles_)
	{
		int row = roadTile.first;
		int col = roadTile.second;
		std::shared_ptr<sf::RectangleShape> road(new sf::RectangleShape);
		road->setSize(sf::Vector2f(TileSize, TileSize));
		road->setPosition(col * TileSize, row * TileSize);
		road->setFillColor(sf::Color::Black);
		mapPictures_.push_back(road);
	}

	// the graphical presentation of the spawns
	for (auto spawnTile : spawnTiles_)
	{
		int row = spawnTile.first;
		int col = spawnTile.second;
		std::shared_ptr<sf::RectangleShape> spawn(new sf::RectangleShape);
		spawn->setSize(sf::Vector2f(TileSize, TileSize));
		spawn->setPosition(col * TileSize, row * TileSize);
		spawn->setFillColor(sf::Color::Yellow);
		mapPictures_.push_back(spawn);
	}

	// the graphical presentation of the bases
	for (auto baseTile : baseTiles_)
	{
		int row = baseTile.first;
		int col = baseTile.second;
		std::shared_ptr<sf::RectangleShape> base(new sf::RectangleShape);
		base->setSize(sf::Vector2f(TileSize, TileSize));
		base->setPosition(col * TileSize, row * TileSize);
		base->setFillColor(sf::Color::Red);
		mapPictures_.push_back(base);
	}

	// the graphical presentation of the available turret places
	for (auto turretBaseTile : turretBaseTiles_)
	{
		int row = turretBaseTile.first;
		int col = turretBaseTile.second;
		std::shared_ptr<sf::CircleShape> turretBase(new sf::CircleShape);
		turretBase->setRadius(TileSize * 0.3f);
		turretBase->setPosition((col + 0.2f) * TileSize, (row + 0.2f) * TileSize);
		turretBase->setFillColor(sf::Color::Blue);
		mapPictures_.push_back(turretBase);
	}
}
