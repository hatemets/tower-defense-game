#include "../include/Turret.hpp"
#include "../include/auxiliary/constants.hpp"
#include <math.h>
#include <iostream>
#include <limits>


Turret::Turret(int row, int col, int price, float rotationSpeed, float rateOfFire, float radarRange, float projectileRange) : 
    row_(row), 
    col_(col), 
    price_(price),  
    rotationSpeed_(rotationSpeed),  
    rateOfFire_(rateOfFire),  
    radarRange_(radarRange),
    projectileRange_(projectileRange),  
    currentAngle_(0) 
{
    picture_.setPosition(getTileX() * TileSize, getTileY() * TileSize);
    picture_.setSize(sf::Vector2f(TileSize / 1.5f, TileSize / 5.f));
    picture_.setOrigin(0.f, TileSize / 10.f);
    picture_.setFillColor(sf::Color::Black);

    nextFire_ = sf::seconds(0);  // ready to shoot immediately 
}


void Turret::update(sf::Time deltaTime, Enemies* enemies)
{
    // rotate
    currentAngle_ += rotate(deltaTime, enemies);
    // std::cout << currentAngle_ << std::endl;
    while (currentAngle_ >= 360) {
        currentAngle_ -= 360;
    }
    while (currentAngle_ < 0) {
        currentAngle_ += 360;
    }

    picture_.setRotation(currentAngle_);

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


void Turret::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(picture_, states);
}


std::shared_ptr<Enemy> Turret::getNearestEnemyInRadar(Enemies* enemies)
{
    std::shared_ptr<Enemy> nearest(nullptr);
    float minDistance = std::numeric_limits<float>::max();
    float turretX = getTileX();
    float turretY = getTileY();
    for (auto enemy : enemies->getList()) {
        float enemyDistance = Map::calculateDistance(turretX, turretY, enemy->getTileX(), enemy->getTileY());
        if (enemyDistance < minDistance && enemyDistance <= radarRange_) {
            minDistance = enemyDistance;
            nearest = enemy;
        }
    }
    return nearest;
}


float Turret::rotateToNearestEnemyInRadar(sf::Time deltaTime, Enemies* enemies)
{
    auto target = getNearestEnemyInRadar(enemies);
    if (target) {
        float maxRotation = deltaTime.asSeconds() * rotationSpeed_;
        float angle = Map::calculateAngle(getTileX(), getTileY(), target->getTileX(), target->getTileY());
        float neededRotation = angle - currentAngle_;
        while (neededRotation > 180.f) {
            neededRotation -= 360.f;
        } 
        while (neededRotation < -180.f) {
            neededRotation += 360.f;
        }
        if ( abs(neededRotation) <= maxRotation ) {
            return neededRotation;
        } else if (neededRotation > 0) {
            return maxRotation;
        } else {
            return -maxRotation;
        }
    }
    return 0.f;
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


float Turret::getRadarRange() const
{
    return radarRange_;
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

SimpleTurret::SimpleTurret(int row, int col) : 
    Turret(row, col, 10, 91, 5, 5, 5)
{
}


float SimpleTurret::rotate(sf::Time deltaTime, Enemies* enemies)
{
    return deltaTime.asSeconds() * rotationSpeed_; // rotate without aiming
}


bool SimpleTurret::shoot()
{
    return true; // shoot always when possible
}


// GunTurret 

GunTurret::GunTurret(int row, int col) : 
    Turret(row, col, 10, 91, 5, 5, 5)
{
}


float GunTurret::rotate(sf::Time deltaTime, Enemies* enemies)
{
    return rotateToNearestEnemyInRadar(deltaTime, enemies);
}


bool GunTurret::shoot()
{
    return true; // shoot always when possible
}


// Turrets

Turrets::Turrets(Enemies *enemies)
    : enemies_(enemies)
{
}

void Turrets::update(sf::Time deltaTime)
{
    for (auto turret : turrets_)
    {
        turret->update(deltaTime, enemies_);
    }
}


void Turrets::add(std::shared_ptr<Turret> turret)
{
    turrets_.push_back(turret);
}


const std::list<std::shared_ptr<Turret>> &Turrets::getList() const
{
    return turrets_;
}


void Turrets::drawSelf(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto turret : turrets_)
    {
        turret->drawSelf(target, states);
    }
}

