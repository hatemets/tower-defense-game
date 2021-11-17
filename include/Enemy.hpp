#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <list>
#include "Node.hpp"
#include "Map.hpp"

/// The base class of enemies
class Enemy : public Node
{
	public:
		Enemy(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd, float speed, int hitPoints);

		virtual void update(sf::Time deltaTime);
		virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
		void setDirection();
		void move(sf::Time deltaTime);

	public:
		bool isAlive() const;        // alive or dead
		bool hasReachedBase() const; // has succeed to reach the base
		void hit(int maxDamage);     // used by projectile
		float getTileX() const { return tileX_; } // flight angle
		float getTileY() const { return tileY_; } // hit points left
		float getDirection() const { return direction_; } // location tile row
		int getHitPoints() const { return hitPoints_; } // location tile column

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

#endif
