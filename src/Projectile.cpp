#include "../include/Projectile.hpp"
#include "../include/auxiliary/constants.hpp"
#include <math.h>


Projectile::Projectile(sf::RenderWindow& window, float tileX, float tileY, float direction, float speed, 
                       float flightRange, float explosionRange, float maxDamage) : 
    window_(window),
    tileX_(tileX), 
    tileY_(tileY), 
    direction_(direction),  
    speed_(speed),  
    explosionRange_(explosionRange),  
    maxDamage_(maxDamage) 
{
    lifetimeLeft_ = sf::seconds(flightRange / speed);
}


void Projectile::update(sf::Time deltaTime)
{
    if (isHit()) {
        // explode projectile, damage enemies
    } else {
        flight(deltaTime);
        if (isHit()) {
            // explode projectile, damage enemies
        } else {
            lifetimeLeft_ -= deltaTime;
            if (lifetimeLeft_.asSeconds() <= 0) {
                // rewmove projectile
            }
        }
    }
}


void Projectile::draw()
{
    // do we need draw method? Is the projectile responsible of drawing itself?
}


bool Projectile::isHit()
{
    return false; // cannot be done before we have enemy class
}


void Projectile::flight(sf::Time deltaTime)
{
    float distance = speed_ * deltaTime.asSeconds();
    float angle = direction_ * DegreesToRadians;
    float deltaX = distance * cosf(angle);
    float deltaY = distance * sinf(angle);
    tileX_ += deltaX;
    tileY_ += deltaY;
}


float Projectile::getTileX() const
{
    return tileX_;
}


float Projectile::getTileY() const
{
    return tileY_;
}


float Projectile::getDirection() const
{
    return direction_;
}


// Bullet

Bullet::Bullet(sf::RenderWindow& window, float tileX, float tileY, float direction) :
    Projectile(window, tileX, tileY, direction, 5, 5, 0, 50)
{
}
