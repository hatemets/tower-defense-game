#include "../include/Enemy.hpp"
#include "../include/Projectile.hpp"
#include "../include/Map.hpp"
#include "../include/auxiliary/constants.hpp"
#include <math.h>

Enemy::Enemy(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd, float speed, int hitPoints,
             ResourceHolder<sf::Texture, Textures::ID>& textures, Textures::ID enemyStyle, float size)
    : pathIterator_(pathBegin),
      pathEnd_(pathEnd),
	  position_(pathBegin->second + 0.5f, pathBegin->first + 0.5f),
      direction_(0),
      speed_(speed),
      hitPoints_(hitPoints),
	  size_(size)
{
    enemySprite_.setTexture(textures.get(enemyStyle));

    auto imageBounds = enemySprite_.getGlobalBounds();

    enemySprite_.setOrigin(imageBounds.width / 2.f, imageBounds.height / 2.f);
	enemySprite_.setScale(size_ * TileSize / imageBounds.width, size_ * TileSize / imageBounds.height);
	enemySprite_.setPosition(position_.x * TileSize, position_.y * TileSize);

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

        enemySprite_.setPosition(position_.x * TileSize, position_.y * TileSize);
    }
}


void Enemy::drawSelf(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(enemySprite_, states);
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


void Enemy::spawnNewEnemies(EnemyList& enemies, ResourceHolder<sf::Texture, Textures::ID>& textures) const
{
}


// Goblin

Goblin::Goblin(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd, ResourceHolder<sf::Texture, Textures::ID>& textures)
    : Enemy(pathBegin, pathEnd, Enemies::Goblin::speed, Enemies::Goblin::hitPoints, textures, Textures::ID::Goblin, Enemies::Goblin::size)
{
}


// Orc

Orc::Orc(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd, ResourceHolder<sf::Texture, Textures::ID>& textures)
    : Enemy(pathBegin, pathEnd, Enemies::Orc::speed, Enemies::Orc::hitPoints, textures, Textures::ID::Orc, Enemies::Orc::size)
{
}


// Troll

Troll::Troll(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd, ResourceHolder<sf::Texture, Textures::ID>& textures)
    : Enemy(pathBegin, pathEnd, Enemies::Troll::speed, Enemies::Troll::hitPoints, textures, Textures::ID::Troll, Enemies::Troll::size)
{
}


// Slime

Slime::Slime(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd, ResourceHolder<sf::Texture, Textures::ID>& textures)
    : Enemy(pathBegin, pathEnd, Enemies::Slime::speed, Enemies::Slime::hitPoints, textures, Textures::ID::Slime, Enemies::Slime::size)
{
    size_ *= 0.6f; // fix hit radius since the texture has empty area around the enemy picture
}


void Slime::spawnNewEnemies(EnemyList& enemies, ResourceHolder<sf::Texture, Textures::ID>& textures) const
{
    if (!isAlive())
    {
        for (int i = 0; i < Enemies::Slime::babies; i++) 
        {
            auto babySlime = std::make_shared<BabySlime>(BabySlime{pathIterator_, pathEnd_, textures});
			enemies.push_back(babySlime);
        }
    }
}


// BabySlime

BabySlime::BabySlime(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd, ResourceHolder<sf::Texture, Textures::ID>& textures)
    : Enemy(pathBegin, pathEnd, Enemies::BabySlime::speed, Enemies::BabySlime::hitPoints, textures, Textures::ID::Slime, Enemies::BabySlime::size)
{
    size_ *= 0.6f; // fix hit radius since the texture has empty area around the enemy picture
    float deltaX = (rand() % 101 - 50) / 100.f; // random value between -0.5 and +0.5
    float deltaY = (rand() % 101 - 50) / 100.f; // random value between -0.5 and +0.5
    position_ += sf::Vector2f(deltaX, deltaY);
    setDirection(); // fix direction for the changed position
}

