#include "../include/Turret.hpp"
#include "../include/auxiliary/constants.hpp"
#include <math.h>
#include <iostream>
#include <limits>

Turret::Turret(int row, int col, int price, float rateOfFire, float radarRange,
               ResourceHolder<sf::Texture, Textures::ID> &textures, Textures::ID turretBaseStyle, Textures::ID turretStyle, SoundMap& sounds)
    : row_(row),
      col_(col),
      price_(price),
      rateOfFire_(rateOfFire),
      radarRange_(radarRange),
      currentAngle_(0),
      isAimReady_(false),
      sounds_(sounds),
      timeFromLastFire_(),
      soundId_(sounds_.size())
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

    nextFire_ = sf::seconds(0); // ready to shoot immediately
}


void Turret::addSoundPair(int id, const std::string& filename)
{
    auto buffer = std::make_unique<sf::SoundBuffer>();
    buffer->loadFromFile(filename);

    auto sound = std::make_shared<sf::Sound>();
    sound->setBuffer(*buffer);
    sound->setLoop(true);
    sound->setVolume(30);

    auto audioPair = std::make_pair(id, std::make_pair(std::move(buffer), std::move(sound)));
    sounds_.insert(sounds_.end(), std::move(audioPair));
}


void Turret::update(sf::Time deltaTime, const EnemyList &enemies, ProjectileList &projectiles)
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

    auto sound_ = sounds_.find(soundId_)->second.second;

    // shoot
    if (nextFire_ <= deltaTime && isAimReady_)
    {
        timeFromLastFire_.restart();

        if (sound_->getStatus() != sf::Music::SoundSource::Playing)
        {
            sound_->play();
        }

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
        if (sound_->getStatus() == sf::Music::SoundSource::Playing && timeFromLastFire_.getElapsedTime() > getFireInterval())
        {
            sound_->stop();
        }

        nextFire_ -= deltaTime;
    }
}


void Turret::drawSelf(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(turretBaseSprite_, states);
    target.draw(turretSprite_, states);
}


std::shared_ptr<Enemy> Turret::getNearestEnemyInRadar(const EnemyList &enemies)
{
    std::shared_ptr<Enemy> nearest(nullptr);
    float minDistance = std::numeric_limits<float>::max();

    for (auto &enemy : enemies)
    {
        float enemyDistance = Map::calculateDistance(getPosition(), enemy->getPosition());

        if (enemyDistance < minDistance && enemyDistance <= radarRange_)
        {
            minDistance = enemyDistance;
            nearest = enemy;
        }
    }

    return nearest;
}


std::shared_ptr<Enemy> Turret::getStrongestEnemyInRadar(const EnemyList &enemies)
{
    std::shared_ptr<Enemy> strongest(nullptr);
    int maxHitPoints = -1;

    for (auto &enemy : enemies)
    {
        float enemyDistance = Map::calculateDistance(getPosition(), enemy->getPosition());
        int enemyHitPoints = enemy->getHitPoints();

        if (enemyHitPoints > maxHitPoints && enemyDistance <= radarRange_)
        {
            maxHitPoints = enemyHitPoints;
            strongest = enemy;
        }
    }

    return strongest;
}


