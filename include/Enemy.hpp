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
		Enemy(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd, float speed, int hitPoints, 
			  ResourceHolder<sf::Texture, Textures::ID>& textures, Textures::ID enemyStyle, float size);

		virtual void update(sf::Time deltaTime) override;
		virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;

	protected:
		void setDirection();
		void move(sf::Time deltaTime);

	public:
		bool isAlive() const;								 // alive or dead
		bool hasReachedBase() const;						 // has succeed to reach the base
		void hit(int maxDamage);							 // used by projectile
		sf::Vector2f getPosition() const { return position_; }
		float getDirection() const { return direction_; }	 // flight angle
		float getSpeed() const { return speed_; }			 // speed as tiles / second 
		int getHitPoints() const { return hitPoints_; }		 // hitpoints left
		float getRadius() const { return size_ / 2.f; }	     // the hit radius of the enemy

	protected:
		std::vector<std::pair<int, int>>::const_iterator pathIterator_;
		std::vector<std::pair<int, int>>::const_iterator pathEnd_;
		sf::Vector2f position_;
		float direction_;
		float speed_;
		int hitPoints_;
		float size_;

		sf::Sprite enemySprite_;
};

class Goblin : public Enemy
{
	public:
		Goblin(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd, ResourceHolder<sf::Texture, Textures::ID>& textures);
};

#endif
