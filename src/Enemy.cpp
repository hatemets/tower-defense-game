#include "../include/Enemy.hpp"
#include "../include/Projectile.hpp"
#include "../include/Map.hpp"
#include "../include/auxiliary/constants.hpp"
#include <math.h>

Enemy::Enemy(std::pair<std::vector<std::pair<int, int>>::const_iterator, std::vector<std::pair<int, int>>::const_iterator> path, float speed, int hitPoints,
             ResourceHolder<sf::Texture, Textures::ID> &textures, Textures::ID enemyStyle, float size)
    : pathIterator_(path.first),
      pathEnd_(path.second),
      position_(path.first->second + 0.5f, path.first->first + 0.5f),
      direction_(0),
      speed_(speed),
      hitPoints_(hitPoints),
      maxHitPoints_(hitPoints),
      size_(size),
      textures_(textures),
      currentHealthTextureId_(Textures::ID::Health100)
{
    // enemy sprite

    enemySprite_.setTexture(textures.get(enemyStyle));
    auto imageBounds = enemySprite_.getGlobalBounds();

    enemySprite_.setOrigin(imageBounds.width / 2.f, imageBounds.height / 2.f);
    enemySprite_.setScale(size_ * TileSize / imageBounds.width, size_ * TileSize / imageBounds.width); // scale based on width
    enemySprite_.setPosition(position_.x * TileSize, position_.y * TileSize);

    // health sprite

    healthSprite_.setTexture(textures.get(currentHealthTextureId_));
    imageBounds = healthSprite_.getGlobalBounds();

    healthSprite_.setOrigin(imageBounds.width / 2.f, imageBounds.height / 2.f);
    healthSprite_.setScale(size_ * TileSize / imageBounds.width, size_ * TileSize / imageBounds.width); // scale based on width
    healthSprite_.setPosition(position_.x * TileSize, (position_.y - Enemies::HealthBarMargin * size_) * TileSize);

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
        }

        Textures::ID healthTextureId = getHealthTextureID();
        if (healthTextureId != currentHealthTextureId_)
        {
            healthSprite_.setTexture(textures_.get(healthTextureId));
            currentHealthTextureId_ = healthTextureId;
        }

        enemySprite_.setPosition(position_.x * TileSize, position_.y * TileSize);
        healthSprite_.setPosition(position_.x * TileSize, (position_.y - Enemies::HealthBarMargin * size_) * TileSize);
    }
}


void Enemy::drawSelf(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(enemySprite_, states);
    target.draw(healthSprite_, states);
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


Textures::ID Enemy::getHealthTextureID() const
{
    int health = 100 * hitPoints_ / maxHitPoints_;
    if (health > 80)
    {
        return Textures::ID::Health100;
    }
    else if (health > 60)
    {
        return Textures::ID::Health80;
    }
    else if (health > 40)
    {
        return Textures::ID::Health60;
    }
    else if (health > 20)
    {
        return Textures::ID::Health40;
    }
    else
    {
        return Textures::ID::Health20;
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

Goblin::Goblin(const Map &map, ResourceHolder<sf::Texture, Textures::ID> &textures)
    : Enemy(map.getRandomPath(), Enemies::Goblin::speed, Enemies::Goblin::hitPoints, textures, Textures::ID::Goblin, Enemies::Goblin::size)
{
}


// Orc

Orc::Orc(const Map &map, ResourceHolder<sf::Texture, Textures::ID> &textures)
    : Enemy(map.getRandomPath(), Enemies::Orc::speed, Enemies::Orc::hitPoints, textures, Textures::ID::Orc, Enemies::Orc::size)
{
}


// Troll

Troll::Troll(const Map &map, ResourceHolder<sf::Texture, Textures::ID> &textures)
    : Enemy(map.getShortestPath(), Enemies::Troll::speed, Enemies::Troll::hitPoints, textures, Textures::ID::Troll, Enemies::Troll::size)
{
}


// Slime

Slime::Slime(const Map &map, ResourceHolder<sf::Texture, Textures::ID> &textures)
    : Enemy(map.getShortestPath(), Enemies::Slime::speed, Enemies::Slime::hitPoints, textures, Textures::ID::Slime, Enemies::Slime::size)
{
}


void Slime::spawnNewEnemies(EnemyList &newEnemies) const
{
    if (!isAlive() && !hasReachedBase())
    {
        for (int i = 0; i < Enemies::Slime::babies; i++)
        {
            auto babySlime = std::make_shared<BabySlime>(BabySlime{*this, textures_});
            newEnemies.push_back(babySlime);
        }
    }
}


// BabySlime

BabySlime::BabySlime(const Slime &parent, ResourceHolder<sf::Texture, Textures::ID> &textures)
    : Enemy(std::make_pair(parent.getPathIterator(), parent.getPathEnd()), Enemies::BabySlime::speed, Enemies::BabySlime::hitPoints, textures, Textures::ID::Slime, Enemies::BabySlime::size)
{
    float deltaX = (rand() % 101 - 50) / 100.f; // random value between -0.5 and +0.5
    float deltaY = (rand() % 101 - 50) / 100.f; // random value between -0.5 and +0.5
    position_ = parent.getPosition() + sf::Vector2f(deltaX, deltaY);
    setDirection(); // fix direction for the changed position
    update(sf::seconds(0));
}


// Kobold

Kobold::Kobold(const Map &map, ResourceHolder<sf::Texture, Textures::ID> &textures)
    : Enemy(map.getSafestPath(), Enemies::Kobold::speed, Enemies::Kobold::hitPoints, textures, Textures::ID::Kobold, Enemies::Kobold::size)
{
}
