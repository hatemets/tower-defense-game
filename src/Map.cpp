#include "../include/Map.hpp"
#include "../include/auxiliary/constants.hpp"
#include <cmath>
#include <fstream>
#include <sstream> 


Map::Map(const std::string& filename, ResourceHolder<sf::Texture, Textures::ID>& textures)
	: textures_(textures)
{
	loadFile(filename);
	findPaths();
	loadTextures();
}


void Map::drawSelf(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (auto& pic : mapPictures_)
	{
		target.draw(*pic, states);
	}
}


float Map::calculateAngle(const sf::Vector2f posA, const sf::Vector2f posB)
{
	return atan2f(posB.y - posA.y, posB.x - posA.x) * RadiansToDegrees;
}


float Map::calculateDistance(const sf::Vector2f posA, const sf::Vector2f posB)
{
	float deltaX = posA.x - posB.x;
	float deltaY = posA.y - posB.y;

	return std::sqrt(std::pow(deltaX, 2) + std::pow(deltaY, 2));
}


bool Map::isContact(const sf::Vector2f posA, float aRadius, const sf::Vector2f posB, float bRadius)
{
	float minDistance = aRadius + bRadius;

	return calculateDistance(posA, posB) <= minDistance;
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


void Map::findPaths()
{
	for (auto spawnTile : spawnTiles_) {
		std::vector<std::pair<int, int>> path;
		path.push_back(spawnTile);
		findPaths(path);
	}
}


void Map::findPaths(std::vector<std::pair<int, int>>& path)
{
	do
	{
		int row = path.rbegin()->first;
		int col = path.rbegin()->second;

		if (isBase(row, col)) 
		{
			// found a base i.e. the end point of this path
			paths_.push_back(path);
			return;
		}

		// find next road/base tiles

		std::vector<std::pair<int, int>> nextTiles;

		if (!isMember(row + 1, col, path) && (isRoad(row + 1, col) || isBase(row + 1, col)))
		{
			nextTiles.push_back(std::make_pair(row + 1, col));
		}
		if (!isMember(row - 1, col, path) && (isRoad(row - 1, col) || isBase(row - 1, col)))
		{
			nextTiles.push_back(std::make_pair(row - 1, col));
		}
		if (!isMember(row, col + 1, path) && (isRoad(row, col + 1) || isBase(row, col + 1)))
		{
			nextTiles.push_back(std::make_pair(row, col + 1));
		}
		if (!isMember(row, col - 1, path) && (isRoad(row, col - 1) || isBase(row, col - 1)))
		{
			nextTiles.push_back(std::make_pair(row, col - 1));
		}

		switch (nextTiles.size())
		{
			case 0:
				return; // dead end

			case 1:
				path.push_back(nextTiles[0]);
				break;

			default:
				for (auto nextTile : nextTiles)
				{
					std::vector<std::pair<int, int>> pathCopy = path;
					pathCopy.push_back(nextTile);
					findPaths(pathCopy);
				}
				return; // all path branches are taken care of by the above recursion
		}
	} while (true);
}


void Map::loadTileset(const std::vector<std::pair<int, int>>& tiles_, Textures::ID style)
{
	for (auto tile : tiles_)
	{
		int row = tile.first;
		int col = tile.second;

		auto sprite = std::make_shared<sf::Sprite>(textures_.get(style));
		auto imageBounds = sprite->getGlobalBounds();
		sprite->setScale(TileSize / imageBounds.width, TileSize / imageBounds.height);
		sprite->setPosition(col * TileSize, row * TileSize);

		mapPictures_.push_back(sprite);
	}
}


void Map::loadTextures()
{
	// the graphical presentation of the road
	loadTileset(roadTiles_);
	loadTileset(spawnTiles_);
	loadTileset(baseTiles_);
	loadTileset(turretBaseTiles_, Textures::ID::BombTurretBase);
}
