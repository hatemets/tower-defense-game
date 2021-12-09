#include "../include/Level.hpp"
#include "../include/BackgroundSprite.hpp"
#include "../include/Map.hpp"
#include "../include/Enemy.hpp"
#include "../include/auxiliary/constants.hpp"
#include <memory>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>

Level::Level(sf::RenderWindow& window, std::shared_ptr<GameData> gameData)
	: Mode(window, gameData),
	textures_(),
	map_(nullptr),
	enemies_(),
	minSpawnInterval_(sf::seconds(LevelMinSpawnIntervals[gameData->getLevel() - 1])),
	maxSpawnInterval_(sf::seconds(LevelMaxSpawnIntervals[gameData->getLevel() - 1])),
	nextSpawn_(sf::seconds(LevelFirstSpawnTime)),
	turrets_(),
	projectileVertices_(sf::Points, 0),
	selectedTurret_(nullptr),
	selectedTurretBase_(nullptr),
    gameOverMessage_("Game Over", Message::Type::GameOver),
    credits_(LevelLimits[gameData_->getLevel() - 1]),
    monstersKilled_(0),
    passed_(false),
	maxOpenLevel_(gameData->getMaxOpenLevel()),
    backgroundMusic_(),
    sounds_()
{
	loadResources();
	createScene();
    createStats();
	updateTexts();
    playMusic();
}


void Level::pauseSounds()
{
    for (auto& audioPair : sounds_)
    {
        audioPair.second.second->pause();
    }
}


void Level::playMusic()
{
    backgroundMusic_.openFromFile("./include/audio/Adventures_Himitsu.wav");
    backgroundMusic_.play();
    backgroundMusic_.setLoop(true);
}


void Level::createStats()
{
    creditsText_.setFont(fonts_.get(Fonts::ID::SourceCodePro));
    creditsText_.setCharacterSize(CreditsTextFontSize);
    creditsText_.setFillColor(sf::Color::White);
    creditsText_.setPosition(CreditsTextPaddingX, 0.f);

    levelText_.setFont(fonts_.get(Fonts::ID::SourceCodePro));
    levelText_.setCharacterSize(LevelTextFontSize);
    levelText_.setFillColor(sf::Color::White);
    levelText_.setPosition(WindowWidth / 2.f + 25.f, 0.f);
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

	buttonShapes_.load(Buttons::ID::Home);
	buttonShapes_.load(Buttons::ID::LevelMenu);
	buttonShapes_.load(Buttons::ID::BuyGunTurret);
	buttonShapes_.load(Buttons::ID::BuyDoubleGunTurret);
	buttonShapes_.load(Buttons::ID::BuyTripleGunTurret);
	buttonShapes_.load(Buttons::ID::BuyBombTurret);
	buttonShapes_.load(Buttons::ID::BuyMissileTurret);
	buttonShapes_.load(Buttons::ID::CloseBuyMenu);
	buttonShapes_.load(Buttons::ID::SellTurret);
	buttonShapes_.load(Buttons::ID::CloseSellMenu);
}


void Level::createScene()
{
	initializePointers(static_cast<std::size_t>(Layers::TotalCount));
	addBackground();
	addButtons();
	addBuyMenu();
	addSellMenu();
	loadMap();
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
	auto homeButton = std::make_unique<Button>("X", fonts_, buttonShapes_, Buttons::ID::LevelMenu, 4);
	auto homeButtonSize = homeButton->getButton().getSize();

	// NOTE: Added button padding y for it to stick to the upper side of the window
	homeButton->setPosition(WindowWidth - homeButtonSize.x / 2.f, homeButtonSize.y / 2.f - ButtonMargin);
	buttons_.push_back(homeButton.get());
	layers_[static_cast<std::size_t>(Layers::HUD)]->addChild(std::move(homeButton));
}


