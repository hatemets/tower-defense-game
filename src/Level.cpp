#include "../include/Level.hpp"
#include "../include/BackgroundSprite.hpp"
#include "../include/Map.hpp"
#include "../include/Enemy.hpp"
#include "../include/auxiliary/constants.hpp"
#include <memory>
#include <algorithm>
#include <iostream>

Level::Level(sf::RenderWindow& window, sf::Time minSpawnInterval, sf::Time maxSpawnInterval)
	: Mode(window),
	textures_(),
	map_(nullptr),
	enemies_(),
	minSpawnInterval_(minSpawnInterval),
	maxSpawnInterval_(maxSpawnInterval),
	// TODO: Remove hardcoded values
	nextSpawn_(sf::seconds(1)),
	turrets_(),
	projectileVertices_(sf::Points, 0)
{
	loadResources();
	createScene();
}


void Level::loadResources()
{
	textures_.load(Textures::ID::GrassArea, "./include/images/Grass.png");
	textures_.load(Textures::ID::DirtPath, "./include/images/Ground.png");
	textures_.load(Textures::ID::Flag, "./include/images/Flag.png");
	textures_.load(Textures::ID::GunTurretBase, "./include/images/GunTurretBase.png");
	textures_.load(Textures::ID::GunTurret, "./include/images/GunTurret.png");
	textures_.load(Textures::ID::DoubleGunTurret, "./include/images/DoubleGunTurret.png");
	textures_.load(Textures::ID::DoubleGunTurretBase, "./include/images/DoubleGunTurretBase.png");
	textures_.load(Textures::ID::TripleGunTurret, "./include/images/TripleGunTurret.png");
	textures_.load(Textures::ID::TripleGunTurretBase, "./include/images/TripleGunTurretBase.png");
	textures_.load(Textures::ID::BombTurretBase, "./include/images/BombTurretBase.png");
	textures_.load(Textures::ID::BombTurret, "./include/images/BombTurret.png");
	textures_.load(Textures::ID::Goblin, "./include/images/Goblin.png");
	textures_.load(Textures::ID::Orc, "./include/images/Orc.png");
	textures_.load(Textures::ID::Troll, "./include/images/Troll.png");
	textures_.load(Textures::ID::Slime, "./include/images/Slime.png");
	textures_.load(Textures::ID::Health100, "./include/images/Health100.png");
	textures_.load(Textures::ID::Health80, "./include/images/Health80.png");
	textures_.load(Textures::ID::Health60, "./include/images/Health60.png");
	textures_.load(Textures::ID::Health40, "./include/images/Health40.png");
	textures_.load(Textures::ID::Health20, "./include/images/Health20.png");

	buttonShapes_.load(Buttons::ID::HomeButton);
}


void Level::createScene()
{
	initializePointers(static_cast<std::size_t>(Layers::TotalCount));
	addBackground();
	addButtons();
	loadMap();

	// Simulate buying turrets
	const std::vector<std::pair<int, int>>& turretBaseTiles = map_->getTurretBaseTiles();

	std::size_t turretCreateCount = std::min<std::size_t>(4, turretBaseTiles.size());

	std::vector<std::pair<int, int>> turretTiles;

	while (turretTiles.size() < turretCreateCount)
	{
		auto tile = turretBaseTiles[rand() % turretBaseTiles.size()];
		int row = tile.first;
		int col = tile.second;

		if (!Map::isMember(row, col, turretTiles))
		{
			// Add a turret to the turret container
			switch (turretTiles.size())
			{
				case 0:
					turrets_.push_back(std::make_shared<GunTurret>(GunTurret{ row, col, textures_ }));
					break;

				case 1:
					turrets_.push_back(std::make_shared<DoubleGunTurret>(DoubleGunTurret{ row, col, textures_ }));
					break;

				case 2:
					turrets_.push_back(std::make_shared<TripleGunTurret>(TripleGunTurret{ row, col, textures_ }));
					break;

				default:
					turrets_.push_back(std::make_shared<BombTurret>(BombTurret{ row, col, textures_ }));
					break;
			}
			turretTiles.push_back(tile);
		}
	}
}


void Level::loadMap()
{
	// Map
	auto map = std::make_unique<Map>(Map{"./include/maps/map2.txt", textures_}); // how the level/map is chosen?
	map_ = map.get();
	map_->setPosition(0.f, 0.f);
	layers_[static_cast<std::size_t>(Layers::Background)]->addChild(std::move(map));
}


void Level::addButtons()
{
	// Home button
	auto homeButton = std::make_unique<Button>("X", fonts_, Fonts::ID::SourceCodePro, buttonShapes_, Buttons::ID::HomeButton);
	auto homeButtonSize = homeButton->getButton().getSize();

	// NOTE: Added button padding y for it to stick to the upper side of the window
	homeButton->setPosition(WindowWidth - homeButtonSize.x / 2.f, homeButtonSize.y / 2.f - ButtonPaddingY);
	buttons_.push_back(homeButton.get());
	layers_[static_cast<std::size_t>(Layers::HUD)]->addChild(std::move(homeButton));
}


