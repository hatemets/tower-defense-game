#ifndef TURRET_HPP
#define TURRET_HPP

#include <SFML/Graphics.hpp>

// The base class of turrets
class Turret
{
	public:
		Turret(sf::RenderWindow& window, int row, int col, int price, 
               float rotationSpeed, float rateOfFire, float projectileRange);
		virtual void update(sf::Time deltaTime);
		virtual void draw();

    protected:
        void move(int row, int col);
        float calculateDistance(float targetRow, float targetCol) const;
        float calculatetAngle(float targetRow, float targetCol) const;
        virtual float rotate(sf::Time deltaTime) = 0;  // note: change this: needs the enemies as a parameter
        virtual bool shoot() = 0;  // note: change this: the return value should be a projectile

    public:
        int getRow() const;  // location tile row
        int getCol() const;  // location tile column
        int getPrice() const;  // purchase price
        float getRotationSpeed() const;  // max degrees per second (i.e. 90 means that full round takes 4 seconds)
        float getRateOfFire() const;  // max number of shots per second
        sf::Time getFireInterval() const;  // min time between shots
        float getProjectileRange() const;  // projectile range as tiles
        float getCurrentAngle() const;  // 0-359.999...
        sf::Time getNextFire() const;  // time before can shoot again

	protected:
		sf::RenderWindow& window_;
        int row_;  
        int col_;  
        const int price_;  
        const float rotationSpeed_;  
        const float rateOfFire_;  
        const float projectileRange_;  
        float currentAngle_; 
        sf::Time nextFire_;  
};


class SimpleTurret : 
    public Turret
{
    public:
        SimpleTurret(sf::RenderWindow& window, int row, int col);
    
    protected:
        virtual float rotate(sf::Time deltaTime);
        virtual bool shoot();
};


class GunTurret :
    public Turret
{
    public:
        GunTurret(sf::RenderWindow& window, int row, int col);
    
    protected:
        virtual float rotate(sf::Time deltaTime);
        virtual bool shoot();
};


class DoubleGunTurret :
    public Turret
{
    public:
        DoubleGunTurret(sf::RenderWindow& window, int row, int col);
    
    protected:
        virtual float rotate(sf::Time deltaTime);
        virtual bool shoot();
};


class BombTurret :
    public Turret
{
    public:
        BombTurret(sf::RenderWindow& window, int row, int col);
    
    protected:
        virtual float rotate(sf::Time deltaTime);
        virtual bool shoot();   
};


class MissileTurret :
    public Turret
{
    public:
        MissileTurret(sf::RenderWindow& window, int row, int col);
    
    protected:
        virtual float rotate(sf::Time deltaTime);
        virtual bool shoot();  
};

#endif
