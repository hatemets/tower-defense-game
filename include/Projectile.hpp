#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>
#include "Enemy.hpp"

using EnemyList = std::list<std::shared_ptr<Enemy>>;

// The base class of projectiles
class Projectile
{
	public:
		Projectile(float tileX, float tileY, float direction, float speed, float flightRange, float explosionRange, float maxDamage);

		virtual void update(sf::Time deltaTime, const EnemyList& enemies);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
		virtual std::shared_ptr<Enemy> checkHit(const EnemyList& enemies);
		virtual void explode(std::shared_ptr<Enemy> hitEnemy, const EnemyList& enemies);
		virtual void flight(sf::Time deltaTime); 

	public:
		bool isAlive() const;  // lifetime left
		float getTileX() const;  // location tile row
		float getTileY() const;  // location tile column
		float getDirection() const; // flight angle

	protected:
		float tileX_;  
		float tileY_;  
		float direction_;  
		const float speed_;  
		const float explosionRange_;  
		const float maxDamage_; 
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


class Projectiles : public Node
{
	public:
		Projectiles(const EnemyList& enemies);
		virtual void update(sf::Time deltaTime);

		void add(std::shared_ptr<Projectile> projectile);
		// const std::list<std::shared_ptr<Projectile>> &getList() const;

	private:
		virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		std::list<std::shared_ptr<Bullet>> bullets_;
		std::list<std::shared_ptr<Projectile>> otherProjectiles_;

		const EnemyList& enemies_;

		sf::VertexArray bulletVertices_; ///< combine picture of all bullets
};


#endif
