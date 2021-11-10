#include "../include/Enemy.hpp"
#include "../include/Projectile.hpp"
#include "../include/auxiliary/constants.hpp"
#include <math.h>


Enemy::Enemy(sf::RenderWindow& window, float tileX, float tileY, sf::Time timeUntilSpawn, float speed, int hitPoints) : 
    window_(window),
    tileX_(tileX), 
    tileY_(tileY), 
    direction_(0),
    timeUntilSpawn_(timeUntilSpawn),
    speed_(speed),  
    hitPoints_(hitPoints)
{
    setDirection();
}


void Enemy::update(sf::Time deltaTime)
{
    if (!isSpawned()) {
        timeUntilSpawn_ -= deltaTime;
    } else if (isAlive() && !hasReachedBase()) {
        setDirection();
        move(deltaTime);
    }
}


void Enemy::draw()
{
    // do we need draw method? Is the enemy responsible of drawing itself?
}


void Enemy::setDirection()
{
    direction_ = 0;  // fix this: calculate new direction based on current position and path
}


void Enemy::move(sf::Time deltaTime)
{
    float distance = speed_ * deltaTime.asSeconds();
    float angle = direction_ * DegreesToRadians;
    float deltaX = distance * cosf(angle);
    float deltaY = distance * sinf(angle);
    tileX_ += deltaX;
    tileY_ += deltaY;
}


bool Enemy::isSpawned() const 
{
    return timeUntilSpawn_.asSeconds() <= 0;
}


bool Enemy::isAlive() const
{
    return isSpawned() && hitPoints_ > 0;
}


bool Enemy::hasReachedBase() const
{
    return false;  // fix this: check if enemy is in the base tile
}


void Enemy::hit(int maxDamage)
{
    int halfDamage = maxDamage / 2;
    if (halfDamage == 0) {
        hitPoints_ -= maxDamage;
    } else {
        hitPoints_ -= 1 + halfDamage + rand() % halfDamage;
    }
}


float Enemy::getTileX() const
{
    return tileX_;
}


float Enemy::getTileY() const
{
    return tileY_;
}


float Enemy::getDirection() const
{
    return direction_;
}


int Enemy::getHitPoints() const
{
    return hitPoints_;
}


 // Goblin

 Goblin::Goblin(sf::RenderWindow& window, float tileX, float tileY, sf::Time timeUntilSpawn) :
    Enemy(window, tileX, tileY, timeUntilSpawn, 0.5, 500)
{
}



