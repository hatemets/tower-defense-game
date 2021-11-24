#include "../include/Enemy.hpp"
#include "../include/Projectile.hpp"
#include "../include/Map.hpp"
#include "../include/auxiliary/constants.hpp"
#include <math.h>

Enemy::Enemy(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd, float speed, int hitPoints, float radius)
    : pathIterator_(pathBegin),
      pathEnd_(pathEnd),
	  position_(pathBegin->second + 0.5f, pathBegin->first + 0.5f),
      direction_(0),
      speed_(speed),
      hitPoints_(hitPoints),
	  radius_(radius)
{
    picture_.setSize(sf::Vector2f(TileSize / 2.f, TileSize / 2.f));
    picture_.setOrigin(TileSize / 4.f, TileSize / 4.f);
    picture_.setFillColor(sf::Color::Green);

    update(sf::seconds(0));
}

void Enemy::update(sf::Time deltaTime)
{
    if (isAlive() && !hasReachedBase())
    {
        move(deltaTime);

        auto target = *pathIterator_;

        float targetX = target.second + 0.5f;
        float targetY = target.first + 0.5f;

        if (Map::isContact(position_, 0.f, sf::Vector2f(targetX, targetY), 0.25f))
        {
            pathIterator_++;
            setDirection();
            // picture_.setRotation(direction_);
        }

        /* picture_.setPosition((float)TileSize * position_); */
        picture_.setPosition(position_.x * TileSize, position_.y * TileSize);
    }
}

void Enemy::drawSelf(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(picture_, states);
}

void Enemy::setDirection()
{
    if (!hasReachedBase())
    {
        auto target = *pathIterator_;
        float targetX = target.second + 0.5f;
        float targetY = target.first + 0.5f;
        direction_ = Map::calculateAngle(position_, sf::Vector2f(targetX, targetY));
    }
}

void Enemy::move(sf::Time deltaTime)
{
    float distance = speed_ * deltaTime.asSeconds();
    if (distance != 0)
    {
        float angle = direction_ * DegreesToRadians;
        float deltaX = distance * std::cos(angle);
        float deltaY = distance * std::sin(angle);

		position_ = sf::Vector2f(position_.x + deltaX, position_.y + deltaY);
    }
}

bool Enemy::isAlive() const
{
    return hitPoints_ > 0;
}

bool Enemy::hasReachedBase() const
{
    return pathIterator_ == pathEnd_;
}

void Enemy::hit(int maxDamage)
{
    int halfDamage = maxDamage / 2;

    if (halfDamage == 0)
    {
        hitPoints_ -= maxDamage;
    }
    else
    {
        hitPoints_ -= 1 + halfDamage + rand() % halfDamage;
    }
}

// Goblin

Goblin::Goblin(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd)
    : Enemy(pathBegin, pathEnd, Enemies::Goblin::goblinSpeed, Enemies::Goblin::hitPoints)
{
}