void Level::addBuyMenu()
{
	int buttonCount = 6;
	const float buttonMargin = 10.f;

	std::stringstream ss1;
	ss1 << "Buy Gun Turret $" << Turrets::Gun::price;
	auto buyButton = std::make_shared<Button>(ss1.str(), fonts_, buttonShapes_, Buttons::ID::BuyGunTurret, 28);
	buyButton->setPosition(WindowWidth / 2.f, WindowHeight / 2.f - ((buttonCount - 1) / 2.f) * (buyButton->getButton().getSize().y + buttonMargin));
	buyMenu_.push_back(buyButton);

	addBuyButton("Double Gun Turret", Turrets::DoubleGun::price, Buttons::ID::BuyDoubleGunTurret, buttonMargin);
	addBuyButton("Bomb Turret", Turrets::Bomb::price, Buttons::ID::BuyBombTurret, buttonMargin);
	addBuyButton("Triple Gun Turret", Turrets::TripleGun::price, Buttons::ID::BuyTripleGunTurret, buttonMargin);
	addBuyButton("Missile Turret", Turrets::Missile::price, Buttons::ID::BuyMissileTurret, buttonMargin);

	buyButton = std::make_shared<Button>("Cancel", fonts_, buttonShapes_, Buttons::ID::CloseBuyMenu);
	auto pos = buyMenu_[buyMenu_.size() - 1]->getButton().getPosition();
	buyButton->setPosition(pos.x, pos.y + buyButton->getButton().getSize().y + buttonMargin);
	buyMenu_.push_back(buyButton);
}


void Level::addBuyButton(std::string name, int price, Buttons::ID buttonId, float buttonMargin)
{
	std::stringstream ss;
	ss << "Buy " << name << " $" << price;
	auto buyButton = std::make_shared<Button>(ss.str(), fonts_, buttonShapes_, buttonId, 28);
	auto pos = buyMenu_[buyMenu_.size() - 1]->getButton().getPosition();
	buyButton->setPosition(pos.x, pos.y + buyButton->getButton().getSize().y + buttonMargin);
	buyMenu_.push_back(buyButton);
}


void Level::addSellMenu()
{
	int buttonCount = 2;
	const float buttonMargin = 10.f;

	auto sellButton = std::make_shared<Button>("Remove Turret", fonts_, buttonShapes_, Buttons::ID::SellTurret);
	sellButton->setPosition(WindowWidth / 2.f, WindowHeight / 2.f - ((buttonCount - 1) / 2.f) * (sellButton->getButton().getSize().y + buttonMargin));
	sellMenu_.push_back(sellButton);

	sellButton = std::make_shared<Button>("Cancel", fonts_, buttonShapes_, Buttons::ID::CloseSellMenu);
	auto pos = sellMenu_[sellMenu_.size() - 1]->getButton().getPosition();
	sellButton->setPosition(pos.x, pos.y + sellButton->getButton().getSize().y + buttonMargin);
	sellMenu_.push_back(sellButton);
}


