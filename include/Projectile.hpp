#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>
#include "Enemy.hpp"

using EnemyList = std::list<std::shared_ptr<Enemy>>;

// The base class of projectiles
class Projectile : public Node
{
	public:
		Projectile(sf::Vector2f position, float direction, float speed, float flightRange, int maxDamage, bool drawAsVertex, float explosionRadius = 0.f);

		virtual void update(sf::Time deltaTime, const EnemyList& enemies);
		virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;

	protected:
		std::shared_ptr<Enemy> checkHit(const EnemyList& enemies);
		EnemyList getEnemiesInExplosion(const EnemyList &enemies);
		void explode(std::shared_ptr<Enemy> hitEnemy, const EnemyList& enemies);
		virtual void flight(sf::Time deltaTime); 

	public:
		bool isAlive() const;  							    // has lifetime left
		sf::Vector2f getPosition() const { return position_; }
		float getDirection() const { return direction_; }   // flight angle
		bool drawAsVertex() const { return drawAsVertex_; } // draw as vertex (instead of a shape/sprite)

	protected:
		sf::Vector2f position_;
		float direction_;  

		const float speed_;          // projectile speed as tiles per second
		const float explosionRadius_; // damage area as tiles (0 if requires direct hit)
		const int maxDamage_;        // max hit points damage 
		const bool drawAsVertex_;

		sf::Time lifetimeLeft_; 
};


class Bullet : public Projectile
{
	public:
		Bullet(sf::Vector2f position, float direction);
};


class Bomb : public Projectile
{
	public:
		Bomb(sf::Vector2f position, float direction);

		virtual void update(sf::Time deltaTime, const EnemyList& enemies) override;
		virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;
		
		sf::CircleShape picture_;
};


class Missile : public Projectile
{
	public:
		Missile(sf::Vector2f position, float direction);

	protected:
		virtual void flight(sf::Time deltaTime); 
};


#endif
