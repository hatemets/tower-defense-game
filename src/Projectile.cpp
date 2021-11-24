#include "../include/Projectile.hpp"
#include "../include/auxiliary/constants.hpp"
#include <math.h>
#include <memory>
#include <algorithm>

Projectile::Projectile(sf::Vector2f position, float direction, float speed, float flightRange, int maxDamage, bool drawAsVertex, float explosionRadius)
	: position_(position),
	direction_(direction),
	speed_(speed),
	explosionRadius_(explosionRadius),
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
	// override needed only if shape/sprite used
}

bool Projectile::isAlive() const
{
	return lifetimeLeft_.asSeconds() > 0.f;
}

std::shared_ptr<Enemy> Projectile::checkHit(const EnemyList& enemies)
{
	for (std::shared_ptr<Enemy> enemy : enemies)
	{
		if (Map::isContact(position_, 0.f, enemy->getPosition(), enemy->getRadius()))
		{
			return enemy;
		}
	}

	return std::shared_ptr<Enemy>(nullptr);
}

EnemyList Projectile::getEnemiesInExplosion(const EnemyList &enemies)
{
	EnemyList enemiesInExplosion;

	if (explosionRadius_ > 0.f)
	{
		sf::Vector2f projectilePosition(position_);

		for (auto &enemy : enemies)
		{
			float enemyDistance = Map::calculateDistance(projectilePosition, enemy->getPosition());

			if (enemyDistance <= explosionRadius_)
			{
				enemiesInExplosion.push_back(enemy);
			}
		}
	}

	return enemiesInExplosion;
}

void Projectile::explode(std::shared_ptr<Enemy> hitEnemy, const EnemyList& enemies)
{
	if (explosionRadius_ == 0 && hitEnemy)
	{
		hitEnemy->hit(maxDamage_); // damage only the hit enemy
	}
	else if (explosionRadius_ > 0)
	{
		//damage all enemies in the range
		for (auto enemy : getEnemiesInExplosion(enemies)) {
			enemy->hit(maxDamage_);
		}
	}
}

void Projectile::flight(sf::Time deltaTime)
{
	float distance = speed_ * deltaTime.asSeconds();
	float angle = direction_ * DegreesToRadians;
	float deltaX = distance * std::cos(angle);
	float deltaY = distance * std::sin(angle);

	position_ += sf::Vector2f(deltaX, deltaY);
}


// Bullet

Bullet::Bullet(sf::Vector2f position, float direction) : Projectile(position, direction, Projectiles::Bullet::speed, Projectiles::Bullet::range, Projectiles::Bullet::damage, true)
{
}


// Bomb

Bomb::Bomb(sf::Vector2f position, float direction) : Projectile(position, direction, Projectiles::Bomb::speed, Projectiles::Bomb::range, Projectiles::Bomb::damage, false, Projectiles::Bomb::explosionRadius)
{
	const float divider = 1.f / Projectiles::Bomb::size;
	const float radius = TileSize / divider;

	picture_.setRadius(radius);
    picture_.setOrigin(radius, radius);
    picture_.setFillColor(sf::Color::Black);
}

void Bomb::update(sf::Time deltaTime, const EnemyList& enemies) 
{
	Projectile::update(deltaTime, enemies);
	picture_.setPosition((float)TileSize * position_);
}

void Bomb::drawSelf(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(picture_, states);
}
