#include "../include/World.hpp"

World::World(sf::RenderWindow& window)
    : window_(window),
      currentState_(States::Menu),
      currentLevel_(nullptr)
{   
    // load levels and activate the first one
    std::shared_ptr<Level> testLevel(new Level(window, "Test Level"));
    levels_.push_back(testLevel);
    currentLevel_ = testLevel;
}

void World::update(sf::Time deltaTime) 
{
    if (currentLevel_) {
        currentLevel_->update(deltaTime);
    }
}

void World::draw()
{
    if (currentLevel_) {
        currentLevel_->draw();
    }
}