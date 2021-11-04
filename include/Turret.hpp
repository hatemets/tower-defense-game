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
        sf::Time fireInterval();
        virtual void rotate(sf::Time deltaTime) = 0;  // note: change this: needs the enemies as a parameter
        virtual bool shoot() = 0;  // note: change this: the return value should be a projectile


	protected:
		sf::RenderWindow& window_;
        int row_;  // location tile row
        int col_;  // location tile column
        int price_;  // purchase price
        float rotationSpeed_;  // max degrees per second (i.e. 90 means that full round takes 4 seconds)
        float rateOfFire_;  // max number of projectiles per second
        float projectileRange_;  // max projectile range as tiles
        float currentAngle_;  // 0-359.999...
        sf::Time nextFire_;  // time before can shoot again

};


class SimpleTurret : 
    public Turret
{
    public:
        SimpleTurret(sf::RenderWindow& window, int row, int col);
        
        // these are in the header so that buy menu can show the turret info (?)
        const int Price = 10;
        const float RotationSpeed = 90;
        const float RateOfFire = 5;
        const float ProjectileRange = 5;
    
    protected:
        virtual void rotate(sf::Time deltaTime);
        virtual bool shoot();
};

#endif
