#include "../include/Turret.hpp"
#include "../include/auxiliary/constants.hpp"
#include <math.h>
#include <iostream>
#include <limits>


Turret::Turret(int row, int col, int price, float rotationSpeed, float rateOfFire, float radarRange, float projectileRange,
               ResourceHolder<sf::Texture, Textures::ID>& textures, Textures::ID turretBaseStyle, Textures::ID turretStyle) : 
    row_(row), 
    col_(col), 
    price_(price),  
    rotationSpeed_(rotationSpeed),  
    rateOfFire_(rateOfFire),  
    radarRange_(radarRange),
    projectileRange_(projectileRange),  
    currentAngle_(0),
    isAimReady_(false)
{
    // turret base sprite
    turretBasePicture_.setTexture(textures.get(turretBaseStyle));
    auto imageBounds = turretBasePicture_.getGlobalBounds();
    turretBasePicture_.setOrigin(imageBounds.width / 2.f, imageBounds.height / 2.f);
	turretBasePicture_.setScale(TileSize / imageBounds.width, TileSize / imageBounds.height);
	turretBasePicture_.setPosition(getTileX() * TileSize, getTileY() * TileSize);

    // turret sprite
    turretPicture_.setTexture(textures.get(turretStyle));
    imageBounds = turretPicture_.getGlobalBounds();
    turretPicture_.setOrigin(imageBounds.width / 2.f, imageBounds.height / 2.f);
	turretPicture_.setScale(TileSize / imageBounds.width, TileSize / imageBounds.height);
	turretPicture_.setPosition(getTileX() * TileSize, getTileY() * TileSize);
 
    nextFire_ = sf::seconds(0);  // ready to shoot immediately 
}


void Turret::update(sf::Time deltaTime, const EnemyList& enemies, ProjectileList& projectiles)
{
    // rotate
    currentAngle_ += rotate(deltaTime, enemies);

    while (currentAngle_ >= 360)
	{
        currentAngle_ -= 360;
    }

    while (currentAngle_ < 0)
	{
        currentAngle_ += 360;
    }

    turretPicture_.setRotation(currentAngle_ - TurretTextureOffset);

	// shoot
	if (nextFire_ <= deltaTime && isAimReady_)
	{
		std::vector<std::shared_ptr<Projectile>> shotProjectiles = shoot();

		if (shotProjectiles.size() > 0)
		{
			for (auto projectile : shotProjectiles)
			{
                // add shot projectiles to the projectile list of the level
				projectiles.push_back(projectile);
			}

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
    target.draw(turretBasePicture_, states);
    target.draw(turretPicture_, states);
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


float Turret::rotateToNearestEnemyInRadar(sf::Time deltaTime, bool estimateEnemyMovement, float projectileSpeed, const EnemyList& enemies)
{
    isAimReady_ = false;

    auto enemy = getNearestEnemyInRadar(enemies);

    if (enemy)
	{
        float targetX = enemy->getTileX();
        float targetY = enemy->getTileY();

        if (estimateEnemyMovement)
        {
            float enemyDistance = Map::calculateDistance(sf::Vector2f(getTileX(), getTileY()), sf::Vector2f(targetX, targetY));
            float flightTime = enemyDistance / projectileSpeed;
            float enemySpeed = enemy->getSpeed();
            float enemyMovement = flightTime * enemySpeed; // not exact but close enough
            float enemyAngle = enemy->getDirection() * DegreesToRadians;
            targetX += enemyMovement * cosf(enemyAngle);
            targetY += enemyMovement * sinf(enemyAngle);
        }

        float maxRotation = deltaTime.asSeconds() * rotationSpeed_;
        float angle = Map::calculateAngle(sf::Vector2f(getTileX(), getTileY()), sf::Vector2f(targetX, targetY));
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
            isAimReady_ = true;
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


sf::Vector2f Turret::getProjectileStartPosition(float barrelPositionAngle)
{
    float radians = (currentAngle_ + barrelPositionAngle) * DegreesToRadians;
    float projectileX = getTileX() + 0.5f * cosf(radians); // x coordinate of the tip of the barrel
    float projectileY = getTileY() + 0.5f * sinf(radians); // y coordinate of the tip of the barrel
    return sf::Vector2f(projectileX, projectileY);
}


// GunTurret 

GunTurret::GunTurret(int row, int col, ResourceHolder<sf::Texture, Textures::ID>& textures)
 : Turret(row, col, GunTurretPrice, GunTurretRotationSpeed, GunTurretRateOfFire, GunTurretRadarRange, GunTurretProjectileRange, textures, Textures::ID::GunTurretBase, Textures::ID::GunTurret)
{
}


float GunTurret::rotate(sf::Time deltaTime, const EnemyList& enemies)
{
    return rotateToNearestEnemyInRadar(deltaTime, true, BulletSpeed, enemies);
}


std::vector<std::shared_ptr<Projectile>> GunTurret::shoot()
{
    std::vector<std::shared_ptr<Projectile>> projectiles;
    sf::Vector2f position = getProjectileStartPosition(0.f);
    projectiles.push_back(std::make_shared<Projectile>(Bullet{position.x, position.y, currentAngle_}));
    return projectiles; 
}


// DoubleGunTurret 

DoubleGunTurret::DoubleGunTurret(int row, int col, ResourceHolder<sf::Texture, Textures::ID>& textures)
 : Turret(row, col, DoubleGunTurretPrice, DoubleGunTurretRotationSpeed, DoubleGunTurretRateOfFire, DoubleGunTurretRadarRange, DoubleGunTurretProjectileRange, textures, Textures::ID::DoubleGunTurretBase, Textures::ID::DoubleGunTurret)
{
}


float DoubleGunTurret::rotate(sf::Time deltaTime, const EnemyList& enemies)
{
    return rotateToNearestEnemyInRadar(deltaTime, true, BulletSpeed, enemies);
}


std::vector<std::shared_ptr<Projectile>> DoubleGunTurret::shoot()
{
    std::vector<std::shared_ptr<Projectile>> projectiles;
    for (auto angle: {10.f, -10.f})
    {
        sf::Vector2f position = getProjectileStartPosition(angle);
        projectiles.push_back(std::make_shared<Projectile>(Bullet{position.x, position.y, currentAngle_}));
    }
    return projectiles; 
}


// TripleGunTurret 

TripleGunTurret::TripleGunTurret(int row, int col, ResourceHolder<sf::Texture, Textures::ID>& textures)
 : Turret(row, col, TripleGunTurretPrice, TripleGunTurretRotationSpeed, TripleGunTurretRateOfFire, TripleGunTurretRadarRange, TripleGunTurretProjectileRange, textures, Textures::ID::TripleGunTurretBase, Textures::ID::TripleGunTurret)
{
}


float TripleGunTurret::rotate(sf::Time deltaTime, const EnemyList& enemies)
{
    return rotateToNearestEnemyInRadar(deltaTime, true, BulletSpeed, enemies);
}


std::vector<std::shared_ptr<Projectile>> TripleGunTurret::shoot()
{
    std::vector<std::shared_ptr<Projectile>> projectiles;
    for (auto angle: {10.f, 0.f, -10.f})
    {
        sf::Vector2f position = getProjectileStartPosition(angle);
        projectiles.push_back(std::make_shared<Projectile>(Bullet{position.x, position.y, currentAngle_}));
    }
    return projectiles; 
}