void Level::update(sf::Time deltaTime)
{
	checkGameOver();

    if (levelPassed() && !passed_)
    {
        passed_ = true;

        if (gameData_->getLevel() >= maxOpenLevel_ && maxOpenLevel_ < TotalLevels)
        {
			maxOpenLevel_ = gameData_->getLevel() + 1;

			try
			{
				std::ofstream ofs("./include/auxiliary/cache.txt", std::ios::trunc);
            	ofs << maxOpenLevel_;
            	ofs.close();
			}
			catch (...)
			{
				// failed to store max level to the cache file
			}    
        }
    }

	if (!gameData_->isGameOver())
	{
		collectRewards();
		updateEnemies(deltaTime);
		updateTurrets(deltaTime);
		updateExplosions(deltaTime);
		createExplosions();
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
				gameData_->setGameOver(true);
				selectedTurret_ = nullptr; // disable sell menu
				selectedTurretBase_ = nullptr; // disable buy menu
                sounds_.clear();
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
            credits_ += enemy->getReward();
            monstersKilled_++;
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


void Level::createExplosions()
{
	for (auto& projectile : projectiles_)
	{
		if (!projectile->isAlive() && projectile->getExplosionRadius() > 0.f)
		{
			explosions_.push_back(std::make_shared<Explosion>(Explosion{projectile->getPosition(), projectile->getExplosionRadius()}));
		}
	}
}


void Level::updateExplosions(sf::Time deltaTime)
{
	// remove outdated explosions
	explosions_.erase(std::remove_if(explosions_.begin(), explosions_.end(),
				[](const std::shared_ptr<Explosion> &explosion)
				{
				return !explosion->isAlive();
				}), explosions_.end());

	for (auto& explosion : explosions_)
	{
		explosion->update(deltaTime);
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
	ss1 << "/" << std::min(maxOpenLevel_, TotalLevels);

    if (levelPassed())
    {
        ss1 << " [Completed]";
    }

    ss1 << "    Score: " << monstersKilled_;

	levelText_.setString(ss1.str());
	levelText_.setOrigin(levelText_.getLocalBounds().width / 2.f, 0.f);

	std::stringstream ss2;
	ss2 << "Gold: " << credits_;
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

	for (auto& explosion : explosions_)
	{
		explosion->drawSelf(target, states);
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
	/* target.draw(monstersKilledText_, states); */

	if (gameData_->isGameOver())
	{
        gameOverMessage_.drawSelf(target, states);
	}
	else if (selectedTurret_)
	{
		for (auto& button : sellMenu_)
		{
			button->drawSelf(target, states);
		}		
	}
	else if (selectedTurretBase_)
	{
		for (auto& button : buyMenu_)
		{
			button->drawSelf(target, states);
		}		
	}
}


ModeState Level::handleInput(sf::Vector2i mousePos)
{
    // Exit if X button is clicked
    if (Mode::handleInput(mousePos).action == Action::ModeChange)
    {
        return Mode::handleInput(mousePos);
    }

	auto mouseTileCoords = window_.mapPixelToCoords(mousePos) / (float)TileSize;

	if (selectedTurret_)
	{
		// handle sell menu click
		auto found = std::find_if(sellMenu_.begin(), sellMenu_.end(), [&](std::shared_ptr<Button> button)
		{
			return button->getButton().getGlobalBounds().contains(window_.mapPixelToCoords(mousePos));
		});

		if (found != sellMenu_.end())
		{
			std::shared_ptr<Button> button = *found;

			switch (button->getType())
			{
				case Buttons::ID::SellTurret:
					turrets_.erase(std::remove(turrets_.begin(), turrets_.end(), selectedTurret_), turrets_.end());
					map_->findSafestPaths(turrets_); // this has to be called everytime turrets are updated
					break;
				case Buttons::ID::CloseSellMenu:
					break;
				default:
					break;
			}
			selectedTurret_ = nullptr; // remove selection
		}
	}
	else if (selectedTurretBase_)
	{
		// handle buy menu click
		auto found = std::find_if(buyMenu_.begin(), buyMenu_.end(), [&](std::shared_ptr<Button> button)
		{
			return button->getButton().getGlobalBounds().contains(window_.mapPixelToCoords(mousePos));
		});

		if (found != buyMenu_.end())
		{
			int row = selectedTurretBase_->first;
			int col = selectedTurretBase_->second;
			std::shared_ptr<Turret> turret(nullptr);

			std::shared_ptr<Button> button = *found;

			switch (button->getType())
			{
				case Buttons::ID::BuyGunTurret:
					turret = std::make_shared<GunTurret>(GunTurret{ row, col, textures_, sounds_ });
					break;
				case Buttons::ID::BuyDoubleGunTurret:
					turret = std::make_shared<DoubleGunTurret>(DoubleGunTurret{ row, col, textures_, sounds_ });
					break;
				case Buttons::ID::BuyTripleGunTurret:
					turret = std::make_shared<TripleGunTurret>(TripleGunTurret{ row, col, textures_, sounds_ });
					break;
				case Buttons::ID::BuyBombTurret:
					turret = std::make_shared<BombTurret>(BombTurret{ row, col, textures_, sounds_ });
					break;
				case Buttons::ID::BuyMissileTurret:
					turret = std::make_shared<MissileTurret>(MissileTurret{ row, col, textures_, sounds_ });
					break;
				case Buttons::ID::CloseBuyMenu:
					break;
				default:
					break;
			}
			selectedTurretBase_ = nullptr; // remove selection

			if (turret && turret->getPrice() <= credits_)
			{
                credits_ -= turret->getPrice();
				turrets_.push_back(turret);
				map_->findSafestPaths(turrets_); // this has to be called everytime turrets are updated
			}
		}
	}
	else if (!gameData_->isGameOver())
	{
		// select clicked turret
		for (auto& turret : turrets_)
		{
			if (Map::calculateDistance(mouseTileCoords, turret->getPosition()) <= 0.75f) // 0.75 > sqrt(2) / 2
			{
				selectedTurret_ = turret;
				break;
			}
		}

		// select clicked turret base
		if (!selectedTurret_)
		{
			int row = mouseTileCoords.y;
			int col = mouseTileCoords.x;

			if (map_->isTurretBase(row, col))
			{
				selectedTurretBase_ = std::make_shared<std::pair<int, int>>(row, col);
			}
		}
	}

	return Mode::handleInput(mousePos);
}


bool Level::levelPassed()
{
    return monstersKilled_ >= RequiredMonsterKills;
}
