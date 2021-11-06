#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>

// The base class of turrets
class Projectile
{
	public:
		Projectile(sf::RenderWindow& window, float row, float col, float direction, float speed, 
                   float flightRange, float explosionRange, float maxDamage);
		virtual void update(sf::Time deltaTime);
		virtual void draw();

    protected:
        virtual bool isHit(); // fix this: change return value to enemy list
        virtual void flight(sf::Time deltaTime); 
        // float calculateDistance(float targetRow, float targetCol) const; // fix this: use common code with turret
        // float calculatetAngle(float targetRow, float targetCol) const; // fix this: use common code with turret

    public:
        float getRow() const;  // location tile row
        float getCol() const;  // location tile column
        float getDirection() const; // flight angle

	protected:
		sf::RenderWindow& window_;
        float row_;  
        float col_;  
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
        Bullet(sf::RenderWindow& window, float row, float col, float direction);
};


class Bomb :
    public Projectile
{
    public:
        Bomb(sf::RenderWindow& window, float row, float col, float directionl);
};


class Missile :
    public Projectile
{
    public:
        Missile(sf::RenderWindow& window, float row, float col, float direction);
    
    protected:
        virtual bool isHit();
        virtual void flight(sf::Time deltaTime);
    
    private:
        // float calculateDistance(float targetRow, float targetCol) const; // fix this: use common code with turret
        // float calculatetAngle(float targetRow, float targetCol) const; // fix this: use common code with turret
};


#endif