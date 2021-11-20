#ifndef TURRET_HPP
#define TURRET_HPP

#include <SFML/Graphics.hpp>
#include "Enemy.hpp"
#include "Projectile.hpp"

using EnemyList = std::list<std::shared_ptr<Enemy>>;
using ProjectileList = std::list<std::shared_ptr<Projectile>>;

// The base class of turrets
class Turret : public Node
{
	public:
		Turret(int row, int col, int price, float rotationSpeed, float rateOfFire, float radarRange, float projectileRange);

		virtual void update(sf::Time deltaTime, const EnemyList& enemies, ProjectileList& projectiles);
		virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;       

	protected:
		virtual float rotate(sf::Time deltaTime, const EnemyList& enemies) = 0;
        virtual std::vector<std::shared_ptr<Projectile>> shoot() = 0;

		std::shared_ptr<Enemy> getNearestEnemyInRadar(const EnemyList& enemies);
		float rotateToNearestEnemyInRadar(sf::Time deltaTime, bool estimateEnemyMovement, const EnemyList& enemies);

	public:
		int getRow() const { return row_; }                                       // location tile row
		int getCol() const { return col_; }                                       // location tile column
		float getTileX() const { return row_ + 0.5f; }                            // turret centre x in tile coordinates
		float getTileY() const { return col_ + 0.5f; }                            // turret centre y in tile coordinates
		int getPrice() const { return price_; }                                   // purchase price
		float getRotationSpeed() const { return rotationSpeed_; }                 // max degrees per second (i.e. 90 means that full round takes 4 seconds)
		float getRateOfFire() const { return rateOfFire_; }                       // max number of shots per second
		sf::Time getFireInterval() const { return sf::seconds(1 / rateOfFire_); } // min time between shots
		float getRadarRange() const { return radarRange_; }                       // radar range as tiles
		float getProjectileRange() const { return projectileRange_; }             // projectile range as tiles
		float getCurrentAngle() const { return currentAngle_; }                   // 0-359.999...
		sf::Time getNextFire() const { return nextFire_; }                        // time before can shoot again

	protected:
		const int row_;  
		const int col_;  
		const int price_;  
		const float rotationSpeed_;  
		const float rateOfFire_;  
		const float radarRange_;
		const float projectileRange_;  
		float currentAngle_; 
		sf::Time nextFire_;  

		sf::RectangleShape picture_; // Shape should be replaced with a Sprite
};


class SimpleTurret : 
	public Turret
{
	public:
		SimpleTurret(int row, int col);

	private:
		virtual float rotate(sf::Time deltaTime, const EnemyList& enemies) override;
        virtual std::vector<std::shared_ptr<Projectile>> shoot() override;
};


class GunTurret :
	public Turret
{
	public:
		GunTurret(int row, int col);

	private:
		virtual float rotate(sf::Time deltaTime, const EnemyList& enemies) override;
        virtual std::vector<std::shared_ptr<Projectile>> shoot() override;
};


class DoubleGunTurret :
	public Turret
{
	public:
		DoubleGunTurret(int row, int col);

	private:
		virtual float rotate(sf::Time deltaTime, const EnemyList& enemies) override;
        virtual std::vector<std::shared_ptr<Projectile>> shoot() override;
};


class BombTurret :
	public Turret
{
	public:
		BombTurret(int row, int col);

	private:
		virtual float rotate(sf::Time deltaTime, const EnemyList& enemies) override;
        virtual std::vector<std::shared_ptr<Projectile>> shoot() override;
};


class MissileTurret :
	public Turret
{
	public:
		MissileTurret(int row, int col);

	private:
		virtual float rotate(sf::Time deltaTime, const EnemyList& enemies) override;
        virtual std::vector<std::shared_ptr<Projectile>> shoot() override;
};


#endif
