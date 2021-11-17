#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <list>
#include "Node.hpp"
#include "Map.hpp"

/// The base class of enemies
class Enemy
{
    public:
        Enemy(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd, float speed, int hitPoints);
        
        virtual void update(sf::Time deltaTime);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        void setDirection();
        void move(sf::Time deltaTime);

    public:
        bool isAlive() const;        ///< alive or dead
        bool hasReachedBase() const; ///< has succeed to reach the base
        void hit(int maxDamage);     ///< used by projectile
        float getTileX() const;      ///< location tile row
        float getTileY() const;      ///< location tile column
        float getDirection() const;  ///< flight angle
        int getHitPoints() const;    ///< hit points left

    protected:
        std::vector<std::pair<int, int>>::const_iterator pathIterator_;
        std::vector<std::pair<int, int>>::const_iterator pathEnd_;
        float tileX_;
        float tileY_;
        float direction_;
        float speed_;
        int hitPoints_;

        sf::RectangleShape picture_; // Shape should be replaced with a Sprite
};

class Goblin : public Enemy
{
public:
    Goblin(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd);
};

class Enemies : public Node
{
public:
    Enemies(Map* map, sf::Time minSpawnInterval, sf::Time maxSpawnInterval);
    virtual void update(sf::Time deltaTime);
    const std::list<std::shared_ptr<Enemy>> &getList() const;

private:
    virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    std::list<std::shared_ptr<Enemy>> enemies_;
    Map* map_; ///< Hold by unique pointer elsewhere.
    sf::Time minSpawnInterval_;
    sf::Time maxSpawnInterval_;
    sf::Time nextSpawn_;
};

#endif