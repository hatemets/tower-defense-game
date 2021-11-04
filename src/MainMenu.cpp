#include "../include/MainMenu.hpp"
#include "../include/BackgroundTile.hpp"
#include <memory>

MainMenu::MainMenu(sf::RenderWindow& window)
	: Mode(window),
	textures_()
{
	loadTextures();
	createScene();
}


void MainMenu::loadTextures()
{
	// TODO:
	// Load buttons
}


void MainMenu::createScene()
{
	for (std::size_t i = 0; i < static_cast<std::size_t>(Layers::totalCount); ++i)
	{
		std::unique_ptr<Node> layerNode = std::make_unique<Node>();

		layers_.push_back(layerNode.get());

		// Move (NOT copy) the node as a child to the node tree structure
		nodeTree_.addChild(std::move(layerNode));
	}


	// TODO: Use the resource manager
	sf::Texture bgtxt;
	bgtxt.loadFromFile("/home/mark/projects/tower-defense-6/include/images/background1.jpg");
	bgtxt.setRepeated(true);

	sf::IntRect bounds{0, 0, static_cast<int>(window_.getSize().x), static_cast<int>(window_.getSize().y)};

	auto background = std::make_unique<BackgroundTile>(BackgroundTile{bgtxt, bounds});
	background->setPosition(0.f, 0.f);

	int i = static_cast<std::size_t>(Layers::Background);
	layers_[i]->addChild(std::move(background));
}

/* void MainMenu::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const */
/* { */
/* 	target.draw(nodeTree_, states); */
/* } */

void MainMenu::update(sf::Time deltaTime)
{
}
