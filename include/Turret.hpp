#ifndef TURRET_HPP
#define TURRET_HPP

#include <SFML/Graphics.hpp>
#include "Enemy.hpp"

// The base class of turrets
class Turret
{
	public:
		Turret(int row, int col, int price, float rotationSpeed, float rateOfFire, float radarRange, float projectileRange);

        virtual void update(sf::Time deltaTime, Enemies* enemies);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;       

    protected:
        virtual float rotate(sf::Time deltaTime, Enemies* enemies) = 0;  // note: change this: needs the enemies as a parameter
        virtual bool shoot() = 0;  // note: change this: the return value should be a projectile

        std::shared_ptr<Enemy> getNearestEnemyInRadar(Enemies* enemies);
        float rotateToNearestEnemyInRadar(sf::Time deltaTime, Enemies* enemies);

    public:
        int getRow() const;  // location tile row
        int getCol() const;  // location tile column
        float getTileX() const;  // turret centre x in tile coordinates
        float getTileY() const;  // turret centre y in tile coordinates
        int getPrice() const;  // purchase price
        float getRotationSpeed() const;  // max degrees per second (i.e. 90 means that full round takes 4 seconds)
        float getRateOfFire() const;  // max number of shots per second
        sf::Time getFireInterval() const;  // min time between shots
        float getRadarRange() const;  // radar range as tiles
        float getProjectileRange() const;  // projectile range as tiles
        float getCurrentAngle() const;  // 0-359.999...
        sf::Time getNextFire() const;  // time before can shoot again

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
    
    protected:
        virtual float rotate(sf::Time deltaTime, Enemies* enemies);
        virtual bool shoot();
};


class GunTurret :
    public Turret
{
    public:
        GunTurret(int row, int col);
    
    protected:
        virtual float rotate(sf::Time deltaTime, Enemies* enemies);
        virtual bool shoot();
};


class DoubleGunTurret :
    public Turret
{
    public:
        DoubleGunTurret(int row, int col);
    
    protected:
        virtual float rotate(sf::Time deltaTime, Enemies* enemies);
        virtual bool shoot();
};


class BombTurret :
    public Turret
{
    public:
        BombTurret(int row, int col);
    
    protected:
        virtual float rotate(sf::Time deltaTime, Enemies* enemies);
        virtual bool shoot();   
};


class MissileTurret :
    public Turret
{
    public:
        MissileTurret(int row, int col);
    
    protected:
        virtual float rotate(sf::Time deltaTime, Enemies* enemies);
        virtual bool shoot();  
};


class Turrets : public Node
{
public:
    Turrets(Enemies* enemies);
    virtual void update(sf::Time deltaTime);
    void add(std::shared_ptr<Turret> turret);
    const std::list<std::shared_ptr<Turret>> &getList() const;

private:
    virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    std::list<std::shared_ptr<Turret>> turrets_;
    Enemies* enemies_; ///< Hold by unique pointer elsewhere.
};

#endif
