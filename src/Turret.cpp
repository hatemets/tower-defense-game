#include "../include/Turret.hpp"

Turret::Turret(sf::RenderWindow& window, int row, int col, int price, 
               float rotationSpeed, float rateOfFire, float projectileRange) : 
    window_(window),
    row_(row), 
    col_(col), 
    price_(price),  
    rotationSpeed_(rotationSpeed),  
    rateOfFire_(rateOfFire),  
    projectileRange_(projectileRange),  
    currentAngle_(rand() % 360) 
{
    nextFire_ = sf::seconds(0);  // ready to shoot immediately 
}


void Turret::update(sf::Time deltaTime)
{
    rotate();
    if (nextFire_ <= deltaTime) {
        if (shoot()) {
            nextFire_ = fireInterval();
        } else {
            nextFire_ = sf::seconds(0);
        }
    } else {
        nextFire_ -= deltaTime;
    }
}


void Turret::draw()
{
    // do we need draw method? Is the turret responsible to draw itself?
}


sf::Time Turret::fireInterval()
{
    return sf::seconds(1 / rateOfFire_);
}