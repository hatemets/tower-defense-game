#include "../include/Explosion.hpp"
#include "../include/auxiliary/constants.hpp"

Explosion::Explosion(sf::Vector2f position, float explosionRadius)
	: position_(position),
	  explosionRadius_(explosionRadius),
      time_(sf::seconds(0))
{
    picture_.setPosition((float)TileSize * position_);
    update(sf::seconds(0));
}


void Explosion::update(sf::Time deltaTime)
{
    time_ += deltaTime;
    float radius = explosionRadius_ * TileSize;
    int alpha = 200;
    if (time_.asSeconds() < ExplosionExpansionTime)
    {
        radius *= time_.asSeconds() / ExplosionExpansionTime;
    }
    else
    {
        alpha -= 200 * ((time_.asSeconds() - ExplosionExpansionTime) / ExplosionCooldownTime); 
    }
    if (alpha < 0)
    {
        alpha = 0;
    }
	picture_.setRadius(radius);
	picture_.setOrigin(radius, radius);
    picture_.setFillColor(sf::Color(255, 69, 0, alpha));
}


void Explosion::drawSelf(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(picture_, states);
}


bool Explosion::isAlive() const
{
    return time_.asSeconds() < (ExplosionExpansionTime + ExplosionCooldownTime);
}