#include "../include/Level.hpp"
#include "../include/BackgroundSprite.hpp"
#include "../include/Map.hpp"
#include "../include/Enemy.hpp"
#include "../include/auxiliary/constants.hpp"
#include <memory>
#include <algorithm>

Level::Level(sf::RenderWindow& window)
	: Mode(window),
	textures_(),
	map_(nullptr),
	enemies_(nullptr),
	turrets_(nullptr)
{
	loadResources();
	createScene();
}


void Level::loadResources()
{
	textures_.load(Resources::ID::GrassArea, "./include/images/levelBackground.png");
	buttonShapes_.load(Resources::ID::HomeButton);
}


void Level::createScene()
{
	for (std::size_t i = 0; i < static_cast<std::size_t>(Layers::TotalCount); ++i)
	{
		auto layerNode = std::make_unique<Node>();

		layers_.push_back(layerNode.get());

		nodeTree_.addChild(std::move(layerNode));
	}


	sf::Texture& backgroundTexture = textures_.get(Resources::ID::GrassArea);
	backgroundTexture.setRepeated(true);

	sf::IntRect bounds(windowBounds_);

	auto background = std::make_unique<BackgroundSprite>(BackgroundSprite{backgroundTexture, bounds});
	background->setPosition(0.f, 0.f);
	layers_[static_cast<std::size_t>(Layers::Background)]->addChild(std::move(background));

	auto map = std::make_unique<Map>(Map{"./include/maps/map1.txt"}); // how the level/map is chosen?
	map_ = map.get();
	map_->setPosition(0.f, 0.f);
	layers_[static_cast<std::size_t>(Layers::Background)]->addChild(std::move(map));

	auto enemies = std::make_unique<Enemies>(Enemies{map_, sf::seconds(3.f), sf::seconds(10.f)});
	enemies_ = enemies.get();
	enemies_->setPosition(0.f, 0.f);
	layers_[static_cast<std::size_t>(Layers::Entities)]->addChild(std::move(enemies));

	auto turrets = std::make_unique<Turrets>(Turrets{enemies_});
	turrets_ = turrets.get();
	turrets_->setPosition(0.f, 0.f);
	layers_[static_cast<std::size_t>(Layers::Entities)]->addChild(std::move(turrets));

	// simulate buying turrets
	const std::vector<std::pair<int, int>> &turretBaseTiles = map_->getTurretBaseTiles();
	size_t turretCreateCount = std::min(3u, turretBaseTiles.size());
	std::vector<std::pair<int, int>> turretTiles;
	while (turretTiles.size() < turretCreateCount) {
		auto tile = turretBaseTiles[rand() % turretBaseTiles.size()];
		int row = tile.second;
		int col = tile.first;
		if (!Map::isMember(row, col, turretTiles)) {
			auto turret = std::make_shared<GunTurret>(GunTurret{ row, col });
			turrets_->add(turret);
			turretTiles.push_back(tile);
		}
	}

	auto homeButton = std::make_unique<Button>("Back to Main Menu", fonts_, Resources::ID::SourceCodePro, buttonShapes_, Resources::ID::HomeButton);
	homeButton->setPosition(WindowWidth / 2.f, WindowHeight / 2.f);
	buttons_.push_back(homeButton.get());
	layers_[static_cast<std::size_t>(Layers::HUD)]->addChild(std::move(homeButton));
}

void Level::update(sf::Time deltaTime)
{
	if (enemies_)
	{
		enemies_->update(deltaTime);
	}
	if (turrets_)
	{
		turrets_->update(deltaTime);
	}
}
