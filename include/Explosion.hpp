#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include <SFML/Graphics.hpp>
#include "Node.hpp"

class Explosion : public Node
{
	public:
		Explosion(sf::Vector2f position, float explosionRadius);

		virtual void update(sf::Time deltaTime);
		virtual void drawSelf(sf::RenderTarget &target, sf::RenderStates states) const override;

	public:
		bool isAlive() const; // has lifetime left

	protected:
		sf::Vector2f position_;		  // position as tile coordinates
		const float explosionRadius_; // damage area as tiles (0 if requires direct hit)

		sf::Time time_; 
        sf::CircleShape picture_;
};

#endif
