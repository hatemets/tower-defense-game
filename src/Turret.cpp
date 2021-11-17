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


void Turret::update(sf::Time deltaTime, const EnemyList& enemies)
{
    // rotate
    currentAngle_ += rotate(deltaTime, enemies);
    // std::cout << currentAngle_ << std::endl;
    while (currentAngle_ >= 360)
	{
        currentAngle_ -= 360;
    }

    while (currentAngle_ < 0)
	{
        currentAngle_ += 360;
    }

    picture_.setRotation(currentAngle_);

	// shoot
	if (nextFire_ <= deltaTime)
	{
		if (shoot())
		{
			nextFire_ = getFireInterval();
		}
		else
		{
			nextFire_ = sf::seconds(0);
		}
	}
	else
	{
		nextFire_ -= deltaTime;
	}
}


void Turret::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(picture_, states);
}


std::shared_ptr<Enemy> Turret::getNearestEnemyInRadar(const EnemyList& enemies)
{
    std::shared_ptr<Enemy> nearest(nullptr);
    float minDistance = std::numeric_limits<float>::max();
    float turretX = getTileX();
    float turretY = getTileY();

    for (auto& enemy : enemies)
	{
        float enemyDistance = Map::calculateDistance(sf::Vector2f(turretX, turretY), sf::Vector2f(enemy->getTileX(), enemy->getTileY()));

        if (enemyDistance < minDistance && enemyDistance <= radarRange_)
		{
            minDistance = enemyDistance;
            nearest = enemy;
        }
    }

    return nearest;
}


float Turret::rotateToNearestEnemyInRadar(sf::Time deltaTime, const EnemyList& enemies)
{
    auto target = getNearestEnemyInRadar(enemies);

    if (target)
	{
        float maxRotation = deltaTime.asSeconds() * rotationSpeed_;
        float angle = Map::calculateAngle(sf::Vector2f(getTileX(), getTileY()), sf::Vector2f(target->getTileX(), target->getTileY()));
        float neededRotation = angle - currentAngle_;

        while (neededRotation > 180.f)
		{
            neededRotation -= 360.f;
		} 

		while (neededRotation < -180.f)
		{
			neededRotation += 360.f;
		}

		if ( abs(neededRotation) <= maxRotation )
		{
			return neededRotation;
		}
		else if (neededRotation > 0)
		{
			return maxRotation;
		}
		else
		{
			return -maxRotation;
		}
    }

    return 0.f;
}




// SimpleTurret 

SimpleTurret::SimpleTurret(int row, int col) : 
    Turret(row, col, 10, 91, 5, 5, 5)
{
}


float SimpleTurret::rotate(sf::Time deltaTime, const EnemyList& enemies)
{
    return deltaTime.asSeconds() * rotationSpeed_; // rotate without aiming
}


bool SimpleTurret::shoot()
{
    return true; // shoot always when possible
}


// GunTurret 

GunTurret::GunTurret(int row, int col) : 
	// TODO: Remove hardcoded values
    Turret(row, col, 10, 91, 5, 5, 5)
{
}


float GunTurret::rotate(sf::Time deltaTime, const EnemyList& enemies)
{
    return rotateToNearestEnemyInRadar(deltaTime, enemies);
}


bool GunTurret::shoot()
{
    return true; // shoot always when possible
}
