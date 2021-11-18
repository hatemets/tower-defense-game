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
		// TODO: Remove hardcoded values
		Enemy(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd, float speed, int hitPoints, float radius = 15.f);

		virtual void update(sf::Time deltaTime) override;
		virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;

	protected:
		void setDirection();
		void move(sf::Time deltaTime);

	public:
		bool isAlive() const;								 // alive or dead
		bool hasReachedBase() const;						 // has succeed to reach the base
		void hit(int maxDamage);							 // used by projectile
		float getTileX() const { return tileX_; }			 // flight angle
		float getTileY() const { return tileY_; }			 // hitpoints left
		float getDirection() const { return direction_; }	 // location tile row
		int getHitPoints() const { return hitPoints_; }		 // location tile column
		float getRadius() const { return radius_; }			 // radius of the enemy (assuming it's a circle)

	protected:
		std::vector<std::pair<int, int>>::const_iterator pathIterator_;
		std::vector<std::pair<int, int>>::const_iterator pathEnd_;
		float tileX_;
		float tileY_;
		float direction_;
		float speed_;
		int hitPoints_;
		float radius_;

		sf::RectangleShape picture_; // Shape should be replaced with a Sprite
};

class Goblin : public Enemy
{
	public:
		Goblin(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd);
};

#endif
