#include "../include/Turret.hpp"
#include "../include/auxiliary/constants.hpp"
#include <math.h>


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
    // rotate
    currentAngle_ += rotate(deltaTime);
    while (currentAngle_ >= 360) {
        currentAngle_ -= 360;
    }
    while (currentAngle_ < 0) {
        currentAngle_ += 360;
    }

    // shoot
    if (nextFire_ <= deltaTime) {
        if (shoot()) {
            nextFire_ = getFireInterval();
        } else {
            nextFire_ = sf::seconds(0);
        }
    } else {
        nextFire_ -= deltaTime;
    }
}


void Turret::draw()
{
    // do we need draw method? Is the turret responsible of drawing itself?
}


void Turret::move(int row, int col)
{
    row_ = row;
    col_ = col;
}


int Turret::getRow() const
{
    return row_;
}


int Turret::getCol() const
{
    return col_;
}  


float Turret::getTileX() const
{
    return row_ + 0.5f;
}  
        

float Turret::getTileY() const
{
    return col_ + 0.5f;
}  

int Turret::getPrice() const
{
    return price_;
}


float Turret::getRotationSpeed() const
{
    return rotationSpeed_;
}


float Turret::getRateOfFire() const
{
    return rateOfFire_;
}


sf::Time Turret::getFireInterval() const
{
    return sf::seconds(1 / rateOfFire_);
}


float Turret::getProjectileRange() const
{
    return projectileRange_;
}


float Turret::getCurrentAngle() const
{
    return currentAngle_;
}


sf::Time Turret::getNextFire() const
{
    return nextFire_;
}


// SimpleTurret 

SimpleTurret::SimpleTurret(sf::RenderWindow& window, int row, int col) : 
    Turret(window, row, col, 10, 91, 5, 5)
{
}


float SimpleTurret::rotate(sf::Time deltaTime)
{
    return deltaTime.asSeconds() * rotationSpeed_; // rotate without aiming
}


bool SimpleTurret::shoot()
{
    return true; // shoot always when possible
}


