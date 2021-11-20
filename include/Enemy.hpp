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
		Enemy(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd, float speed, int hitPoints, float radius = 0.25f);

		virtual void update(sf::Time deltaTime) override;
		virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;

	protected:
		void setDirection();
		void move(sf::Time deltaTime);

	public:
		bool isAlive() const;								 // alive or dead
		bool hasReachedBase() const;						 // has succeed to reach the base
		void hit(int maxDamage);							 // used by projectile
		float getTileX() const { return tileX_; }	         // the x location in tile coordinates 		 
		float getTileY() const { return tileY_; }			 // the y location in tile coordinates 
		float getDirection() const { return direction_; }	 // flight angle
		int getHitPoints() const { return hitPoints_; }		 // hitpoints left
		float getRadius() const { return radius_; }			 // the hit radius of the enemy

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
