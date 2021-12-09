#include "../include/Map.hpp"
#include "../include/auxiliary/constants.hpp"
#include "../include/Turret.hpp"
#include <cmath>
#include <fstream>
#include <sstream>
#include <limits>

Map::Map(const std::string &filename, ResourceHolder<sf::Texture, Textures::ID> &textures)
	: textures_(textures)
{
	loadFile(filename);
	findPaths();
	loadTextures();
}


void Map::drawSelf(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (auto &pic : mapPictures_)
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


std::pair<std::vector<std::pair<int, int>>::const_iterator, std::vector<std::pair<int, int>>::const_iterator> Map::getPath(const std::vector<int> &pathIndexes) const
{
	switch (pathIndexes.size())
	{
		case 0:
			throw std::runtime_error("No path indexes available!");
			break;

		case 1:
		{
			int pathIndex = pathIndexes[0];
			return std::make_pair(paths_[pathIndex].cbegin(), paths_[pathIndex].cend());
			break;
		}

		default:
		{
			int pathIndex = pathIndexes[rand() % pathIndexes.size()];
			return std::make_pair(paths_[pathIndex].cbegin(), paths_[pathIndex].cend());
			break;
		}
	}
}


std::pair<std::vector<std::pair<int, int>>::const_iterator, std::vector<std::pair<int, int>>::const_iterator> Map::getRandomPath() const
{
	return getPath(pathIndexes_);
}


std::pair<std::vector<std::pair<int, int>>::const_iterator, std::vector<std::pair<int, int>>::const_iterator> Map::getShortestPath() const
{
	return getPath(shortestPathIndexes_);
}


std::pair<std::vector<std::pair<int, int>>::const_iterator, std::vector<std::pair<int, int>>::const_iterator> Map::getSafestPath() const
{
	return getPath(safestPathIndexes_);
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
	for (auto spawnTile : spawnTiles_)
	{
		std::vector<std::pair<int, int>> path;
		path.push_back(spawnTile);
		findPaths(path);
	}

	for (int i = 0; i < static_cast<int>(paths_.size()); i++)
	{
		pathIndexes_.push_back(i);
	}

	findShortestPaths();

	// safest = shortest before any turrets are added
	for (int pathIndex : shortestPathIndexes_)
	{
		safestPathIndexes_.push_back(pathIndex);
	}
}


void Map::findPaths(std::vector<std::pair<int, int>> &path)
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


// find shortest path for each spawn tile
void Map::findShortestPaths()
{
	for (auto spawnTile : spawnTiles_)
	{
		int minLength = std::numeric_limits<int>::max();
		int shortestIndex = -1;
		for (int i = 0; i < static_cast<int>(paths_.size()); i++)
		{
			if (*paths_[i].begin() == spawnTile)
			{
				int pathLength = paths_[i].size();
				if (pathLength < minLength)
				{
					minLength = pathLength;
					shortestIndex = i;
				}
			}
		}
		if (shortestIndex >= 0)
		{
			shortestPathIndexes_.push_back(shortestIndex);
		}
	}
}


// find safest path for each spawn tile
void Map::findSafestPaths(TurretList &turrets)
{
	safestPathIndexes_.clear();

	std::vector<std::tuple<sf::Vector2f, float, float>> turretInfos;

	for (auto &turret : turrets)
	{
		float maxDamagePerSecond = 0;
		for (auto &projectile : turret->shoot())
		{
			maxDamagePerSecond += projectile->getMaxDamage() * turret->getRateOfFire();
		}
		turretInfos.push_back(std::make_tuple(turret->getPosition(), turret->getRadarRange(), maxDamagePerSecond));
	}

	std::vector<float> pathTotalDamages;
	for (auto &path : paths_)
	{
		float pathTotalDamage = 0;
		for (auto ite = path.begin(); ite != path.end(); ite++)
		{
			float roadX = ite->second + 0.5f;
			float roadY = ite->first + 0.5f;
			sf::Vector2f roadPosition(roadX, roadY);
			for (auto &turretInfo : turretInfos)
			{
				if (isContact(roadPosition, 0.f, std::get<0>(turretInfo), std::get<1>(turretInfo)))
				{
					pathTotalDamage += std::get<2>(turretInfo);
				}
			}
		}
		pathTotalDamages.push_back(pathTotalDamage);
	}

	for (auto spawnTile : spawnTiles_)
	{
		float minTotalDamage = std::numeric_limits<float>::max();
		int safestIndex = -1;
		for (int i = 0; i < static_cast<int>(paths_.size()); i++)
		{
			if (*paths_[i].begin() == spawnTile)
			{
				if (pathTotalDamages[i] < minTotalDamage)
				{
					minTotalDamage = pathTotalDamages[i];
					safestIndex = i;
				}
			}
		}
		if (safestIndex >= 0)
		{
			safestPathIndexes_.push_back(safestIndex);
		}
	}
}


void Map::loadTileset(const std::vector<std::pair<int, int>> &tiles_, Textures::ID style, float scale)
{
	for (auto tile : tiles_)
	{
		int row = tile.first;
		int col = tile.second;

		auto sprite = std::make_shared<sf::Sprite>(textures_.get(style));
		auto imageBounds = sprite->getGlobalBounds();
		sprite->setScale(scale * TileSize / imageBounds.width, scale * TileSize / imageBounds.height);
		float scalingFix = (1.f - scale) / 2.f;
		sprite->setPosition((col + scalingFix) * TileSize, (row + scalingFix) * TileSize);

		mapPictures_.push_back(sprite);
	}
}


void Map::loadTextures()
{
	// the graphical presentation of the road
	loadTileset(roadTiles_);
	loadTileset(spawnTiles_);
	loadTileset(baseTiles_);
	loadTileset(baseTiles_, Textures::ID::Flag, 0.5f);
	loadTileset(turretBaseTiles_, Textures::ID::BombTurretBase);
}
