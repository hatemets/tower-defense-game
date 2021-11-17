#include "../include/Enemy.hpp"
#include "../include/Projectile.hpp"
#include "../include/Map.hpp"
#include "../include/auxiliary/constants.hpp"
#include <math.h>

Enemy::Enemy(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd, float speed, int hitPoints)
    : pathIterator_(pathBegin),
      pathEnd_(pathEnd),
      tileX_(pathBegin->second + 0.5f),
      tileY_(pathBegin->first + 0.5f),
      direction_(0),
      speed_(speed),
      hitPoints_(hitPoints)
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

        if (Map::isContact(sf::Vector2f(tileX_, tileY_), 0.f, sf::Vector2f(targetX, targetY), 0.25f))
        {
            pathIterator_++;
            setDirection();
            // picture_.setRotation(direction_);
        }

        picture_.setPosition(tileX_ * TileSize, tileY_ * TileSize);
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
        direction_ = Map::calculateAngle(sf::Vector2f(tileX_, tileY_), sf::Vector2f(targetX, targetY));
    }
}

void Enemy::move(sf::Time deltaTime)
{
    float distance = speed_ * deltaTime.asSeconds();
    if (distance != 0)
    {
        float angle = direction_ * DegreesToRadians;
        float deltaX = distance * cosf(angle);
        float deltaY = distance * sinf(angle);
        tileX_ += deltaX;
        tileY_ += deltaY;
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
    : Enemy(pathBegin, pathEnd, 1.5, 500)
{
}

// Enemies

Enemies::Enemies(Map *map, sf::Time minSpawnInterval, sf::Time maxSpawnInterval)
    : map_(map),
      minSpawnInterval_(minSpawnInterval),
      maxSpawnInterval_(maxSpawnInterval),
      nextSpawn_(sf::seconds(1))
{
}

void Enemies::update(sf::Time deltaTime)
{
    enemies_.erase(std::remove_if(enemies_.begin(), enemies_.end(),
                                  [](const std::shared_ptr<Enemy> &enemy)
                                  {
                                      return !enemy->isAlive() || enemy->hasReachedBase();
                                  }),
                   enemies_.end());

    for (auto enemy : enemies_)
    {
        enemy->update(deltaTime);
    }

    nextSpawn_ -= deltaTime;
    if (nextSpawn_.asSeconds() <= 0)
    {
        sf::Time timeDiff = maxSpawnInterval_ - minSpawnInterval_;
        if (timeDiff.asMilliseconds() > 1)
        {
            sf::Time randomTime = sf::milliseconds(rand() % timeDiff.asMilliseconds());
            nextSpawn_ = minSpawnInterval_ + randomTime;
        }
        else
        {
            nextSpawn_ = minSpawnInterval_;
        }

        auto path = map_->getPath();
        auto goblin = std::make_shared<Goblin>(Goblin{path.first, path.second});
        enemies_.push_back(goblin);
    }
}


const std::list<std::shared_ptr<Enemy>>& Enemies::getList() const
{
    return enemies_;
}


void Enemies::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto enemy : enemies_)
    {
        enemy->drawSelf(target, states);
    }
}
