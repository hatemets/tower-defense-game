#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <list>
#include "Node.hpp"
#include "Map.hpp"


class Enemy;
using EnemyList = std::list<std::shared_ptr<Enemy>>;


/// The base class of enemies
class Enemy : public Node
{
	public:
		Enemy(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd, float speed, int hitPoints, 
			  ResourceHolder<sf::Texture, Textures::ID>& textures, Textures::ID enemyStyle, float size);

		virtual void update(sf::Time deltaTime) override;
		virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;

	protected:
		void setDirection();
		void move(sf::Time deltaTime);
		Textures::ID getHealthTextureID() const;

	public:
		bool isAlive() const;								 // alive or dead
		bool hasReachedBase() const;						 // has succeed to reach the base
		void hit(int maxDamage);							 // used by projectile
		sf::Vector2f getPosition() const { return position_; }
		float getDirection() const { return direction_; }	 // flight angle
		float getSpeed() const { return speed_; }			 // speed as tiles / second 
		int getHitPoints() const { return hitPoints_; }		 // hitpoints left
		float getRadius() const { return size_ / 2.f; }	     // the hit radius of the enemy
		virtual void spawnNewEnemies(EnemyList& newEnemies) const {}; // possibility to spawn new enemies

	protected:
		std::vector<std::pair<int, int>>::const_iterator pathIterator_;
		std::vector<std::pair<int, int>>::const_iterator pathEnd_;
		sf::Vector2f position_;
		float direction_;
		float speed_;
		int hitPoints_;
		int maxHitPoints_;
		float size_;

		sf::Sprite enemySprite_;
		sf::Sprite healthSprite_;
		ResourceHolder<sf::Texture, Textures::ID>& textures_;
		Textures::ID currentHealthTextureId_;
};


class Goblin : public Enemy
{
	public:
		Goblin(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd, ResourceHolder<sf::Texture, Textures::ID>& textures);
};


class Orc : public Enemy
{
	public:
		Orc(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd, ResourceHolder<sf::Texture, Textures::ID>& textures);
};


class Troll : public Enemy
{
	public:
		Troll(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd, ResourceHolder<sf::Texture, Textures::ID>& textures);
};


class Slime : public Enemy
{
	public:
		Slime(std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd, ResourceHolder<sf::Texture, Textures::ID>& textures);

		virtual void spawnNewEnemies(EnemyList& newEnemies) const;
};


class BabySlime : public Enemy
{
	public:
		BabySlime(const Slime& parent, std::vector<std::pair<int, int>>::const_iterator pathBegin, std::vector<std::pair<int, int>>::const_iterator pathEnd, ResourceHolder<sf::Texture, Textures::ID>& textures);
};


#endif