float Turret::rotateToEnemy(sf::Time deltaTime, bool estimateEnemyMovement, float projectileSpeed, std::shared_ptr<Enemy> enemy)
{
    isAimReady_ = false;

    if (enemy)
    {
        auto targetPos = enemy->getPosition();

        if (estimateEnemyMovement)
        {
            float barrelLength = TurretScaler * 0.5f;
            float enemyDistance = Map::calculateDistance(sf::Vector2f(getTileX(), getTileY()), targetPos) - barrelLength;
            if (enemyDistance > 0.f)
            {
                float flightTime = enemyDistance / projectileSpeed;
                float enemySpeed = enemy->getSpeed();
                float enemyMovement = flightTime * enemySpeed; // not exact but close enough
                float enemyAngle = enemy->getDirection() * DegreesToRadians;

                targetPos += sf::Vector2f(enemyMovement * std::cos(enemyAngle), enemyMovement * std::sin(enemyAngle));
            }
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

        if (abs(neededRotation) <= maxRotation)
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


float Turret::rotateToNearestEnemyInRadar(sf::Time deltaTime, bool estimateEnemyMovement, float projectileSpeed, const EnemyList &enemies)
{
    auto enemy = getNearestEnemyInRadar(enemies);
    return rotateToEnemy(deltaTime, estimateEnemyMovement, projectileSpeed, enemy);
}


float Turret::rotateToStrongestEnemyInRadar(sf::Time deltaTime, bool estimateEnemyMovement, float projectileSpeed, const EnemyList &enemies)
{
    auto enemy = getStrongestEnemyInRadar(enemies);
    return rotateToEnemy(deltaTime, estimateEnemyMovement, projectileSpeed, enemy);
}


using namespace Turrets;

sf::Vector2f Turret::getProjectileStartPosition(float barrelPositionAngle)
{
    float radians = (currentAngle_ + barrelPositionAngle) * DegreesToRadians;
    float projectileX = getTileX() + TurretScaler * 0.5f * cosf(radians); // x coordinate of the tip of the barrel
    float projectileY = getTileY() + TurretScaler * 0.5f * sinf(radians); // y coordinate of the tip of the barrel
    return sf::Vector2f(projectileX, projectileY);
}


// GunTurret

GunTurret::GunTurret(int row, int col, ResourceHolder<sf::Texture, Textures::ID> &textures, SoundMap& sounds)
    : Turret(row, col, Gun::price, Gun::firerate, Gun::radarRange, textures, Textures::ID::GunTurretBase, Textures::ID::GunTurret, sounds)
{
    addSoundPair(soundId_, "./include/audio/Rifle.wav");
}


float GunTurret::rotate(sf::Time deltaTime, const EnemyList &enemies)
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

DoubleGunTurret::DoubleGunTurret(int row, int col, ResourceHolder<sf::Texture, Textures::ID> &textures, SoundMap& sounds)
    : Turret(row, col, DoubleGun::price, DoubleGun::firerate, DoubleGun::radarRange, textures, Textures::ID::DoubleGunTurretBase, Textures::ID::DoubleGunTurret, sounds)
{
    addSoundPair(soundId_, "./include/audio/Laser.wav");
}


float DoubleGunTurret::rotate(sf::Time deltaTime, const EnemyList &enemies)
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

TripleGunTurret::TripleGunTurret(int row, int col, ResourceHolder<sf::Texture, Textures::ID> &textures, SoundMap& sounds)
    : Turret(row, col, TripleGun::price, TripleGun::firerate, TripleGun::radarRange, textures, Textures::ID::TripleGunTurretBase, Textures::ID::TripleGunTurret, sounds)
{
    addSoundPair(soundId_, "./include/audio/Laser.wav");
}


float TripleGunTurret::rotate(sf::Time deltaTime, const EnemyList &enemies)
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

BombTurret::BombTurret(int row, int col, ResourceHolder<sf::Texture, Textures::ID> &textures, SoundMap& sounds)
    : Turret(row, col, Turrets::Bomb::price, Turrets::Bomb::firerate, Turrets::Bomb::radarRange, textures, Textures::ID::BombTurretBase, Textures::ID::BombTurret, sounds)
{
    addSoundPair(soundId_, "./include/audio/Bomb.wav");
}


float BombTurret::rotate(sf::Time deltaTime, const EnemyList &enemies)
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


// MissileTurret

MissileTurret::MissileTurret(int row, int col, ResourceHolder<sf::Texture, Textures::ID> &textures, SoundMap& sounds)
    : Turret(row, col, Turrets::Missile::price, Turrets::Missile::firerate, Turrets::Missile::radarRange, textures, Textures::ID::MissileBase, Textures::ID::Missile, sounds),
      target_(nullptr),
      textures_(textures)
{
    addSoundPair(soundId_, "./include/audio/Explosion.wav");
    sounds_.find(soundId_)->second.second->setLoop(false);
}


void MissileTurret::drawSelf(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(turretBaseSprite_, states);

    if (nextFire_ <= (getFireInterval() / 2.f))
    {
        target.draw(turretSprite_, states);
    }
}


float MissileTurret::rotate(sf::Time deltaTime, const EnemyList &enemies)
{
    target_ = getStrongestEnemyInRadar(enemies);
    return rotateToEnemy(deltaTime, false, Projectiles::Missile::speed, target_);
}


std::vector<std::shared_ptr<Projectile>> MissileTurret::shoot()
{
    std::vector<std::shared_ptr<Projectile>> projectiles;

    if (target_ && target_->isAlive() && !target_->hasReachedBase())
    {
        sf::Vector2f position = getProjectileStartPosition(0.f);
        projectiles.push_back(std::make_shared<::Missile>(::Missile{position, currentAngle_, target_, textures_}));
    }

    return projectiles;
}
