#include "../include/Projectile.hpp"
#include "../include/auxiliary/constants.hpp"
#include <math.h>
#include <memory>
#include <algorithm>

Projectile::Projectile(sf::Vector2f position, float direction, float speed, float flightRange, int maxDamage, float size, float explosionRadius)
	: position_(position),
	  direction_(direction),
	  speed_(speed),
	  explosionRadius_(explosionRadius),
	  maxDamage_(maxDamage),
	  size_(size)
{
	lifetimeLeft_ = sf::seconds(flightRange / speed);
}


void Projectile::update(sf::Time deltaTime, const EnemyList &enemies)
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


std::shared_ptr<Enemy> Projectile::checkHit(const EnemyList &enemies)
{
	for (std::shared_ptr<Enemy> enemy : enemies)
	{
		if (Map::isContact(position_, getRadius(), enemy->getPosition(), enemy->getRadius()))
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


void Projectile::explode(std::shared_ptr<Enemy> hitEnemy, const EnemyList &enemies)
{
	if (explosionRadius_ == 0 && hitEnemy)
	{
		hitEnemy->hit(maxDamage_); // damage only the hit enemy
	}
	else if (explosionRadius_ > 0)
	{
		//damage all enemies in the range
		for (auto enemy : getEnemiesInExplosion(enemies))
		{
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

Bullet::Bullet(sf::Vector2f position, float direction)
	: Projectile(position, direction, Projectiles::Bullet::speed, Projectiles::Bullet::range, Projectiles::Bullet::damage, Projectiles::Bullet::size)
{
	if (!drawAsVertex())
	{
		const float radius = getRadius() * TileSize;
		picture_.setRadius(radius);
		picture_.setOrigin(radius, radius);
		picture_.setFillColor(sf::Color::White);
	}
}


void Bullet::update(sf::Time deltaTime, const EnemyList &enemies)
{
	if (!drawAsVertex())
	{
		Projectile::update(deltaTime, enemies);
		picture_.setPosition((float)TileSize * position_);
	}
}


void Bullet::drawSelf(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (!drawAsVertex())
	{
		target.draw(picture_, states);
	}
}


// Bomb

Bomb::Bomb(sf::Vector2f position, float direction)
	: Projectile(position, direction, Projectiles::Bomb::speed, Projectiles::Bomb::range, Projectiles::Bomb::damage, Projectiles::Bomb::size, Projectiles::Bomb::explosionRadius)
{
	const float radius = getRadius() * TileSize;
	picture_.setRadius(radius);
	picture_.setOrigin(radius, radius);
	picture_.setFillColor(sf::Color::Black);
}


void Bomb::update(sf::Time deltaTime, const EnemyList &enemies)
{
	Projectile::update(deltaTime, enemies);
	picture_.setPosition((float)TileSize * position_);
}


void Bomb::drawSelf(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(picture_, states);
}


// Missile

Missile::Missile(sf::Vector2f position, float direction, std::shared_ptr<Enemy> target, ResourceHolder<sf::Texture, Textures::ID> &textures)
	: Projectile(position, direction, Projectiles::Missile::speed, Projectiles::Missile::range, Projectiles::Missile::damage, Projectiles::Missile::size, Projectiles::Missile::explosionRadius),
	  target_(target)
{
	sprite_.setTexture(textures.get(Textures::ID::Missile));
	auto imageBounds = sprite_.getGlobalBounds();
	sprite_.setOrigin(imageBounds.width / 2.f, imageBounds.height / 2.f);
	sprite_.setScale(TurretScaler * TileSize / imageBounds.width, TurretScaler * TileSize / imageBounds.height);
	sprite_.setPosition((float)TileSize * position_);
}


void Missile::update(sf::Time deltaTime, const EnemyList &enemies)
{
	if (target_ && target_->isAlive())
	{
		direction_ = Map::calculateAngle(position_, target_->getPosition());
	}
	Projectile::update(deltaTime, enemies);
	sprite_.setRotation(direction_ - TurretTextureOffset);
	sprite_.setPosition((float)TileSize * position_);
}


void Missile::drawSelf(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}
