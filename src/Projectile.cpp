#include "../include/Projectile.hpp"
#include "../include/auxiliary/constants.hpp"
#include <math.h>


Projectile::Projectile(sf::RenderWindow& window, float row, float col, float direction, float speed, 
                       float flightRange, float explosionRange, float maxDamage) : 
    window_(window),
    row_(row), 
    col_(col), 
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


bool Projectile::isHit()
{
    return false; // cannot be done before we have enemy class
}


void Projectile::flight(sf::Time deltaTime)
{
    float distance = speed_ * deltaTime.asSeconds();
    float angle = direction_ * DegreesToRadians;
    float deltaRow = distance * cosf(angle);
    float deltaCol = distance * sinf(angle);
    row_ += deltaRow;
    col_ += deltaCol;
}


void Projectile::draw()
{
    // do we need draw method? Is the projectile responsible of drawing itself?
}


float Projectile::getRow() const
{
    return row_;
}


float Projectile::getCol() const
{
    return col_;
}


float Projectile::getDirection() const
{
    return direction_;
}