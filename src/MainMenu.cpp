#include "../include/MainMenu.hpp"
#include "../include/BackgroundSprite.hpp"
#include <memory>

MainMenu::MainMenu(sf::RenderWindow& window)
	: Mode(window),
	textures_()
{
	loadResources();
	createScene();
}


void MainMenu::loadResources()
{
	textures_.load(Resources::ID::GrassArea, "/home/mark/projects/tower-defense-6/include/images/background1.jpg");
}


void MainMenu::createScene()
{
	for (std::size_t i = 0; i < static_cast<std::size_t>(Layers::totalCount); ++i)
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
}

void MainMenu::update(sf::Time deltaTime)
{
}
