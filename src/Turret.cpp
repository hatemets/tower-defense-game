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
    rotate(deltaTime);
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


SimpleTurret::SimpleTurret(sf::RenderWindow& window, int row, int col) : 
    Turret(window, row, col, Price, RotationSpeed, RateOfFire, ProjectileRange)
{
}


void SimpleTurret::rotate(sf::Time deltaTime)
{
    currentAngle_ += deltaTime.asSeconds() * rotationSpeed_; // rotate without aiming
    while (currentAngle_ >= 360) {
        currentAngle_ -= 360;
    }
}


bool SimpleTurret::shoot()
{
    return true; // shoot always when possible
}


