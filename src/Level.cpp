#include "../include/Level.hpp"
#include "../include/BackgroundSprite.hpp"
#include "../include/Map.hpp"
#include "../include/Enemy.hpp"
#include "../include/auxiliary/constants.hpp"
#include <memory>
#include <algorithm>
#include <iostream>
#include <sstream>

Level::Level(sf::RenderWindow& window, std::shared_ptr<GameData> gameData)
	: Mode(window),
	textures_(),
	map_(nullptr),
	gameData_(gameData),
	enemies_(),
	minSpawnInterval_(sf::seconds(LevelMinSpawnIntervals[gameData->getLevel() - 1])),
	maxSpawnInterval_(sf::seconds(LevelMaxSpawnIntervals[gameData->getLevel() - 1])),
	nextSpawn_(sf::seconds(1)),
	turrets_(),
	projectileVertices_(sf::Points, 0)
{
	loadResources();
	createScene();

	updateTexts();

	levelText_.setFont(fonts_.get(Fonts::ID::SourceCodePro));
	levelText_.setCharacterSize(LevelTextFontSize);
	levelText_.setFillColor(sf::Color::White);
	levelText_.setPosition(WindowWidth / 2.f, 0.f);
	levelText_.setOrigin(levelText_.getLocalBounds().width / 2.f, 0.f);

	creditsText_.setFont(fonts_.get(Fonts::ID::SourceCodePro));
	creditsText_.setCharacterSize(CreditsTextFontSize);
	creditsText_.setFillColor(sf::Color::White);
	creditsText_.setPosition(CreditsTextPaddingX, 0.f);

	gameOverText_.setString("Game Over");
	gameOverText_.setFont(fonts_.get(Fonts::ID::SourceCodePro));
	gameOverText_.setCharacterSize(GameOverTextFontSize);
	gameOverText_.setFillColor(sf::Color::Red);
	gameOverText_.setPosition(WindowWidth / 2.f, WindowHeight / 2.f);
	gameOverText_.setOrigin(gameOverText_.getLocalBounds().width / 2.f, gameOverText_.getLocalBounds().height);
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
	textures_.load(Textures::ID::MissileBase, "./include/images/MissileBase.png");
	textures_.load(Textures::ID::Missile, "./include/images/Missile.png");
	textures_.load(Textures::ID::Goblin, "./include/images/Goblin.png");
	textures_.load(Textures::ID::Orc, "./include/images/Orc.png");
	textures_.load(Textures::ID::Troll, "./include/images/Troll.png");
	textures_.load(Textures::ID::Slime, "./include/images/Slime.png");
	textures_.load(Textures::ID::Kobold, "./include/images/Kobold.png");
	textures_.load(Textures::ID::Health100, "./include/images/Health100.png");
	textures_.load(Textures::ID::Health80, "./include/images/Health80.png");
	textures_.load(Textures::ID::Health60, "./include/images/Health60.png");
	textures_.load(Textures::ID::Health40, "./include/images/Health40.png");
	textures_.load(Textures::ID::Health20, "./include/images/Health20.png");

	buttonShapes_.load(Buttons::ID::HomeButton);
	buttonShapes_.load(Buttons::ID::LevelMenuButton);
}


void Level::createScene()
{
	initializePointers(static_cast<std::size_t>(Layers::TotalCount));
	addBackground();
	addButtons();
	loadMap();

	// Simulate buying turrets
	const std::vector<std::pair<int, int>>& turretBaseTiles = map_->getTurretBaseTiles();

	std::size_t turretCreateCount = std::min<std::size_t>(5, turretBaseTiles.size());

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

				case 3:
					turrets_.push_back(std::make_shared<BombTurret>(BombTurret{ row, col, textures_ }));
					break;

				default:
					turrets_.push_back(std::make_shared<MissileTurret>(MissileTurret{ row, col, textures_ }));
					break;
			}
			turretTiles.push_back(tile);
		}
	}
	map_->findSafestPaths(turrets_); // this has to be called everytime turrets are updated
}


void Level::loadMap()
{
	std::stringstream ss;
	ss << "./include/maps/map" << gameData_->getLevel() << ".txt";
	auto map = std::make_unique<Map>(Map{ss.str(), textures_}); 
	map_ = map.get();
	map_->setPosition(0.f, 0.f);
	layers_[static_cast<std::size_t>(Layers::Background)]->addChild(std::move(map));
}


void Level::addButtons()
{
	// Home button
	auto homeButton = std::make_unique<Button>("X", fonts_, Fonts::ID::SourceCodePro, buttonShapes_, Buttons::ID::LevelMenuButton);
	auto homeButtonSize = homeButton->getButton().getSize();

	// NOTE: Added button padding y for it to stick to the upper side of the window
	homeButton->setPosition(WindowWidth - homeButtonSize.x / 2.f, homeButtonSize.y / 2.f - ButtonPaddingY);
	buttons_.push_back(homeButton.get());
	layers_[static_cast<std::size_t>(Layers::HUD)]->addChild(std::move(homeButton));
}


void Level::update(sf::Time deltaTime)
{
	checkGameOver();
	if (!gameData_->isGameOver())
	{
		collectRewards();
		updateEnemies(deltaTime);
		updateTurrets(deltaTime);
		updateProjectiles(deltaTime);
		updateTexts();
	}
}


void Level::checkGameOver()
{
	if (!gameData_->isGameOver())
	{
		for (auto& enemy : enemies_)
		{
			if (enemy->hasReachedBase())
			{
				gameData_->setGameOver();
				return;
			}
		}
	}
}


void Level::collectRewards()
{
	for (auto& enemy : enemies_)
	{
		if (!enemy->isAlive())
		{
			gameData_->addCredits(enemy->getReward());
		}
	}
}


void Level::updateEnemies(sf::Time deltaTime)
{
	EnemyList newEnemies;
	for (auto& enemy : enemies_)
	{
		enemy->spawnNewEnemies(newEnemies);
	}
	for (auto& enemy : newEnemies) 
	{
		enemies_.push_back(enemy);
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

		switch (rand() % std::min(gameData_->getLevel(), 5))
		{
			case 0:
			{
				auto orc = std::make_shared<Orc>(Orc{*map_, textures_});
				enemies_.push_back(orc);
				break;
			}

			case 1:
			{
				auto goblin = std::make_shared<Goblin>(Goblin{*map_, textures_});
				enemies_.push_back(goblin);
				break;
			}

			case 2:
			{
				auto troll = std::make_shared<Troll>(Troll{*map_, textures_});
				enemies_.push_back(troll);
				break;
			}

			case 3:
			{
				auto slime = std::make_shared<Slime>(Slime{*map_, textures_});
				enemies_.push_back(slime);
				break;
			}

			case 4:
			{
				auto kobold = std::make_shared<Kobold>(Kobold{*map_, textures_});
				enemies_.push_back(kobold);
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


void Level::updateTexts()
{
	std::stringstream ss1;
	ss1 << "Level " << gameData_->getLevel();
	ss1 << "/" << std::max(gameData_->getMaxOpenLevel(), 1);
	levelText_.setString(ss1.str());

	std::stringstream ss2;
	ss2 << "Credits: " << gameData_->getCredits();
	creditsText_.setString(ss2.str());
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

	target.draw(levelText_, states);
	target.draw(creditsText_, states);

	if (gameData_->isGameOver())
	{
		target.draw(gameOverText_, states);
	}
}

