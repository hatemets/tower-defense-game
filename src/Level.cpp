#include "../include/Level.hpp"
#include "../include/BackgroundSprite.hpp"
#include <memory>


Level::Level(sf::RenderWindow& window)
	: Mode(window),
	textures_()
{
	loadTextures();
	createScene();
}


void Level::loadTextures()
{
	textures_.load(Textures::ID::GrassArea, "/home/mark/projects/tower-defense-6/include/images/levelBackground.png");
}


void Level::createScene()
{
	for (std::size_t i = 0; i < static_cast<std::size_t>(Layers::totalCount); ++i)
	{
		auto layerNode = std::make_unique<Node>();

		layers_.push_back(layerNode.get());

		nodeTree_.addChild(std::move(layerNode));
	}


	sf::Texture& backgroundTexture = textures_.get(Textures::ID::GrassArea);
	backgroundTexture.setRepeated(true);

	sf::IntRect bounds(windowBounds_);

	auto background = std::make_unique<BackgroundSprite>(BackgroundSprite{backgroundTexture, bounds});
	background->setPosition(0.f, 0.f);

	std::size_t i = static_cast<std::size_t>(Layers::Background);
	layers_[i]->addChild(std::move(background));
}

void Level::update(sf::Time deltaTime)
{
}
