#include "../include/LevelMenu.hpp"
#include "../include/BackgroundSprite.hpp"
#include "../include/auxiliary/constants.hpp"
#include <memory>
#include <iostream>
#include <sstream>

LevelMenu::LevelMenu(sf::RenderWindow& window, std::shared_ptr<GameData> gameData)
	: Mode(window),
	textures_(),
	gameData_(gameData)
{
	loadResources();
	createScene();
}


void LevelMenu::loadResources()
{
	textures_.load(Textures::ID::LevelMenuBackground, "./include/images/LevelMenuBackground.png");

	buttonShapes_.load(Buttons::ID::Home);
	buttonShapes_.load(Buttons::ID::CheatMode);
	buttonShapes_.load(Buttons::ID::Level1);
	buttonShapes_.load(Buttons::ID::Level2);
	buttonShapes_.load(Buttons::ID::Level3);
	buttonShapes_.load(Buttons::ID::Level4);
	buttonShapes_.load(Buttons::ID::Level5);
	buttonShapes_.load(Buttons::ID::Level6);
	buttonShapes_.load(Buttons::ID::Level7);
	buttonShapes_.load(Buttons::ID::Level8);
	buttonShapes_.load(Buttons::ID::Level9);
	buttonShapes_.load(Buttons::ID::Start);
}


void LevelMenu::createScene()
{
	initializePointers(static_cast<std::size_t>(Layers::TotalCount));
	addBackground();
	addButtons();
}


void LevelMenu::addBackground()
{
	// Set the background for the menu
	sf::Texture& backgroundTexture = textures_.get(Textures::ID::LevelMenuBackground);
	/* backgroundTexture.setRepeated(true); */

	/* sf::IntRect bounds(windowBounds_); */

	auto background = std::make_unique<BackgroundSprite>(BackgroundSprite{backgroundTexture});
	background->setPosition(WindowWidth / 2.f, WindowHeight/ 2.f);
	layers_[static_cast<std::size_t>(Layers::Background)]->addChild(std::move(background));
}


void LevelMenu::addButtons()
{
	const float buttonMargin = 10.f;
	int maxOpenLevel = gameData_->getMaxOpenLevel();
	int buttonCount = 2 + maxOpenLevel;

	if (CheatModeEnabled)
	{
		buttonCount += 1;
	}
	
	/* auto startButton = std::make_unique<Button>("New Game", fonts_, buttonShapes_, Buttons::ID::Start); */
	/* startButton->setPosition(WindowWidth / 2.f, WindowHeight / 2.f - ((buttonCount - 1) / 2.f) * (startButton->getButton().getSize().y + buttonMargin)); */
	/* buttons_.push_back(startButton.get()); */
	/* layers_[static_cast<std::size_t>(Layers::Buttons)]->addChild(std::move(startButton)); */

	if (CheatModeEnabled)
	{
		auto cheatButton = std::make_unique<Button>("Cheat Mode", fonts_, buttonShapes_, Buttons::ID::CheatMode);
		cheatButton->setPosition(WindowWidth / 2.f, WindowHeight / 2.f + 130.f);
		buttons_.push_back(cheatButton.get());
		layers_[static_cast<std::size_t>(Layers::Buttons)]->addChild(std::move(cheatButton));
	}

	for (int level = 1; level <= TotalLevels; level++)
	{
		std::stringstream ss;
		ss << "Level " << level;
		Buttons::ID levelButtonId = static_cast<Buttons::ID>(static_cast<int>(Buttons::ID::Level1) + level - 1);

		auto levelButton = std::make_unique<Button>(ss.str(), fonts_, buttonShapes_, levelButtonId, 8);

        auto size = levelButton->getButton().getSize();

        // Margin between the buttons
        const float margin = 30.f;

        // The offset position for the level buttons (the position of the top mid button)
        sf::Vector2f pos(WindowWidth / 2.f, WindowHeight / 2.f - 70.f);

        // Two rows for level buttons
        float y = (level % 2 == 1) ? pos.y : (pos.y + size.y + margin);
        float x{};

        switch (level)
        {
            case 1: case 2:
                x = pos.x - size.x - margin;
                break;
            case 3: case 4:
                x = pos.x;
                break;
            case 5: case 6:
                x = pos.x + size.x + margin;
                break;
            default:
                throw std::runtime_error("Level button error");
        }

        sf::Vector2f finalPosition(x, y);

        levelButton->setPosition(finalPosition.x, finalPosition.y);
        buttons_.push_back(levelButton.get());

		layers_[static_cast<std::size_t>(Layers::Buttons)]->addChild(std::move(levelButton));
	}

	// Home button
	auto homeButton = std::make_unique<Button>("X", fonts_, buttonShapes_, Buttons::ID::Home, 4);
	auto homeButtonSize = homeButton->getButton().getSize();
	homeButton->setPosition(WindowWidth - homeButtonSize.x / 2.f, homeButtonSize.y / 2.f - ButtonMargin);
	buttons_.push_back(homeButton.get());
	layers_[static_cast<std::size_t>(Layers::Buttons)]->addChild(std::move(homeButton));
}

void LevelMenu::update(sf::Time deltaTime)
{
}