void Level::update(sf::Time deltaTime)
{
	updateEnemies(deltaTime);
	updateTurrets(deltaTime);
	updateProjectiles(deltaTime);
}


void Level::updateEnemies(sf::Time deltaTime)
{
	for (auto& enemy : enemies_)
	{
		enemy->spawnNewEnemies(enemies_);
	}

	enemies_.erase(std::remove_if(enemies_.begin(), enemies_.end(),
				[](const std::shared_ptr<Enemy> &enemy)
				{
				return !enemy->isAlive() || enemy->hasReachedBase();
				}),
			enemies_.end());

	for (auto& enemy : enemies_)
	{
		enemy->update(deltaTime);
	}

	nextSpawn_ -= deltaTime;

	if (nextSpawn_.asSeconds() <= 0)
	{
		sf::Time timeDiff = maxSpawnInterval_ - minSpawnInterval_;
		if (timeDiff.asMilliseconds() > 1)
		{
			sf::Time randomTime = sf::milliseconds(rand() % timeDiff.asMilliseconds());
			nextSpawn_ = minSpawnInterval_ + randomTime;
		}
		else
		{
			nextSpawn_ = minSpawnInterval_;
		}

		int level = 4; // FIX THIS: This should be the actual level number
		switch (rand() % std::min(level, 4)) // 4 is here the number of all different enemies
		{
			case 0:
			{
				auto path = map_->getRandomPath();
				auto orc = std::make_shared<Orc>(Orc{path.first, path.second, textures_});
				enemies_.push_back(orc);
				break;
			}

			case 1:
			{
				auto path = map_->getRandomPath();
				auto goblin = std::make_shared<Goblin>(Goblin{path.first, path.second, textures_});
				enemies_.push_back(goblin);
				break;
			}

			case 2:
			{
				auto path = map_->getShortestPath();
				auto troll = std::make_shared<Troll>(Troll{path.first, path.second, textures_});
				enemies_.push_back(troll);
				break;
			}

			case 3:
			{
				auto path = map_->getShortestPath();
				auto slime = std::make_shared<Slime>(Slime{path.first, path.second, textures_});
				enemies_.push_back(slime);
				break;
			}
		}
		
	}
}


void Level::updateTurrets(sf::Time deltaTime)
{
	for (auto& turret : turrets_)
	{
		turret->update(deltaTime, enemies_, projectiles_);
	}
}


void Level::updateProjectiles(sf::Time deltaTime)
{
	// remove outdated projectiles
	projectiles_.erase(std::remove_if(projectiles_.begin(), projectiles_.end(),
				[](const std::shared_ptr<Projectile> &projectile)
				{
				return !projectile->isAlive();
				}), projectiles_.end());

	for (auto& projectile : projectiles_)
	{
		projectile->update(deltaTime, enemies_);
	}

	if (GameHasVertexProjectiles)
	{
		// collect all projectiles, that can be drawn as a vertex
		projectileVertices_.resize(projectiles_.size());

		int vertexCount = 0;
		for (auto& projectile : projectiles_)
		{
			if (projectile->drawAsVertex())
			{
				projectileVertices_[vertexCount].position = projectile->getPosition() * (float)TileSize;
				projectileVertices_[vertexCount].color = sf::Color::White;
				vertexCount++;
			}
		}

		projectileVertices_.resize(vertexCount);
	}
	
}


void Level::addBackground()
{
	// Background
	sf::Texture& backgroundTexture = textures_.get(Textures::ID::GrassArea);
	backgroundTexture.setRepeated(true);

	sf::IntRect bounds(windowBounds_);

	auto background = std::make_unique<BackgroundSprite>(BackgroundSprite{backgroundTexture, bounds});
	background->setColor(sf::Color(128, 128, 128)); // make grass darker so that bullets are more visible
	background->setPosition(0.f, 0.f);
	layers_[static_cast<std::size_t>(Layers::Background)]->addChild(std::move(background));
}


void Level::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
	Mode::drawSelf(target, states);

	for (auto& enemy : enemies_)
	{
		enemy->drawSelf(target, states);
	}

	for (auto& turret : turrets_)
	{
		turret->drawSelf(target, states);
	}

	// draw vertex projectiles
	if (projectileVertices_.getVertexCount() > 0)
	{
		target.draw(projectileVertices_, states);
	}

	// draw sprite/shape projectiles
	for (auto& projectile : projectiles_)
	{
		if (!projectile->drawAsVertex())
		{
			projectile->drawSelf(target, states);
		}
	}
}

