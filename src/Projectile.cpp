#include "../include/Projectile.hpp"
#include "../include/auxiliary/constants.hpp"
#include <math.h>
#include <memory>
#include <algorithm>

Projectile::Projectile(float tileX, float tileY, float direction, float speed, float flightRange, float explosionRange, float maxDamage)
	: tileX_(tileX),
	tileY_(tileY),
	direction_(direction),
	speed_(speed),
	explosionRange_(explosionRange),
	maxDamage_(maxDamage)
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

void Projectile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
}

bool Projectile::isAlive() const
{
	return lifetimeLeft_.asSeconds() > 0.f;
}

std::shared_ptr<Enemy> Projectile::checkHit(const EnemyList& enemies)
{
	for (std::shared_ptr<Enemy> enemy : enemies->getList())
	{
		if (Map::isContact(tileX_, tileY_, 0.f, enemy->getTileX(), enemy->getTileY(), enemy->getRadius()))
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

float Projectile::getTileX() const
{
	return tileX_;
}

float Projectile::getTileY() const
{
	return tileY_;
}

float Projectile::getDirection() const
{
	return direction_;
}

// Bullet

Bullet::Bullet(float tileX, float tileY, float direction) : Projectile(tileX, tileY, direction, 5, 5, 0, 50)
{
}

// Projectiles

Projectiles::Projectiles(const EnemyList& enemies)
	: enemies_(enemies),
	bulletVertices_(sf::Points, 0)
{
}

void Projectiles::update(sf::Time deltaTime)
{
	// remove outdated bullets and other projectiles
	bullets_.erase(std::remove_if(bullets_.begin(), bullets_.end(),
				[](const std::shared_ptr<Bullet> &bullet)
				{
				return !bullet->isAlive();
				}),
			bullets_.end());
	otherProjectiles_.erase(std::remove_if(otherProjectiles_.begin(), otherProjectiles_.end(),
				[](const std::shared_ptr<Projectile> &projectile)
				{
				return !projectile->isAlive();
				}),
			otherProjectiles_.end());

	for (auto bullet : bullets_)
	{
		bullet->update(deltaTime, enemies_);
	}
	for (auto projectile : otherProjectiles_)
	{
		projectile->update(deltaTime, enemies_);
	}

	bulletVertices_.resize(bullets_.size());
	int i = 0;
	for (auto bullet : bullets_)
	{
		bulletVertices_[i].position = sf::Vector2f(bullet->getTileX() * TileSize, bullet->getTileY() * TileSize);
		bulletVertices_[i].color = sf::Color::White;
		i++;
	}
}

void Projectiles::add(std::shared_ptr<Projectile> projectile)
{
	std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(projectile);

	if (bullet)
	{
		bullets_.push_back(bullet);
	}
	else
	{
		otherProjectiles_.push_back(projectile);
	}
}

void Projectiles::drawSelf(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (bulletVertices_.getVertexCount() > 0)
	{
		target.draw(bulletVertices_, states);
	}

	for (auto projectile : otherProjectiles_)
	{
		projectile->draw(target, states);
	}
}
