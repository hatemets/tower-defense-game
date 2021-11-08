#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

// The base class of enemies
class Enemy
{
	public:
		Enemy(sf::RenderWindow& window, float tileX, float tileY, sf::Time timeUntilSpawn, float speed, int hitPoints);
		virtual void update(sf::Time deltaTime);
		virtual void draw();

    protected:
        void setDirection();
        void move(sf::Time deltaTime); 

    public:
        bool isSpawned() const;  // 
        bool isAlive() const;  // alive or dead
        bool hasReachedBase() const;  // has succeed to reach the base
        void hit(int maxDamage);  // used by projectile
        float getTileX() const;  // location tile row
        float getTileY() const;  // location tile column
        float getDirection() const; // flight angle
        int getHitPoints() const;  // hit points left

	protected:
		sf::RenderWindow& window_;
        float tileX_;  
        float tileY_;  
        float direction_;
        sf::Time timeUntilSpawn_;  
        const float speed_;  
        int hitPoints_;     
};


class Goblin : 
    public Enemy
{
    public:
        Goblin(sf::RenderWindow& window, float tileX, float tileY, sf::Time timeUntilSpawn);
};


#endif