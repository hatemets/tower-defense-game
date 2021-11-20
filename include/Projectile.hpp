#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>
#include "Enemy.hpp"

using EnemyList = std::list<std::shared_ptr<Enemy>>;

// The base class of projectiles
class Projectile : public Node
{
	public:
		Projectile(float tileX, float tileY, float direction, float speed, float flightRange, float explosionRange, int maxDamage, bool drawAsVertex);

		virtual void update(sf::Time deltaTime, const EnemyList& enemies);
		virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;

	protected:
		virtual std::shared_ptr<Enemy> checkHit(const EnemyList& enemies);
		virtual void explode(std::shared_ptr<Enemy> hitEnemy, const EnemyList& enemies);
		virtual void flight(sf::Time deltaTime); 

	public:
		bool isAlive() const;  							    // has lifetime left
		float getTileX() const { return tileX_; }  		    // projectile centre x in tile coordinates
		float getTileY() const { return tileY_; }   		// projectile centre y in tile coordinates
		float getDirection() const { return direction_; }   // flight angle
		bool drawAsVertex() const { return drawAsVertex_; } // draw as vertex (instead of a sprite)

	protected:
		float tileX_;  
		float tileY_;  
		float direction_;  
		const float speed_;  
		const float explosionRange_;  
		const int maxDamage_; 
		const bool drawAsVertex_;
		sf::Time lifetimeLeft_; 
};


class Bullet : 
	public Projectile
{
	public:
		Bullet(float tileX, float tileY, float direction);
};


class Bomb :
	public Projectile
{
	public:
		Bomb(float tileX, float tileY, float directionl);
};


class Missile :
	public Projectile
{
	public:
		Missile(float tileX, float tileY, float direction);

	protected:
		virtual std::shared_ptr<Enemy> checkHit(const EnemyList& enemies);
		virtual void explode(std::shared_ptr<Enemy> enemy, const EnemyList& enemies);
		virtual void flight(sf::Time deltaTime); 
};


#endif
