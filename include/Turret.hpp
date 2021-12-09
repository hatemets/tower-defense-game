#ifndef TURRET_HPP
#define TURRET_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Enemy.hpp"
#include "Projectile.hpp"

using EnemyList = std::list<std::shared_ptr<Enemy>>;
using ProjectileList = std::list<std::shared_ptr<Projectile>>;
using SoundMap = std::map<int, std::pair<std::unique_ptr<sf::SoundBuffer>, std::shared_ptr<sf::Sound>>>;

// The base class of turrets
class Turret : public Node
{
	public:
		Turret(int row, int col, int price, float rateOfFire, float radarRange,
			ResourceHolder<sf::Texture, Textures::ID> &textures, Textures::ID turretBaseStyle, Textures::ID turretStyle, SoundMap& sounds);

		virtual void update(sf::Time deltaTime, const EnemyList &enemies, ProjectileList &projectiles);
		virtual void drawSelf(sf::RenderTarget &target, sf::RenderStates states) const override;
		virtual std::vector<std::shared_ptr<Projectile>> shoot() = 0;

	protected:
        virtual float rotate(sf::Time deltaTime, const EnemyList &enemies) = 0;

        std::shared_ptr<Enemy> getNearestEnemyInRadar(const EnemyList &enemies);
        std::shared_ptr<Enemy> getStrongestEnemyInRadar(const EnemyList &enemies);
        float rotateToEnemy(sf::Time deltaTime, bool estimateEnemyMovement, float projectileSpeed, std::shared_ptr<Enemy> enemy);
        float rotateToNearestEnemyInRadar(sf::Time deltaTime, bool estimateEnemyMovement, float projectileSpeed, const EnemyList &enemies);
        float rotateToStrongestEnemyInRadar(sf::Time deltaTime, bool estimateEnemyMovement, float projectileSpeed, const EnemyList &enemies);

		sf::Vector2f getProjectileStartPosition(float barrelPositionAngle);

	public:
		int getRow() const { return row_; }			   // location tile row
		int getCol() const { return col_; }			   // location tile column
		float getTileX() const { return col_ + 0.5f; } // turret centre x in tile coordinates
		float getTileY() const { return row_ + 0.5f; } // turret centre y in tile coordinates
		sf::Vector2f getPosition() const { return sf::Vector2f(getTileX(), getTileY()); }
		int getPrice() const { return price_; }										// purchase price
		float getRateOfFire() const { return rateOfFire_; }							// max number of shots per second
		sf::Time getFireInterval() const { return sf::seconds(1.f / rateOfFire_); } // min time between shots
		float getRadarRange() const { return radarRange_; }							// radar range as tiles
		float getCurrentAngle() const { return currentAngle_; }						// 0-359.999...
		sf::Time getNextFire() const { return nextFire_; }							// time before can shoot again
        void addSoundPair(int id, const std::string& filename);
        int getSoundId() const { return soundId_; }
        void stopSound() { sounds_.find(soundId_)->second.second->stop(); }

	protected:
		const int row_;
		const int col_;
		const int price_;
		const float rateOfFire_;
		const float radarRange_;
		float currentAngle_;
		bool isAimReady_; // is current angle OK for shooting
		sf::Time nextFire_;

		sf::Sprite turretBaseSprite_;
		sf::Sprite turretSprite_;
        SoundMap& sounds_;
        sf::Clock timeFromLastFire_;
        int soundId_;
};


class GunTurret : public Turret
{
	public:
		GunTurret(int row, int col, ResourceHolder<sf::Texture, Textures::ID> &textures, SoundMap& sounds);

	private:
		virtual float rotate(sf::Time deltaTime, const EnemyList &enemies) override;
		virtual std::vector<std::shared_ptr<Projectile>> shoot() override;
};


class DoubleGunTurret : public Turret
{
	public:
		DoubleGunTurret(int row, int col, ResourceHolder<sf::Texture, Textures::ID> &textures, SoundMap& sounds);

	private:
		virtual float rotate(sf::Time deltaTime, const EnemyList &enemies) override;
		virtual std::vector<std::shared_ptr<Projectile>> shoot() override;
};


class TripleGunTurret : public Turret
{
	public:
		TripleGunTurret(int row, int col, ResourceHolder<sf::Texture, Textures::ID> &textures, SoundMap& sounds);

	private:
		virtual float rotate(sf::Time deltaTime, const EnemyList &enemies) override;
		virtual std::vector<std::shared_ptr<Projectile>> shoot() override;
};


class BombTurret : public Turret
{
	public:
		BombTurret(int row, int col, ResourceHolder<sf::Texture, Textures::ID> &textures, SoundMap& sounds);

	private:
		virtual float rotate(sf::Time deltaTime, const EnemyList &enemies) override;
		virtual std::vector<std::shared_ptr<Projectile>> shoot() override;
};


class MissileTurret : public Turret
{
	public:
		MissileTurret(int row, int col, ResourceHolder<sf::Texture, Textures::ID> &textures, SoundMap& sounds);

		virtual void drawSelf(sf::RenderTarget &target, sf::RenderStates states) const override;

	private:
		virtual float rotate(sf::Time deltaTime, const EnemyList &enemies) override;
		virtual std::vector<std::shared_ptr<Projectile>> shoot() override;

		std::shared_ptr<Enemy> target_; // the targeted enemy
		ResourceHolder<sf::Texture, Textures::ID> &textures_;
};

#endif
