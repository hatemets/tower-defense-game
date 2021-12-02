#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>
#include "Enemy.hpp"

// The base class of projectiles
class Projectile : public Node
{
	public:
		Projectile(sf::Vector2f position, float direction, float speed, float flightRange, int maxDamage, float size, float explosionRadius = 0.f);

		virtual void update(sf::Time deltaTime, const EnemyList &enemies);
		virtual void drawSelf(sf::RenderTarget &target, sf::RenderStates states) const override;

	protected:
		std::shared_ptr<Enemy> checkHit(const EnemyList &enemies);
		EnemyList getEnemiesInExplosion(const EnemyList &enemies);
		void explode(std::shared_ptr<Enemy> hitEnemy, const EnemyList &enemies);
		virtual void flight(sf::Time deltaTime);

	public:
		bool isAlive() const; // has lifetime left
		sf::Vector2f getPosition() const { return position_; }
		float getDirection() const { return direction_; } // flight angle
		float getRadius() const { return size_ / 2.f; }
		float getExplosionRadius() const { return explosionRadius_; }
		int getMaxDamage() const { return maxDamage_; }
		bool drawAsVertex() const { return size_ == 0.f; } // draw as vertex (instead of a shape/sprite)

	protected:
		sf::Vector2f position_;		  // position as tile coordinates
		float direction_;			  // flight direction
		const float speed_;			  // projectile speed as tiles per second
		const float explosionRadius_; // damage area as tiles (0 if requires direct hit)
		const int maxDamage_;		  // max hit points damage
		const float size_;			  // projectile size (both visual and hit area)

		sf::Time lifetimeLeft_; // flight time left (if no hit)
};


class Bullet : public Projectile
{
	public:
		Bullet(sf::Vector2f position, float direction);

		virtual void update(sf::Time deltaTime, const EnemyList &enemies) override;
		virtual void drawSelf(sf::RenderTarget &target, sf::RenderStates states) const override;

	private:
		sf::CircleShape picture_;
};


class Bomb : public Projectile
{
	public:
		Bomb(sf::Vector2f position, float direction);

		virtual void update(sf::Time deltaTime, const EnemyList &enemies) override;
		virtual void drawSelf(sf::RenderTarget &target, sf::RenderStates states) const override;

	private:
		sf::CircleShape picture_;
};


class Missile : public Projectile
{
	public:
		Missile(sf::Vector2f position, float direction, std::shared_ptr<Enemy> target, ResourceHolder<sf::Texture, Textures::ID> &textures);

		virtual void update(sf::Time deltaTime, const EnemyList &enemies) override;
		virtual void drawSelf(sf::RenderTarget &target, sf::RenderStates states) const override;

	private:
		std::shared_ptr<Enemy> target_;
		sf::Sprite sprite_;
};

#endif
