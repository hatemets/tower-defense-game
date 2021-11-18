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
	bulletVertices_(sf::Points, 0)
{
	loadResources();
	createScene();
}


void Level::loadResources()
{
	textures_.load(Textures::ID::GrassArea, "./include/images/Grass.png");
	textures_.load(Textures::ID::DirtPath, "./include/images/Ground.png");
	textures_.load(Textures::ID::OrangeBase, "./include/images/TurretBaseOrange.png");

	buttonShapes_.load(Buttons::ID::HomeButton);
}


void Level::createScene()
{
	initializePointers(static_cast<std::size_t>(Layers::TotalCount));
	addBackground();
	addButtons();
	loadMap();

	// Projectiles
	// TODO: Implement projectiles

	// Simulate buying turrets
	const std::vector<std::pair<int, int>>& turretBaseTiles = map_->getTurretBaseTiles();

	std::size_t turretCreateCount = std::min<std::size_t>(3, turretBaseTiles.size());
	/* std::size_t turretCreateCount = (3 < turretBaseTiles.size()) ? 3 : turretBaseTiles.size(); */

	std::vector<std::pair<int, int>> turretTiles;

	while (turretTiles.size() < turretCreateCount)
	{
		auto tile = turretBaseTiles[rand() % turretBaseTiles.size()];
		int row = tile.second;
		int col = tile.first;

		if (!Map::isMember(row, col, turretTiles))
		{
			// Add a turret to the turret container
			turrets_.push_back(std::make_shared<GunTurret>(GunTurret{ row, col }));
			turretTiles.push_back(tile);
		}
	}
}


void Level::loadMap()
{
	// Map
	auto map = std::make_unique<Map>(Map{"./include/maps/map1.txt", textures_}); // how the level/map is chosen?
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
	enemies_.erase(std::remove_if(enemies_.begin(), enemies_.end(),
				[](const std::shared_ptr<Enemy> &enemy)
				{
				return !enemy->isAlive() || enemy->hasReachedBase();
				}),
			enemies_.end());

	for (auto enemy : enemies_)
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

		auto path = map_->getPath();
		auto goblin = std::make_shared<Goblin>(Goblin{path.first, path.second});
		enemies_.push_back(goblin);
	}
}


void Level::updateTurrets(sf::Time deltaTime)
{
	for (auto& turret : turrets_)
	{
		turret->update(deltaTime, enemies_);
	}
}


void Level::updateProjectiles(sf::Time deltaTime)
{

	// remove outdated bullets and other projectiles
	projectiles_.erase(std::remove_if(projectiles_.begin(), projectiles_.end(),
				[](const std::shared_ptr<Projectile> &projectile)
				{
				return !projectile->isAlive();
				}), projectiles_.end());

	for (auto& projectile : projectiles_)
	{
		projectile->update(deltaTime, enemies_);
	}

	bulletVertices_.resize(projectiles_.size());

	int i = 0;

	for (auto& bullet : projectiles_)
	{
		bulletVertices_[i].position = sf::Vector2f(bullet->getTileX() * TileSize, bullet->getTileY() * TileSize);
		bulletVertices_[i].color = sf::Color::White;
		i++;
	}
}


void Level::addBackground()
{
	// Background
	sf::Texture& backgroundTexture = textures_.get(Textures::ID::GrassArea);
	backgroundTexture.setRepeated(true);

	sf::IntRect bounds(windowBounds_);

	auto background = std::make_unique<BackgroundSprite>(BackgroundSprite{backgroundTexture, bounds});
	background->setPosition(0.f, 0.f);
	layers_[static_cast<std::size_t>(Layers::Background)]->addChild(std::move(background));
}

void Level::addProjectile(std::shared_ptr<Projectile> projectile)
{
	std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(projectile);

	// TODO: Remove the if statement and the parameter
	if (bullet)
	{
		projectiles_.push_back(bullet);
	}
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

	if (bulletVertices_.getVertexCount() > 0)
	{
		target.draw(bulletVertices_, states);
	}

	// TODO: Might need to change projectile code
	/* for (auto& projectile : projectiles_) */
	/* { */
	/* 	projectile->drawSelf(target, states); */
	/* } */
}

