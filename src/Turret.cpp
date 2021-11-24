#include "../include/Turret.hpp"
#include "../include/auxiliary/constants.hpp"
#include <math.h>
#include <iostream>
#include <limits>

Turret::Turret(int row, int col, int price, float rateOfFire, float radarRange,
		ResourceHolder<sf::Texture, Textures::ID>& textures, Textures::ID turretBaseStyle, Textures::ID turretStyle) : 
	row_(row), 
	col_(col), 
	price_(price),  
	rateOfFire_(rateOfFire),  
	radarRange_(radarRange),
    currentAngle_(0),
    isAimReady_(false)
{
    // turret base sprite
    turretBaseSprite_.setTexture(textures.get(turretBaseStyle));

    auto imageBounds = turretBaseSprite_.getGlobalBounds();

    turretBaseSprite_.setOrigin(imageBounds.width / 2.f, imageBounds.height / 2.f);
	turretBaseSprite_.setScale(TurretScaler * TileSize / imageBounds.width, TurretScaler * TileSize / imageBounds.height);
	turretBaseSprite_.setPosition(getTileX() * TileSize, getTileY() * TileSize);

    // turret sprite
    turretSprite_.setTexture(textures.get(turretStyle));
    imageBounds = turretSprite_.getGlobalBounds();
    turretSprite_.setOrigin(imageBounds.width / 2.f, imageBounds.height / 2.f);
	turretSprite_.setScale(TurretScaler * TileSize / imageBounds.width, TurretScaler * TileSize / imageBounds.height);
	turretSprite_.setPosition(getTileX() * TileSize, getTileY() * TileSize);
 
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

    turretSprite_.setRotation(currentAngle_ - TurretTextureOffset);

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
    target.draw(turretBaseSprite_, states);
    target.draw(turretSprite_, states);
}


std::shared_ptr<Enemy> Turret::getNearestEnemyInRadar(const EnemyList& enemies)
{
    std::shared_ptr<Enemy> nearest(nullptr);
    float minDistance = std::numeric_limits<float>::max();
    float turretX = getTileX();
    float turretY = getTileY();

    for (auto& enemy : enemies)
	{
        float enemyDistance = Map::calculateDistance(sf::Vector2f(turretX, turretY), enemy->getPosition());

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
        auto targetPos = enemy->getPosition();

        if (estimateEnemyMovement)
        {
            float enemyDistance = Map::calculateDistance(sf::Vector2f(getTileX(), getTileY()), targetPos);
            float flightTime = enemyDistance / projectileSpeed;
            float enemySpeed = enemy->getSpeed();
            float enemyMovement = flightTime * enemySpeed; // not exact but close enough
            float enemyAngle = enemy->getDirection() * DegreesToRadians;

			targetPos += sf::Vector2f(enemyMovement * std::cos(enemyAngle), enemyMovement * std::sin(enemyAngle));
        }

        float maxRotation = deltaTime.asSeconds() * Turrets::rotationSpeed;
        float angle = Map::calculateAngle(sf::Vector2f(getTileX(), getTileY()), targetPos);
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


using namespace Turrets;

sf::Vector2f Turret::getProjectileStartPosition(float barrelPositionAngle)
{
    float radians = (currentAngle_ + barrelPositionAngle) * DegreesToRadians;
    float projectileX = getTileX() + 0.5f * cosf(radians); // x coordinate of the tip of the barrel
    float projectileY = getTileY() + 0.5f * sinf(radians); // y coordinate of the tip of the barrel
    return sf::Vector2f(projectileX, projectileY);
}


// GunTurret 

GunTurret::GunTurret(int row, int col, ResourceHolder<sf::Texture, Textures::ID>& textures)
 : Turret(row, col, Gun::price, Gun::firerate, Gun::radarRange, textures, Textures::ID::GunTurretBase, Textures::ID::GunTurret)
 /* : Turret(row, col, GunTurretPrice, GunTurretRotationSpeed, GunTurretRateOfFire, GunTurretRadarRange, textures, Textures::ID::GunTurretBase, Textures::ID::GunTurret) */
{
}


float GunTurret::rotate(sf::Time deltaTime, const EnemyList& enemies)
{
    return rotateToNearestEnemyInRadar(deltaTime, true, Projectiles::Bullet::speed, enemies);
}


std::vector<std::shared_ptr<Projectile>> GunTurret::shoot()
{
    std::vector<std::shared_ptr<Projectile>> projectiles;

    sf::Vector2f position = getProjectileStartPosition(0.f);
    projectiles.push_back(std::make_shared<Bullet>(Bullet{position, currentAngle_}));

    return projectiles; 
}


// DoubleGunTurret 

DoubleGunTurret::DoubleGunTurret(int row, int col, ResourceHolder<sf::Texture, Textures::ID>& textures)
	: Turret(row, col, DoubleGun::price, DoubleGun::firerate, DoubleGun::radarRange, textures, Textures::ID::DoubleGunTurretBase, Textures::ID::DoubleGunTurret)
{
}


float DoubleGunTurret::rotate(sf::Time deltaTime, const EnemyList& enemies)
{
    return rotateToNearestEnemyInRadar(deltaTime, true, Projectiles::Bullet::speed, enemies);
}


std::vector<std::shared_ptr<Projectile>> DoubleGunTurret::shoot()
{
    std::vector<std::shared_ptr<Projectile>> projectiles;

    for (auto angle : {10.f, -10.f})
    {
        sf::Vector2f position = getProjectileStartPosition(angle);
        projectiles.push_back(std::make_shared<Bullet>(Bullet{position, currentAngle_}));
    }

    return projectiles; 
}


// TripleGunTurret 

TripleGunTurret::TripleGunTurret(int row, int col, ResourceHolder<sf::Texture, Textures::ID>& textures)
 : Turret(row, col, TripleGun::price, TripleGun::firerate, TripleGun::radarRange, textures, Textures::ID::TripleGunTurretBase, Textures::ID::TripleGunTurret)
{
}


float TripleGunTurret::rotate(sf::Time deltaTime, const EnemyList& enemies)
{
    return rotateToNearestEnemyInRadar(deltaTime, true, Projectiles::Bullet::speed, enemies);
}


std::vector<std::shared_ptr<Projectile>> TripleGunTurret::shoot()
{
    std::vector<std::shared_ptr<Projectile>> projectiles;

    for (auto angle : {10.f, 0.f, -10.f})
    {
        sf::Vector2f position = getProjectileStartPosition(angle);
        projectiles.push_back(std::make_shared<Bullet>(Bullet{position, currentAngle_}));
    }

    return projectiles; 
}


// BombTurret 

BombTurret::BombTurret(int row, int col, ResourceHolder<sf::Texture, Textures::ID>& textures)
 : Turret(row, col, Turrets::Bomb::price, Turrets::Bomb::firerate, Turrets::Bomb::radarRange, textures, Textures::ID::BombTurretBase, Textures::ID::BombTurret)
{
}


float BombTurret::rotate(sf::Time deltaTime, const EnemyList& enemies)
{
    return rotateToNearestEnemyInRadar(deltaTime, true, Projectiles::Bomb::speed, enemies);
}


std::vector<std::shared_ptr<Projectile>> BombTurret::shoot()
{
    std::vector<std::shared_ptr<Projectile>> projectiles;

    sf::Vector2f position = getProjectileStartPosition(0.f);
    projectiles.push_back(std::make_shared<::Bomb>(::Bomb{position, currentAngle_}));

    return projectiles; 
}
