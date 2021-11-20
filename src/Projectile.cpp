#include "../include/Projectile.hpp"
#include "../include/auxiliary/constants.hpp"
#include <math.h>
#include <memory>
#include <algorithm>

Projectile::Projectile(float tileX, float tileY, float direction, float speed, float flightRange, float explosionRange, float maxDamage, bool drawAsVertex)
	: tileX_(tileX),
	tileY_(tileY),
	direction_(direction),
	speed_(speed),
	explosionRange_(explosionRange),
	maxDamage_(maxDamage),
	drawAsVertex_(drawAsVertex)
{
	lifetimeLeft_ = sf::seconds(flightRange / speed);
}

void Projectile::update(sf::Time deltaTime, const EnemyList& enemies)
{
	std::shared_ptr<Enemy> hitEnemy = checkHit(enemies);

	if (hitEnemy)
	{
		lifetimeLeft_ = sf::seconds(0.f);
	}
	else
	{
		flight(deltaTime);
		hitEnemy = checkHit(enemies);

		if (hitEnemy)
		{
			lifetimeLeft_ = sf::seconds(0.f);
		}
		else
		{
			lifetimeLeft_ -= deltaTime;
		}
	}

	if (!isAlive())
	{
		explode(hitEnemy, enemies);
	}
}

void Projectile::drawSelf(sf::RenderTarget &target, sf::RenderStates states) const
{
}

bool Projectile::isAlive() const
{
	return lifetimeLeft_.asSeconds() > 0.f;
}

std::shared_ptr<Enemy> Projectile::checkHit(const EnemyList& enemies)
{
	for (std::shared_ptr<Enemy> enemy : enemies)
	{
		if (Map::isContact(sf::Vector2f(tileX_, tileY_), 0.f, sf::Vector2f(enemy->getTileX(), enemy->getTileY()), enemy->getRadius()))
		{
			return enemy;
		}
	}

	return std::shared_ptr<Enemy>(nullptr);
}

void Projectile::explode(std::shared_ptr<Enemy> hitEnemy, const EnemyList& enemies)
{
	if (hitEnemy)
	{
		hitEnemy->hit(maxDamage_);
	}
	if (explosionRange_ > 0)
	{
		//damage also other enemies in the range
	}
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


// Bullet

Bullet::Bullet(float tileX, float tileY, float direction) : Projectile(tileX, tileY, direction, 5, 5, 0, 50, true)
{
}


