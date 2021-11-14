#include "../include/Level.hpp"
#include "../include/BackgroundSprite.hpp"
#include "../include/Map.hpp"
#include "../include/Enemy.hpp"
#include "../include/auxiliary/constants.hpp"
#include <memory>

Level::Level(sf::RenderWindow& window)
	: Mode(window),
	textures_(),
	goblin_(nullptr)
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
	Map* mapPtr = map.get();
	map->setPosition(0.f, 0.f);
	layers_[static_cast<std::size_t>(Layers::Background)]->addChild(std::move(map));

	auto path = mapPtr->getPath();
	auto goblin = std::make_unique<Goblin>(Goblin{path.first, path.second});
	goblin_ = goblin.get();
	goblin->setPosition(0.f, 0.f);
	layers_[static_cast<std::size_t>(Layers::Entities)]->addChild(std::move(goblin));

	auto homeButton = std::make_unique<Button>("Back to Main Menu", fonts_, Resources::ID::SourceCodePro, buttonShapes_, Resources::ID::HomeButton);
	homeButton->setPosition(WindowWidth / 2.f, WindowHeight / 2.f);
	buttons_.push_back(homeButton.get());
	layers_[static_cast<std::size_t>(Layers::HUD)]->addChild(std::move(homeButton));
}

void Level::update(sf::Time deltaTime)
{
	if (goblin_) {
		goblin_->update(deltaTime);
	}
}
